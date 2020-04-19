## Animal Crossing Hax

#### How to use

(TODO: add more instructions)

In case you see issues with controller conflicts while in docked mode, try using a USB-C to USB-A adapter in handheld mode. In dock mode, changes in the HDMI connection will briefly make the Switch not respond to incoming USB commands, skipping parts of the sequence. These changes may include turning off the TV, or switching the HDMI input. (Switching to the internal tuner will be OK, if this doesn't trigger a change in the HDMI input.)

#### Pre-reqs
1) Clone this repo

2) Initialize sub modules (or manually clone lufa)
  ```bash
  # from project root
  git clone https://github.com/abcminiuser/lufa.git
  # or
  git clone --recursive git@github.com:bertrandom/snowball-thrower.git
  ```
  
3) Install Arduino IDE https://www.arduino.cc/en/Main/Software

#### Compiling and Flashing onto the Arduino Micro

1) Get AVR tool chain
  ```bash
  brew tap osx-cross/avr
  brew install avr-gcc
  ```

2) Build
  ```bash
  # from project root
  make
  ```

3) Flash (tap the button twice to put it into flash mode)
  ```bash
  # from project root
  ./flash.sh
  ```
  
##### Windows

1) Install GnuWin's Make http://gnuwin32.sourceforge.net/packages/make.htm

2) Add a few things to your SYSTEM PATH
    - Search for "Environment Variables", open the one in Control Panel
    - Click on "Environment Variables..." button on bottom right
    - In "System variables" select "Path" then click "Edit..."
        - Add `C:\Program Files (x86)\GnuWin32\bin`
        - Add `C:\Program Files (x86)\Arduino\hardware\tools\avr\bin`




#### Compiling and Flashing onto the Teensy 2.0++

