#!/bin/bash

# default from `brew tap osx-cross/avr` and `brew install avr-gcc`
export AVR_PATH=/Applications/Arduino.app/Contents/Java/hardware/tools/avr/
export PROGRAM="Joystick.hex"

# search for connected device
for i in $(seq 1 10); do
    export DEVICE_ID=$(ls /dev/cu.usb* 2>&1 | grep -v "No such")
    if [ -z "$DEVICE_ID" ]; then
        echo -ne "[$i of 10] Looking for device, connect and double tap the button to put it in flash mode \033[0K\r"
        sleep 1.5
    else
        echo "Found device, flashing ${PROGRAM} to ${DEVICE_ID}"
        ${AVR_PATH}/bin/avrdude \
            -C${AVR_PATH}/etc/avrdude.conf \
            -v \
            -patmega32u4 \
            -cstk500v1 \
            -P${DEVICE_ID} \
            -b19200 \
            -Uflash:w:$(pwd)/${PROGRAM}:i
        break
    fi
done
