/**
 * Basic Usage Example.
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

// Functions
void Test_Basic();
void Test_Operator();
void Test_Sprintf();
void Test_fdprint();
void Test_Trim();
void Test_Read();
void Test_UnHex();

void setup() {
  Serial.begin(115200);
  while (!Serial) {
  }
  delay(1000);
}

void loop() {
  Test_Basic();
  delay(2000);
  Test_Operator();
  delay(2000);
  Test_Sprintf();
  delay(2000);
  Test_fdprint();
  delay(2000);
  Test_Trim();
  delay(2000);
  Test_Read();
  delay(2000);
  Test_UnHex();
  delay(2000);
}

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
  str.sprintf("%d", VAL);                                                      \
  str.write(F(" = 0x"));                                                       \
  str.Hex(VAL);                                                                \
  Serial.println(str)

#define PrintValueLarge(PRINT, VAL)                                            \
  str.begin();                                                                 \
  str.write(F(PRINT));                                                         \
  str.write(F(" 0x"));                                                         \
  str.Hex(VAL);                                                                \
  Serial.println(str)

#define PrintValueString(PRINT, VAL)                                           \
  str.begin();                                                                 \
  str.write(F(PRINT));                                                         \
  str.write(F("\'"));                                                          \
  str.write(VAL);                                                              \
  str.write(F("\' = 0x"));                                                     \
  str.HexBuffer(VAL, strlen(VAL));                                             \
  Serial.println(str)

#define PrintValueArray(PRINT, ARR, SZ)                                        \
  str.begin();                                                                 \
  str.write(F(PRINT));                                                         \
  str.write(F("["));                                                           \
  str.sprintf("%d", SZ);                                                       \
  str.write(F("] = "));                                                        \
  str.HexArray(ARR, SZ);                                                       \
  Serial.println(str)

#define PrintBinAsString(b)                                                    \
  PrintBinNoFlush(b);                                                          \
  Serial.print(F(" Raw Buffer as String:\n "));                                \
  Serial.println(b);                                                           \
  b.flush()

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

  PrintValueLarge("\n int64_t (-1234567890123456789) ",
                  (int64_t)-1234567890123456789);
  if (!b.write((int64_t)-1234567890123456789))
    return;
  PrintBin(b);

  PrintValueLarge("\n float (3.14159) ", (float)3.14159);
  if (!b.write((float)3.14159))
    return;
  PrintBin(b);

  PrintValueLarge("\n double (3.14159265358979) ", (double)3.14159265358979);
  if (!b.write((double)3.14159265358979))
    return;
  PrintBin(b);

  PrintValue("\n bool ", true);
  if (!b.write(true))
    return;
  PrintBin(b);

  do {
    uint8_t data[5] = {0x12, 0x34, 0x56, 0x78, 0x90};
    PrintValueArray("\n uint8_t* ", data, 5);
    if (!b.write(data, 5))
      return;
    PrintBin(b);
  } while (0);

  do {
    char data[5] = {"Hari"};
    PrintValueArray("\n char* ", data, 5);
    if (!b.write(data, 4))
      return;
    PrintBinAsString(b);
  } while (0);

  PrintValueString("\n const char* ", "Hari Aum!");
  if (!b.write("Hari Aum!"))
    return;
  PrintBinAsString(b);

  String s = "Aum Namh Shivay!";
  PrintValueString("\n String ", s.c_str());
  if (!b.write(s))
    return;
  PrintBinAsString(b);

  PrintValueString("\n F(String) ", "Hare Krishna!");
  if (!b.write(F("Hare Krishna!")))
    return;
  PrintBinAsString(b);
}

void Test_Operator() {
#define BUF_TEST_OPR 50
  uint8_t raw[BUF_TEST_OPR];
  Bin b(raw, BUF_TEST_OPR);

  SEPARATOR("Operator Features of Bin Class");

  PrintValue("\n = uint16_t ", (uint16_t)0x1234);
  b = (uint16_t)0x1234;
  PrintBin(b);

  PrintValue("\n = int32_t ", (int32_t)-1234567890);
  b = (int32_t)-1234567890;
  PrintBinNoFlush(b);

  PrintValueString("\n += F(String) ", "Hare Krishna!");
  b += F("Hare Krishna!");
  PrintBin(b);
}

void Test_Sprintf() {
#define BUF_TEST_SPF 50
  uint8_t raw[BUF_TEST_SPF];
  Bin b(raw, BUF_TEST_SPF);

  SEPARATOR("Sprintf Features of Bin Class");

  PrintValue("\n sprintf with '-6d' on uint16_t ", (uint16_t)0x1234);
  if (!b.sprintf("'%-6d'", (uint16_t)0x1234))
    return;
  PrintBinAsString(b);
  Serial.println();
}

void Test_fdprint() {
#define BUF_TEST_FD 50
  uint8_t raw[BUF_TEST_FD];
  Bin b(raw, BUF_TEST_FD);

  SEPARATOR("Float and Double Print Features of Bin Class");

  PrintValueLarge("\n float (3.14159)", (float)3.14159);
  if (!b.strfloat(3.14159, 7, 5))
    return;
  PrintBinAsString(b);

  PrintValueLarge("\n double (3.14159265358979)", (double)3.14159265358979);
  if (!b.strdouble(3.14159265358979, 17, 14))
    return;
  PrintBinAsString(b);
}

void Test_Trim() {
#define BUF_TEST_TRIM 50
  uint8_t raw[BUF_TEST_TRIM];
  Bin b(raw, BUF_TEST_TRIM);

  SEPARATOR("Trim Features of Bin Class");

  do {
    uint8_t data[5] = {0x12, 0x34, 0x56, 0x78, 0x90};
    PrintValueArray("\n Added uint8_t* ", data, 5);
    if (!b.write(data, 5))
      return;
    PrintBinNoFlush(b);
    Serial.println(F(" Trimming 3 Bytes from the Left"));
    if (b.trimLeft(3) != 3)
      return;
    PrintBin(b);
  } while (0);

  do {
    uint8_t data[5] = {0x12, 0x34, 0x56, 0x78, 0x90};
    PrintValueArray("\n Added uint8_t* ", data, 5);
    if (!b.write(data, 5))
      return;
    PrintBinNoFlush(b);
    Serial.println(F(" Trimming 2 Bytes from the Right"));
    if (b.trimRight(2) != 2)
      return;
    PrintBin(b);
  } while (0);

  do {
    char data[5] = {"Hari"};
    PrintValueArray("\n char* ", data, 5);
    if (!b.write(data, 4))
      return;
    PrintBinNoFlush(b);
    Serial.print(F(" Raw Buffer as String:\n "));
    Serial.println(b);
    Serial.print(F(" Is String: "));
    Serial.println(b.isString());
    PrintBinNoFlush(b);
    Serial.print(F(" Trim the String - "));
    Serial.println(b.trim());
    PrintBin(b);
  } while (0);
}

void Test_Read() {
#define BUF_TEST_READ 50
  uint8_t raw[BUF_TEST_READ];
  Bin b(raw, BUF_TEST_READ);

  SEPARATOR("Read Features of Bin Class");

  do {
    uint8_t data = 0;
    Serial.println(F("\n Writing (uint8_t)0x21 to Bin"));
    if (!b.write((uint8_t)0x21))
      return;
    PrintBinNoFlush(b);
    if (!b.read(&data))
      return;
    PrintValue(" Read Back: ", data);
    PrintBin(b);
  } while (0);

  do {
    char data = 0;
    Serial.println(F("\n Writing (char)'P' to Bin"));
    if (!b.write((char)'P'))
      return;
    PrintBinNoFlush(b);
    if (!b.read(&data))
      return;
    PrintValue(" Read Back: ", data);
    Serial.print(F(" Value in Char: "));
    Serial.println(data);
    PrintBin(b);
  } while (0);

  do {
    int16_t data = 0;
    Serial.println(F("\n Writing (int16_t)-1234 to Bin"));
    if (!b.write((int16_t)-1234))
      return;
    PrintBinNoFlush(b);
    if (!b.read(&data))
      return;
    PrintValue(" Read Back: ", data);
    PrintBin(b);
  } while (0);

  do {
    int32_t data = 0;
    Serial.println(F("\n Writing (int32_t)-1234567890 to Bin"));
    if (!b.write((int32_t)-1234567890))
      return;
    PrintBinNoFlush(b);
    if (!b.read(&data))
      return;
    PrintValue(" Read Back: ", data);
    PrintBin(b);
  } while (0);

  do {
    int64_t data = 0;
    Serial.println(F("\n Writing (int64_t)-1234567890123456789 to Bin"));
    if (!b.write((int64_t)-1234567890123456789))
      return;
    PrintBinNoFlush(b);
    if (!b.read(&data))
      return;
    PrintValueLarge(" Read Back: ", data);
    // Serial.print(F(" Actual Value: "));
    // Serial.println(data);
    PrintBin(b);
  } while (0);

  do {
    float data = 0;
    Serial.println(F("\n Writing (float)3.14159 to Bin"));
    if (!b.write((float)3.14159))
      return;
    PrintBinNoFlush(b);
    if (!b.read(&data))
      return;
    Serial.print(F(" Actual Value: "));
    Serial.println(data, 7);
    PrintBin(b);
  } while (0);

  do {
    double data = 0;
    Serial.println(F("\n Writing (double)3.14159265358979 to Bin"));
    if (!b.write((double)3.14159265358979))
      return;
    PrintBinNoFlush(b);
    if (!b.read(&data))
      return;
    str.begin();
    str.write(F(" Actual Value: "));
    str.strdouble(data, 17, 14);
    Serial.println(str);
    PrintBin(b);
  } while (0);

  do {
    uint8_t dataIn[5] = {0x12, 0x34, 0x56, 0x78, 0x90};
    uint8_t dataOut[5];
    PrintValueArray("\n Added uint8_t[5] ", dataIn, 5);
    if (!b.write(dataIn, 5))
      return;
    PrintBinNoFlush(b);
    if (!b.read(dataOut, 5))
      return;
    PrintValueArray(" Data Read Back: ", dataOut, 5);
    PrintBin(b);
  } while (0);

  do {
    char data[6];
    Serial.println(F("\n Writing (String)'Hari' to Bin"));
    if (!b.write("Hari"))
      return;
    PrintBinNoFlush(b);
    // 1 Byte Extra for Null termination
    if (!b.read(data, strlen("Hari") + 1))
      return;
    PrintValueString(" Read Back: ", data);
    PrintBin(b);
  } while (0);
}

void Test_UnHex() {
#define BUF_TEST_UN 50
  uint8_t raw[BUF_TEST_UN];
  Bin b(raw, BUF_TEST_UN);

  SEPARATOR("UnHex Features of Bin Class");

  PrintValueString("\n Hex Stream 1: ", "1234567890");
  if (!b.unHex((char *)"1234567890"))
    return;
  PrintBin(b);

  PrintValueString("\n Hex Stream 2: ", "123456789");
  if (!b.unHex((char *)"123456789"))
    return;
  PrintBin(b);

  PrintValueString("\n Hex Stream 3: ", "A1cfDfeD");
  if (!b.unHex((char *)"A1cfDfeD"))
    return;
  PrintBin(b);

  PrintValueString("\n Hex Stream 4: ", "A12-315");
  if (!b.unHex((char *)"A12-315"))
    return;
  PrintBin(b);

  PrintValueString("\n Hex Stream 5: ", "Bin is a good lib 5 stars.");
  if (!b.unHex((char *)"Bin is a good lib 5 stars."))
    return;
  PrintBin(b);
}