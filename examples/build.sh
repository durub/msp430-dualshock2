#!/bin/bash
# Usage: [DEBUG=0 or 1] [CPU=msp430x....] build.sh
# Uses the msp430-gcc toolchain

# Choose your CPU (defaults to msp430g2553)
CPU=${CPU:-msp430g2553}

DEBUG=${DEBUG:-0}
DEBUG_FLAGS="-Os"
if [ $DEBUG == 1 ]; then
    DEBUG_FLAGS="-O0 -g3"
fi

# Build the simple_polling example
msp430-gcc ${DEBUG_FLAGS} -mmcu=${CPU} -I../include -o simple_polling.elf ../src/ds2msp.c simple_polling.c