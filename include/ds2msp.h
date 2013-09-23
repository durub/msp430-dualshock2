#ifndef DUALSHOCK2_MSP_H
#define DUALSHOCK2_MSP_H

typedef unsigned char byte;

/* controller config (not supported yet) */
#define DS2MSP_PRESSURE (1 << 0)
#define DS2MSP_RUMBLE   (1 << 1)

/* digital buttons */
#define DS2MSP_SELECT 0x30
#define DS2MSP_L3 0x31
#define DS2MSP_R3 0x32
#define DS2MSP_START 0x33
#define DS2MSP_UP 0x34
#define DS2MSP_RIGHT 0x35
#define DS2MSP_DOWN 0x36
#define DS2MSP_LEFT 0x37
#define DS2MSP_L2 0x40
#define DS2MSP_R2 0x41
#define DS2MSP_L1 0x42
#define DS2MSP_R1 0x43
#define DS2MSP_TRIANGLE 0x44
#define DS2MSP_CIRCLE 0x45
#define DS2MSP_X 0x46
#define DS2MSP_SQUARE 0x47

/* Configures the controller port */
void ds2msp_configure_controller(byte flags);
void ds2msp_poll_controller();
unsigned char ds2msp_check_button(byte button);

#endif