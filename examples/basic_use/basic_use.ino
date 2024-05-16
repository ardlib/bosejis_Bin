/**
 * Advance Usage Example.
 *
 * बोसजी की द्विवर्ण आधारित लाइब्रेरी
 * ===============================
 * सहज एवं अति उपयोगी द्विवर्ण आधारित रचना।
 *
 * एक रचनात्मक भारतीय उत्पाद।
 *
 * Boseji's Bin Library
 * (Easy to use Binary I/O.)
 *
 * Sources
 * -------
 * https://github.com/ardlib/bosejis_Bin
 *
 * License
 * --------
 * SPDX: GPL-3.0-or-later
 *
 *  bosejis_Bin - Boseji's Bin Library.
 *  Copyright (C) 2024 by Abhijit Bose (aka. Boseji)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <bosejis_Bin.h>
#include <bosejis_PString.h>

// Defines
#define SEPARATOR(X)                                                           \
  Serial.println(F("\n----------------------------------------------------")); \
  Serial.println(F(X))

// Globals
#define STR_BUF 200
char raw_str[STR_BUF];
PString str(raw_str, STR_BUF);

// Functions
void Test_Basic();

void setup() {
  Serial.begin(115200);
  while (!Serial) {
  }
  delay(1000);
}

void loop() {
  Test_Basic();
  delay(2000);
}

#define PrintBin(b)                                                            \
  str.begin();                                                                 \
  str.format(" len: %-2d cap: %-2d Buffer: ", b.length(), b.capacity());       \
  str.HexBuffer(b.Bytes(), b.length());                                        \
  Serial.println(str);                                                         \
  b.flush()

#define PrintValue(PRINT, VAL)                                                 \
  str.begin();                                                                 \
  str.print(F(PRINT));                                                         \
  str.print(VAL);                                                              \
  str.print(F(" = 0x"));                                                       \
  str.Hex(VAL);                                                                \
  Serial.println(str)

#define PrintValueLarge(PRINT, VAL)                                            \
  str.begin();                                                                 \
  str.print(F(PRINT));                                                         \
  str.print(F(" 0x"));                                                         \
  str.Hex(VAL);                                                                \
  Serial.println(str)

void Test_Basic() {
#define BUF_TEST_BASIC 50
  uint8_t raw[BUF_TEST_BASIC];
  Bin b(raw, BUF_TEST_BASIC);

  SEPARATOR("Basic Features of Bin Class");

  Serial.println(F("\n Initial Buffer:"));
  PrintBin(b);

  PrintValue("\n uint16_t ", (uint16_t)0x1234);
  if (!b.write((uint16_t)0x1234))
    return;
  PrintBin(b);

  PrintValue("\n int16_t ", (int16_t)-1234);
  if (!b.write((int16_t)-1234))
    return;
  PrintBin(b);

  PrintValue("\n int32_t ", (int32_t)-1234567890);
  if (!b.write((int32_t)-1234567890))
    return;
  PrintBin(b);

  PrintValueLarge("\n int64_t ", (int64_t)-1234567890123456789);
  if (!b.write((int64_t)-1234567890123456789))
    return;
  PrintBin(b);

  PrintValueLarge("\n float ", (float)3.14159);
  if (!b.write((float)3.14159))
    return;
  PrintBin(b);

  PrintValueLarge("\n double ", (double)3.14159265358979);
  if (!b.write((double)3.14159265358979))
    return;
  PrintBin(b);
}