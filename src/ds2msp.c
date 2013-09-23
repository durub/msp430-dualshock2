#include "ds2msp.h"
#include <msp430.h>

/* Library configuration */
#define DS2MSP_PORTOUT P1OUT
#define DS2MSP_PORTIN P1IN
#define DS2MSP_PORTDIR P1DIR
#define DS2MSP_PORTSEL P1SEL
// "pin" is a little misleading
// if it turns out to not use a lot of memory and flash space I will try to make it dynamic later
#define DS2MSP_CLOCK_PIN BIT0
#define DS2MSP_COMMAND_PIN BIT1
#define DS2MSP_DATA_PIN BIT2
#define DS2MSP_ATTENTION_PIN BIT3

#define CHECK_BIT(var,n) ((((var) & (1 << (n)))) >> (n))

/* delay between exchanged bytes */
static void byte_delay() {
    unsigned short i;
    for(i = 0; i < 12000; i++);
}

/* delay between each bit */
static void bit_delay() {
    unsigned char i;
    for(i = 0; i < 80; i++);
}

/* exchanges a byte (full duplex) with the controller */
static byte send_and_receive_byte(byte send_data) {
    byte received_data = 0x00;
    unsigned char i;

    /* send bit by bit */
    for(i = 0; i < 8; i++) {
        /* send our bit by setting the command pin with our send_data "i" bit */
        if(CHECK_BIT(send_data, i) == 0) {
            DS2MSP_PORTOUT &= ~DS2MSP_COMMAND_PIN;
        } else {
            DS2MSP_PORTOUT |=  DS2MSP_COMMAND_PIN;
        }
        /* sinalize that our data is there and ask for the controller data by
           setting the clock pin to low */
        DS2MSP_PORTOUT &= ~DS2MSP_CLOCK_PIN;
        bit_delay();
        /* receive the data sent by the controller */
        if((DS2MSP_PORTIN & DS2MSP_DATA_PIN) != 0) {
            received_data |= (1 << i);
        }
        /* set the clock to high */
        DS2MSP_PORTOUT |= DS2MSP_CLOCK_PIN;
        bit_delay();
    }
    
    return received_data;
}

byte controller_data[9] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void ds2msp_configure_controller(byte flags) {
    DS2MSP_PORTDIR = (DS2MSP_PORTDIR & 0xf0) | (~DS2MSP_DATA_PIN & 0x0f);
    DS2MSP_PORTSEL &= 0xf0;
    DS2MSP_PORTOUT |= (DS2MSP_CLOCK_PIN | DS2MSP_ATTENTION_PIN);
}

void ds2msp_poll_controller() {
    DS2MSP_PORTOUT &= ~DS2MSP_ATTENTION_PIN;
    controller_data[0] = send_and_receive_byte(0x01);
    byte_delay();
    controller_data[1] = send_and_receive_byte(0x42);
    byte_delay();
    controller_data[2] = send_and_receive_byte(0x00);
    byte_delay();
    controller_data[3] = send_and_receive_byte(0x00);
    byte_delay();
    controller_data[4] = send_and_receive_byte(0x00);
    if(controller_data[1] == 0x73) { /* analog mode enabled, still not implemented */
        byte_delay();
        controller_data[5] = send_and_receive_byte(0x00);
        byte_delay();
        controller_data[6] = send_and_receive_byte(0x00);
        byte_delay();
        controller_data[7] = send_and_receive_byte(0x00);
        byte_delay();
        controller_data[8] = send_and_receive_byte(0x00);
        byte_delay();
        controller_data[9] = send_and_receive_byte(0x00);
    }
    DS2MSP_PORTOUT |= DS2MSP_ATTENTION_PIN;
}

byte ds2msp_check_button(byte button) {
    if((controller_data[(button & 0xf0) >> 4] & (1 << (button & 0x0f))) == 0) {
        return 1;
    } else {
        return 0;
    }
}