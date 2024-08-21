/**
 * Special Usage Example.
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

// Defines
#define SEPARATOR(X)                                                           \
  Serial.println(F("\n----------------------------------------------------")); \
  Serial.println(F(X))

// Globals
#define STR_BUF 200
char raw_str[STR_BUF];
Bin str(raw_str, STR_BUF);

// Special Type
typedef struct mydata {
  float value;
  uint16_t id;
} mydata_t;

// Type Related Custom Functions

size_t mydata_read(mydata_t *md, Bin &b);
size_t mydata_write(mydata_t *md, Bin &b);
size_t mydata_Hex(mydata_t *md, Bin &b);

// Test functions

void TestBasic(void);
void TestHex(void);

void setup() {
  Serial.begin(115200);
  while (!Serial) {
  }
  delay(1000);
}

void loop() {
  Test_Basic();
  delay(2000);
  TestHex();
  delay(2000);
}

//---------------------------------------------------------------------------
// Type Related Custom Functions

size_t mydata_read(mydata_t *md, Bin *b) {
  size_t ret = 0, sz = 0;
  // From the End
  ret = b->read(&md->id);
  if (ret == 0)
    return 0;
  sz += ret; // Update the actual size
  ret = b->read(&md->value);
  if (ret == 0)
    return 0;
  // Return the Total Size Read back
  return sz + ret;
}

size_t mydata_write(mydata_t *md, Bin *b) {
  size_t ret = 0, sz = 0;
  ret = b->write(md->value);
  if (ret == 0)
    return 0;
  sz += ret; // Update the actual size
  ret = b->write(md->id);
  if (ret == 0)
    return 0;
  // Return the Total Size Written
  return sz + ret;
}

size_t mydata_Hex(mydata_t *md, Bin *b) {
  size_t ret = 0, sz = 0;
  ret = b->Hex(md->value);
  if (ret == 0)
    return 0;
  sz += ret; // Update the actual size
  ret = b->Hex(md->id);
  if (ret == 0)
    return 0;
  // Return the Total Size Written
  return sz + ret;
}

//---------------------------------------------------------------------------
#define PrintBin(b)                                                            \
  str.begin();                                                                 \
  str.sprintf(" len: %-2d cap: %-2d Buffer: ", b.length(), b.capacity());      \
  str.HexBuffer(b.Bytes(), b.length());                                        \
  Serial.println(str);                                                         \
  b.flush()

#define PrintBinNoFlush(b)                                                     \
  str.begin();                                                                 \
  str.sprintf(" len: %-2d cap: %-2d Buffer: ", b.length(), b.capacity());      \
  str.HexBuffer(b.Bytes(), b.length());                                        \
  Serial.println(str)

#define PrintValue(PRINT, VAL)                                                 \
  str.begin();                                                                 \
  str.write(F(PRINT));                                                         \
  str.Hex(VAL.value);                                                          \
  str.write(F(" ,"));                                                          \
  str.Hex(VAL.id);                                                             \
  str.write(F("}"));                                                           \
  Serial.println(str)

#define PrintBinAsString(b)                                                    \
  PrintBinNoFlush(b);                                                          \
  Serial.print(F(" Raw Buffer as String:\n "));                                \
  Serial.println(b);                                                           \
  b.flush()

void Test_Basic(void) {
#define BUF_TEST_BASIC 50
  uint8_t raw[BUF_TEST_BASIC];
  Bin b(raw, BUF_TEST_BASIC);

  SEPARATOR("Basic Operations on the custom Data-type with Bin Class");

  Serial.println(F("\n Initial Buffer:"));
  PrintBin(b);

  do {
    // Setup the Custom Data Type
    mydata_t md, md2;
    md.value = 22.7;
    md.id = 178;

    PrintValue("\n mydata_t{ 0x", md);
    if (!b.write(md, mydata_write))
      return;
    // PrintBin(b);
    PrintBinNoFlush(b);

    // b.unHex("9a99b541b200");

    if (!b.read(&md2, mydata_read))
      return;
    PrintValue("\n Read Back mydata_t{ 0x", md2);
    PrintBin(b);

  } while (0);
}

void TestHex(void) {
#define BUF_TEST_HEX 50
  uint8_t raw[BUF_TEST_HEX];
  Bin b(raw, BUF_TEST_HEX);

  SEPARATOR("Hex Operations on the custom Data-type with Bin Class");

  Serial.println(F("\n Initial Buffer:"));
  PrintBin(b);

  do {
    // Setup the Custom Data Type
    mydata_t md;
    md.value = 22.7;
    md.id = 178;

    PrintValue("\n mydata_t{ 0x", md);
    if (!b.Hex(md, mydata_Hex)) {
      return;
    }
    PrintBinAsString(b);
  } while (0);
}
