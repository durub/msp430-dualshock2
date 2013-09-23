#include "ds2msp.h"
#include <msp430.h>

byte circle, square, triangle, x, select, start, up, l3, r3;

int main(void) {
    WDTCTL = WDTPW + WDTHOLD; /* disable the watchdog */

    ds2msp_configure_controller(0); /* flags aren't implemented at the moment, hence the zero */
    while(1) {
        ds2msp_poll_controller(); /* polls the controller */
        circle = ds2msp_check_button(DS2MSP_CIRCLE);
        square = ds2msp_check_button(DS2MSP_SQUARE);
        triangle = ds2msp_check_button(DS2MSP_TRIANGLE);
        x = ds2msp_check_button(DS2MSP_X);
        select = ds2msp_check_button(DS2MSP_SELECT);
        start = ds2msp_check_button(DS2MSP_START);
        up = ds2msp_check_button(DS2MSP_UP);
        l3 = ds2msp_check_button(DS2MSP_L3);
        r3 = ds2msp_check_button(DS2MSP_R3);
    }

    return 0;
}