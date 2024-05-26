# बोसजी की द्विवर्ण आधारित लाइब्रेरी

> सहज एवं अति उपयोगी द्विवर्ण आधारित रचना।

> ***एक रचनात्मक भारतीय उत्पाद।***

## Boseji's Bin Library

> (Easy to use Binary I/O.)

- Buffer Write interface
- Floating and Double number writing and `sprintf` to Buffer
- Buffer reuse and Reassignment
- Both String and Binary output interfaces
- Explicit zeroing of Buffer
- Hex Writer with support for Arrays and External buffers
- Byte trimming functions support
- Buffer RAW data read support
- Hex Decoding support

## Installation

### Using [Zip File](https://github.com/ardlib/bosejis_Bin/archive/refs/heads/main.zip) from this repository

Downloading the Zip file of this repository from :

<https://github.com/ardlib/bosejis_Bin/archive/refs/heads/main.zip>

And installing using the **Add .ZIP Library** feature:

- For **Arduino IDE 1.8.19** and above:
    
    Go to Menu `Sketch -> Include Library -> Add .ZIP Library`

## Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell others about this library
- Contribute new Types

Please read [CONTRIBUTING.md](https://github.com/ardlib/bosejis_Bin/blob/master/CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

### `arduino-cli` Usage Details

```sh
# Compile for ESP32 (DOIT DEV KIT V1)
arduino-cli compile --fqbn esp32:esp32:esp32doit-devkit-v1 examples/basic_use
# Flashing
arduino-cli upload -p /dev/ttyUSB0 -v --fqbn esp32:esp32:esp32doit-devkit-v1 \
    examples/basic_use

# Compile for Arduino Uno
arduino-cli compile --fqbn arduino:avr:uno examples/basic_use
# Flashing
arduino-cli upload -p /dev/ttyUSB0 -v --fqbn arduino:avr:uno \
    examples/basic_use
```

## License

`SPDX: GPL-3.0-or-later`

`bosejis_Bin` - Boseji's Bin Library.

Copyright (C) 2024 by Abhijit Bose (aka. Boseji)

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.