/**
 * bosejis_Bin.h - Easy to use Binary I/O.
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
#ifndef bosejis_Bin_h
#define bosejis_Bin_h

#if defined(ARDUINO_ARCH_RP2040)
#include <api/String.h>
using namespace arduino;
#else
#include <WString.h>
#endif

#include <inttypes.h>
#include <stdint.h>

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Compatibility for dtostrf */
#if defined(ARDUINO_ARCH_ESP32)
#include <stdlib_noniso.h>
#elif defined(__AVR__)
// STDLIB is already included
#else
#include <avr/dtostrf.h>
#endif

class Bin {
private:
  uint8_t *_buf, *_cur;
  size_t _size;

public:
  // Basic constructor requires a preallocated buffer
  Bin(uint8_t *buf, size_t size) : _buf(buf), _size(size) { begin(); }
  Bin(char *buf, size_t size)
      : _buf(reinterpret_cast<uint8_t *>(buf)), _size(size) {
    begin();
  }

  // call this to re-use an existing Buffer without cleaning up
  void begin();

  // returns the length of the current string, not counting the 0 terminator
  inline size_t length() { return _cur - _buf; }

  // returns the capacity of the string
  inline size_t capacity() { return _size; }

  // gives access to the internal string
  inline operator uint8_t *() { return _buf; }
  inline operator char *() {
    if (length() > 0 && (!isString()))
      tostr();
    return reinterpret_cast<char *>(_buf);
  }
  inline uint8_t *Bytes() { return _buf; }
  inline const char *c_str() {
    if (length() > 0 && (!isString()))
      tostr();
    return reinterpret_cast<const char *>(_buf);
  }

  // Clean up the Buffer and Reset it for re-use
  void flush();

  // Binary Writer Functions

  size_t write(uint8_t);
  size_t write(char);
  size_t write(int8_t);
  size_t write(bool);
  size_t write(uint16_t);
  size_t write(int16_t);
  size_t write(uint32_t);
  size_t write(int32_t);
  size_t write(uint64_t);
  size_t write(int64_t);
  size_t write(float);
  size_t write(double);
  size_t write(uint8_t *, size_t);
  size_t write(char *, size_t);
  size_t write(const char *b);
  size_t write(const String &s);
  size_t write(const __FlashStringHelper *ifsh);

  // This function allows assignment to an arbitrary scalar value like
  //    str = myfloat;
  template <class T> inline Bin &operator=(T arg) {
    begin();
    write(arg);
    return *this;
  }

  // Concatenation of any type data
  //    str += myfloat;
  template <class T> inline Bin &operator+=(T arg) {
    write(arg);
    return *this;
  }

  // Safe access to sprintf-like formatting,
  // e.g. str.format("Hi, my name is %s and I'm %d years old", name, age);
  size_t sprintf(const char *str, ...);

  // Friendly use of dtostrf
  // dtostrf (double __val, signed char __width,
  //          unsigned char __prec, char *__s)

  size_t strfloat(float b, int8_t min_width, uint8_t num_digits_after_decimal);
  size_t strdouble(double b, int8_t min_width,
                   uint8_t num_digits_after_decimal);

  // This just String Terminates the Bin
  size_t tostr();

  // Print Hex value to the String

  size_t Hex(uint8_t data);
  size_t Hex(char data);
  size_t Hex(uint16_t data);
  size_t Hex(int16_t data);
  size_t Hex(uint32_t data);
  size_t Hex(int32_t data);
  size_t Hex(uint64_t data);
  size_t Hex(int64_t data);
  size_t Hex(bool data);
  size_t Hex(float data);
  size_t Hex(double data);
  template <class T> inline size_t Hex(T *arg) {
    // Print the Memory Address
    return Hex(reinterpret_cast<uint64_t>(arg));
  }

  // Print a Hex Buffer
  template <class T> inline size_t HexBuffer(T *arg, size_t size) {
    size_t ret = 0;
    if (size == 0) {
      return write(F("Empty!"));
    }
    for (size_t i = 0; i < size; i++) {
      ret += Hex(arg[i]);
    }
    return ret;
  }

  // Print a Hex Buffer like C Array
  template <class T> inline size_t HexArray(T *arg, size_t size) {
    size_t ret = 0;
    for (size_t i = 0; i < size; i++) {
      ret += write(F(" 0x"));
      ret += Hex(arg[i]);
      if (i < (size - 1)) {
        ret += write(',');
      }
    }
    return ret;
  }

  // Trim few bytes from the Left Side - returns the bytes removed
  size_t trimLeft(size_t);
  // Trim few bytes from the Right Side - returns the bytes removed
  size_t trimRight(size_t);

  // Returns true if the Bin is indeed Null terminated
  bool isString();

  // Trims off the Null termination at the end - Return the New size
  size_t trim();

  // Read functions to Decode the Stored values - Returns size of value read
  // in bytes.

  size_t read(uint8_t *); // One byte Read not the Whole array.
  size_t read(char *);
  size_t read(int8_t *);
  size_t read(bool *);
  size_t read(uint16_t *);
  size_t read(int16_t *);
  size_t read(uint32_t *);
  size_t read(int32_t *);
  size_t read(uint64_t *);
  size_t read(int64_t *);
  size_t read(float *);
  size_t read(double *);
  size_t read(uint8_t *, size_t); // Here the size is minimum possible
  size_t read(char *, size_t);
};

#endif /* bosejis_Bin_h */