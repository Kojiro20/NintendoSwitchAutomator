# Animal Crossing Nintendo Switch Automator

![animal crossing automation](https://user-images.githubusercontent.com/72478718/100486931-e09fde80-30cb-11eb-8111-6655a082b230.gif)

## Pre-reqs
1) Clone this repo (with `--recurse-submodules`)
   ```bash
   git clone --recurse-submodules git@github.com:<>.git
   ```

2) Ensure lufa was cloned (`make` will fail otherwise)
   ```bash
   # from project root
   git clone https://github.com/abcminiuser/lufa.git
   ```
  
3) Install Arduino IDE https://www.arduino.cc/en/Main/Software

4) Obtain hardware
    - [Arduino Micro](https://www.amazon.com/dp/B00AFY2S56)
    - [Micro USB to USB C cable](https://www.amazon.com/dp/B0744BKDRD) (to connect Arduino to Nintendo Switch)
    - [Breadboard Kit](https://www.amazon.com/dp/B01ERPEMAC)
    - 10kΩ resistor (included in kit)
    - Wires  (included in kit)
    - Push button  (included in kit)

5) Attach the push button to the Arduino Micro according to the following diagram:
![arduino_micro_fritzing](https://user-images.githubusercontent.com/72478718/100475856-c05f2800-30a9-11eb-9a83-1cccae4d495f.png)

## Compiling and Flashing onto the Arduino Micro

### Mac

1) Get AVR tool chain
  ```bash
  brew tap osx-cross/avr
  brew install avr-gcc
  ```

2) Build and flash (tap the button twice to put it into flash mode)
  ```bash
  # from project root
  make && ./flash.sh
  ```

## How to use

You can modify which programs are installed onto the Arduino Micro by opening the `scripts/runner.c` file and adjusting the `InitializeGameScripts` function.

Plug in the Arduino to the Switch by using the micro USB to USB C cable. It will automatically be detected and no setup is needed and the blue light on the Arduino should turn on to indicate it has power.

Use the button (the one that's separately attached, the one directly on the Arduino is a reset button) to select which program to run. 1 button press will run the first program, 2 button presses will run the second program, etc. The delay in between button presses needs to be just right, about 1 second, you can't press too fast or too slow! Then, wait a couple of seconds and the orange light on the Arduino will turn on, which indicates a program is running. When the orange light is on, you can press the reset button to stop running the program, and the light will turn off. Note that after a program "ends" (if it's not an infinitely looping program), the orange light will still be on, so if you want to start another program, you need to reset before picking a new program.

### Tips for each program

- ShakeTreeAndCollect: Start by standing to the tree's right side and face left. Your character may drift slightly over time, so you should place some objects to block yourself in, like:
  ```
     B
  XXOYB
  XXX
  XXX
  O = tree, X = shaken items, Y = you, B = blockage
  ```
- WishStars: This will automatically keep looking up, so it keeps working when people are entering or leaving the island. To prevent villagers from talking to you accidentally, block yourself in (i.e. with holes).
- HitRock: Start from the bottom left corner of the rock.
  ```
  Starting position:
  
    R
  OX
   O
  
  R = rock
  X = you (facing any direction)
  O = hole/obstruction
  ```
- Clone1x1Items / Sell40ItemsNTimes / CloneAndSell80Items: see the comments in `scripts/AnimalCrossing/glitch.c` file for instructions
- BuyBulk: Have your cursor on the item you want to buy. This will buy that item in bulk until your backpack is full (60 times).
- SelectBulk: When your inventory is open and you can multi-select items, this will select every item. Useful for selling entire inventory to Nook Shop.
- MysteryIsland: Stand in front of the dodo, don't talk to him yet, and then start the program. Make sure you have a nook miles ticket in your bag.
- OpenGate: Will stop at the option to choose dodo code or all your friends. Stand in front of the dodo, don't talk to him yet, and then start the program. Make sure you don't have a nook miles ticket in your bag.
- Travel: Will stop at the option to choose dodo code or check friends. Stand in front of the dodo, don't talk to him yet, and then start the program.

## Thanks

Thanks to Shiny Quagsire for his [Splatoon post printer](https://github.com/shinyquagsire23/Switch-Fightstick) and progmem for his [original discovery](https://github.com/progmem/Switch-Fightstick).

Thanks to [exsilium](https://github.com/bertrandom/snowball-thrower/pull/1) for improving the command structure, optimizing the waiting times, and handling the failure scenarios. It can now run indefinitely!

Thanks to Nick Gammon for his post on using Arduino as an [Atmega bootloader programmer](https://www.gammon.com.au/bootloader).
