#!/usr/bin/env bash

set -e

# test-qtpy-m0.sh - Flash Example to Adafruit QT Py M0 (SAMD21)
#
# बोसजी की द्विवर्ण आधारित लाइब्रेरी
# ===============================
# सहज एवं अति उपयोगी द्विवर्ण आधारित रचना।
#
# एक रचनात्मक भारतीय उत्पाद।
#
# Boseji's Bin Library
# (Easy to use Binary I/O.)
#
# Sources
# -------
# https://github.com/ardlib/bosejis_Bin
#
# License
# --------
# SPDX: GPL-3.0-or-later
#
#  bosejis_Bin - Boseji's Bin Library.
#  Copyright (C) 2024 by Abhijit Bose (aka. Boseji)
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <https://www.gnu.org/licenses/>.

arduino-cli cache clean
# Compile for Adafruit QT Py M0 (SAMD21)
arduino-cli compile -v --fqbn adafruit:samd:adafruit_qtpy_m0 examples/basic_use
# Flashing
arduino-cli upload -p /dev/ttyACM1 -v --fqbn adafruit:samd:adafruit_qtpy_m0 \
	examples/basic_use
