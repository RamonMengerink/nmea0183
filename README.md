# Serial Communication with LCD Display

## Description

This Arduino sketch demonstrates serial communication between two devices using the Serial library. It is designed to work with an LCD display driven by the `LCDWIKI_KBV` library.

## Requirements

- Arduino MEGA 2560 board
- LCD display compatible with the `LCDWIKI_KBV` library
- Button connected between pin D53 and GND
- Serial input connected to Serial1 (RX1 D19, TX1 D18 on Arduino Mega 2560)

## Installation

1. Download and install the `LCDWIKI_KBV` library.
2. Connect the LCD display to the Arduino board.
3. Connect a button between pin D53 and GND of the Arduino board.
4. Connect UART signal to pin D19, make sure it potential is between 0V and 5V TTL use MAX3232 IC to convert if needed

## Usage

1. Upload the sketch to your Arduino board.
2. Press the button connected to pin 53 to cycle through different baud rates for `Serial1`.
3. Monitor the serial input on the screen
4. (optional) connect D16 `Serial2` to D19 to observe the data being sent from the Arduino for testing purpose. 

## Pin Configuration

- LCD display:
  - CS: A3
  - CD: A2
  - WR: A1
  - RD: A0
  - Reset: A4

- Button: 53
- Serial 1 input: 19

## Authors

Ramon Mengerink

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
