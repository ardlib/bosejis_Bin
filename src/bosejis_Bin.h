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

#include <WString.h>
#if defined(__AVR__) || defined(ARDUINO_ARCH_SAMD) ||                          \
    defined(ARDUINO_ARCH_RP2040)
#include <inttypes.h>
#elif defined(ARDUINO_ARCH_ESP32) || defined(ESP8266)
#include <stdint.h>
#else
#error "Unknown Architecture to Boseji's Bin Library"
#endif

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

class Bin {
private:
  uint8_t *_buf, *_cur;
  size_t _size;

public:
  // Basic constructor requires a preallocated buffer
  Bin(uint8_t *buf, size_t size) : _buf(buf), _size(size) { begin(); }
  Bin(char *buf, size_t size) : _buf((uint8_t *)buf), _size(size) { begin(); }

  // call this to re-use an existing Buffer without cleaning up
  void begin();

  // returns the length of the current string, not counting the 0 terminator
  inline size_t length() { return _cur - _buf; }

  // returns the capacity of the string
  inline size_t capacity() { return _size; }

  // gives access to the internal string
  inline operator uint8_t *() { return _buf; }
  inline uint8_t *Bytes() { return _buf; }

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
  size_t write(const char *b, bool withTermination = false);
  size_t write(const String &s, bool withTermination = false);
  size_t write(const __FlashStringHelper *ifsh, bool withTermination = false);

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
};

#endif /* bosejis_Bin_h */