Go to the Teensy website and download/install the [Teensy Loader application](https://www.pjrc.com/teensy/loader.html). For Linux, follow their instructions for installing the [GCC Compiler and Tools](https://www.pjrc.com/teensy/gcc.html). For Windows, you will need the [latest AVR toolchain](http://www.atmel.com/tools/atmelavrtoolchainforwindows.aspx) from the Atmel site. See [this issue](https://github.com/LightningStalker/Splatmeme-Printer/issues/10) and [this thread](http://gbatemp.net/threads/how-to-use-shinyquagsires-splatoon-2-post-printer.479497/) on GBAtemp for more information. (Note for Mac users - the AVR MacPack is now called AVR CrossPack. If that does not work, you can try installing `avr-gcc` with `brew`.)

LUFA has been included as a git submodule, so cloning the repo like this:

```
git clone --recursive git@github.com:bertrandom/snowball-thrower.git
```

will put LUFA in the right directory.

You will also need to edit `makefile` before issuing `make`. Change `MCU = atmega32u4` on line 15 to `MCU = at90usb1286`.

Now you should be ready to rock. Open a terminal window in the `SwitchAutomator` directory, type `make`, and hit enter to compile. If all goes well, the printout in the terminal will let you know it finished the build! Follow the directions on flashing `Joystick.hex` onto your Teensy, which can be found page where you downloaded the Teensy Loader application.

#### Compiling and Flashing onto the Arduino UNO R3
You will need to set your [Arduino in DFU mode](https://www.arduino.cc/en/Hacking/DFUProgramming8U2), and flash its USB controller. (Note for Mac users - try [brew](https://brew.sh/index_it.html) to install the dfu-programmer with `brew install dfu-programmer`.) Setting an Arduino UNO R3 in DFU mode is quite easy, all you need is a jumper (the boards come with the needed pins in place). Please note that once the board is flashed, you will need to flash it back with the original firmware to make it work again as a standard Arduino. To compile this project you will need the AVR GCC Compiler and Tools. (Again for Mac users - try brew, adding the [osx-cross/avr](osx-cross/avr) repository, all you need to do is to type `brew tap osx-cross/avr` and `brew install avr-gcc`.) Next, you need to grab the LUFA library: download and install it following the steps described for the Teensy 2.0++.

Finally, open a terminal window in the `SwitchAutomator` directory, edit the `makefile` setting `MCU = atmega16u2`, and compile by typing `make`. Follow the [DFU mode directions](https://www.arduino.cc/en/Hacking/DFUProgramming8U2) to flash `Joystick.hex` onto your Arduino UNO R3 and you are done.

#### Compiling and Flashing onto the Arduino Micro
The Arduino Micro is more like the Teensy in that it has a single microcontroller that communicates directly over USB. Most of the steps are the same as those for the Teensy, except do not download Teensy Loader program. You will also need to edit `makefile` before issuing `make`. Change `MCU = at90usb1286` on line 15 to `MCU = atmega32u4`.

Once finished building, start up Arduino IDE. Under `File -> Preferences`, check `Show verbose output during: upload` and pick OK. With the Arduino plugged in and properly selected under `Tools`, upload any sketch. Find the line with `avrdude` and copy the entire `avrdude` command and all options into a terminal, replacing the `.hex` file and path to the location of the `Joystick.hex` created in the previous step. Also make sure the `-P/dev/??` port is the same as what Arduino IDE is currently reporting. Now double tap the reset button on the Arduino and quickly press Enter in the terminal. This may take several tries. You may need to press Enter first and then the reset button or try various timings. Eventually, `avrdude` should report success. Store the `avrdude` command in a text file or somewhere safe since you will need it every time you want to print a new image.

Sometimes, the Arduino will show up under a different port, so you may need to run Arduino IDE again to see the current port of your Micro.

If you ever need to use your Arduino Micro with Arduino IDE again, the process is somewhat similar. Upload your sketch in the usual way and double tap reset button on the Arduino. It may take several tries and various timings, but should eventually be successful.

The Arduino Leonardo is theoretically compatible, but has not been tested. It also has the ATmega32u4, and is layed out somewhat similar to the Micro.

#### Attaching the optional buzzer
A suitable 5V buzzer may be attached to any of the available pins on PORTB or PORTD. When compiled with `make with-alert`, it will begin sounding once printing has finished. See above warning about PORTB and PORTD. Reference section 31 of [the AT90USB1286 datasheet](http://www.atmel.com/images/doc7593.pdf) for maximum current specs.

Pin 6 on the Teensy is already used for the LED and it draws around 3mA when fully lit. It is recommended to connect the buzzer to another pin. Do not bridge pins for more current.

For the Arduino UNO, the easiest place to connect the buzzer is to any pin of JP2, or pins 1, 3, or 4 of ICSP1, next to JP2. Refer to section 29 of [the ATmega16u2 datasheet](http://www.atmel.com/Images/Atmel-7766-8-bit-AVR-ATmega16U4-32U4_Datasheet.pdf) for maximum current specs. Do not bridge pins for more current.

On the Arduino Micro, D0-D3 may be used, or pins 1, 3, or 4 (PORTB) on the ICSP header. Power specs are the same as for the AT90USB1286 used on the Teensy. The TX and RX LEDs are on PORTD and PORTB respectively and draw around 3mA apiece. Do not bridge pins for more current.

#### Using an arduino Uno as ICSP programmer
This allows the program to be updated without disconnecting from a switch. Locate the small "." dot in one corner of your UNO's ICSP connector. Use this diagram for a pin reference.

#### Wiring
Second, wire the Uno to an Arduino Micro using the ICSP connector. Two pins require special treatment.
 1. The reset pin needs to be connected to pin 10 of the Uno to avoid a reset loop while programming.
 1. Since the goal is to keep the target plugged into the switch while reprogramming, do not connect the 5v line. This is needed to flash without connecting to a switch, but if it is connected the boards must share a common ground plane while providing the 5v supply separately.
 
 
![icsp_pinout](https://user-images.githubusercontent.com/8355718/79698237-7de48b80-823c-11ea-9c2d-949cc400f97b.png)

Make the following connections (for reference [Uno pinout](https://user-images.githubusercontent.com/8355718/79698968-2e548e80-8241-11ea-930e-0c57a3cede80.jpg), [Micro pinout](https://user-images.githubusercontent.com/8355718/79698970-314f7f00-8241-11ea-8120-758758949b9d.jpg)):
 - Programmer ICSP MISO -> Target ICSP MISO
 - Programmer ICSP SCK -> Target ICSP SCK
 - Programmer D10 -> Target ICSP RESET (special case 1)
  - Programmer ICSP GND -> Target ICSP GND
 - Programmer ICSP MOSI -> Target ICSP MOSI
 - Programmer ICSP 5V -> Target ICSP 5V (special case 2)

> Remember to disconnect power when connected to a switch or it will not recognize the device after it is programmed.

##### Configure the Uno as an ISP
First, prepare the Uno to act as an ISP. Note, this sketch can drive debug LEDs on digital output pins 7 (data), 8 (error), 9 (heartbeat). It is not necessary to use this feature, but it can help with debugging.
 1. Open the example sketch named ArduinoISP (File -> Examples -> ArduinoISP).
 1. Select the Uno as target board (Tools -> Board -> "Aruino Uno")
 1. Select the correct port (Tools -> Port -> ...).
 1. Upload the sketch.

#### Flash bootloader
This prepares the bootloader in the Arduino Micro to receive programs through the ICSP connector.
 1. While leaving the Uno connected, select Micro as the target board (Tools -> Board -> "Aruino Micro")
 1. Use the same port that was used previously
 1. Select the Aduino as ISP programmer (Tools -> Programmer -> "Arduino as ISP").
 1. Flash the bootloader (Tools -> Burn Bootloader). This should take about 30s.
 
#### Verify ICSP programming
Flash the blink program to the board (enable verbose output for uploads to see the AVR commands used, in case `flash_isp.sh` needs updated paths).
 1. Open the blink example sketch (File -> Examples -> 01. Basics -> Blink). Other scripts can be closed.
 1. Using the same configuration (Tools -> Board -> "Arudino Micro", same port)
 1. Upload the sketch to the micro (Sketch -> Upload Using Programmer)

#### Thanks

Thanks to Shiny Quagsire for his [Splatoon post printer](https://github.com/shinyquagsire23/Switch-Fightstick) and progmem for his [original discovery](https://github.com/progmem/Switch-Fightstick).

Thanks to [exsilium](https://github.com/bertrandom/snowball-thrower/pull/1) for improving the command structure, optimizing the waiting times, and handling the failure scenarios. It can now run indefinitely!

Thanks to Nick Gammon for his post on using Arduino as an [Atmega bootloader programmer](https://www.gammon.com.au/bootloader).
