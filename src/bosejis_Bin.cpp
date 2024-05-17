/**
 * bosejis_Bin.cpp - Easy to use Binary I/O.
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

#include "bosejis_Bin.h"

void Bin::begin() { _cur = _buf; }

void Bin::flush() {
  memset(_buf, 0, _size);
  begin();
}

size_t Bin::write(uint8_t b) {
  if (_cur < (_buf + _size)) {
    *_cur++ = b;
    return 1;
  }
  return 0;
}

size_t Bin::write(char b) { return write(static_cast<uint8_t>(b)); }

size_t Bin::write(int8_t b) { return write(static_cast<uint8_t>(b)); }

size_t Bin::write(bool b) { return write(static_cast<uint8_t>(b)); }

size_t Bin::write(uint16_t b) {
  if ((_cur + sizeof(b)) < (_buf + _size)) {
    memcpy(_cur, &b, sizeof(b));
    _cur += sizeof(b);
    return sizeof(b);
  }
  return 0;
}

size_t Bin::write(int16_t b) { return write(static_cast<uint16_t>(b)); }

size_t Bin::write(uint32_t b) {
  if ((_cur + sizeof(b)) < (_buf + _size)) {
    memcpy(_cur, &b, sizeof(b));
    _cur += sizeof(b);
    return sizeof(b);
  }
  return 0;
}

size_t Bin::write(int32_t b) { return write(static_cast<uint32_t>(b)); }

size_t Bin::write(uint64_t b) {
  if ((_cur + sizeof(b)) < (_buf + _size)) {
    memcpy(_cur, &b, sizeof(b));
    _cur += sizeof(b);
    return sizeof(b);
  }
  return 0;
}

size_t Bin::write(int64_t b) { return write(static_cast<uint64_t>(b)); }

size_t Bin::write(float b) {
  if ((_cur + sizeof(b)) < (_buf + _size)) {
    memcpy(_cur, &b, sizeof(b));
    _cur += sizeof(b);
    return sizeof(b);
  }
  return 0;
}

size_t Bin::write(double b) {
  if ((_cur + sizeof(b)) < (_buf + _size)) {
    memcpy(_cur, &b, sizeof(b));
    _cur += sizeof(b);
    return sizeof(b);
  }
  return 0;
}

size_t Bin::write(uint8_t *b, size_t sz) {
  if ((_cur + sz) < (_buf + _size)) {
    memcpy(_cur, b, sz);
    _cur += sz;
    return length();
  }
  return 0;
}

size_t Bin::write(char *b, size_t sz) {
  return write(reinterpret_cast<uint8_t *>(b), sz);
}

size_t Bin::write(const char *b) {
  if ((_cur + strlen(b)) < (_buf + _size)) {
    memcpy(_cur, b, strlen(b));
    _cur += strlen(b);
    return length();
  }
  return 0;
}

size_t Bin::write(const String &s) { return write(s.c_str()); }

size_t Bin::write(const __FlashStringHelper *ifsh) {
#if defined(__AVR__)
  PGM_P p = reinterpret_cast<PGM_P>(ifsh);
  size_t n = 0;
  while (1) {
    unsigned char c = pgm_read_byte(p++);
    if (c == 0)
      break;
    if (write(c))
      n++;
    else
      break;
  }
  return n;
#else
  return write(reinterpret_cast<const char *>(ifsh));
#endif
}

size_t Bin::sprintf(const char *str, ...) {
  va_list argptr;
  va_start(argptr, str);
  int ret = vsnprintf(reinterpret_cast<char *>(_cur), _size - (_cur - _buf),
                      str, argptr);
  if (ret) {
    while (*_cur != '\0') {
      ++_cur;
    }
  }
  return ret;
}

size_t Bin::strfloat(float b, int8_t min_width,
                     uint8_t num_digits_after_decimal) {
  return strdouble(static_cast<double>(b), min_width, num_digits_after_decimal);
}

size_t Bin::strdouble(double b, int8_t min_width,
                      uint8_t num_digits_after_decimal) {
  char buf[min_width + 4];
  if (dtostrf(b, min_width, num_digits_after_decimal, buf) != buf)
    return 0;
  size_t sz = strlen(buf);
  if ((_cur + sz) < (_buf + _size)) {
    memcpy(_cur, buf, sz);
    _cur += sz;
    return sz;
  }
  return 0;
}

size_t Bin::tostr() { return write('\0'); }

size_t Bin::Hex(uint8_t data) {
  static const char map[] = {"0123456789abcdef"};
  size_t ret = 0;
  ret = write(map[(uint8_t)((data & 0xF0) >> 4)]);
  ret += write(map[(uint8_t)(data & 0x0F)]);
  return ret;
}

size_t Bin::Hex(char data) { return Hex(static_cast<uint8_t>(data)); }

size_t Bin::Hex(uint16_t data) {
#define U16_ARRAY_SIZE (sizeof(uint16_t))
  uint8_t byteArray[U16_ARRAY_SIZE];
  memcpy(byteArray, &data, U16_ARRAY_SIZE);
  size_t ret = 0;
  for (int32_t i = U16_ARRAY_SIZE - 1; i > -1; i--) {
    ret += Hex(byteArray[i]);
  }
  return ret;
}

size_t Bin::Hex(int16_t data) { return Hex(static_cast<uint16_t>(data)); }

size_t Bin::Hex(uint32_t data) {
#define U32_ARRAY_SIZE (sizeof(uint32_t))
  uint8_t byteArray[U32_ARRAY_SIZE];
  memcpy(byteArray, &data, U32_ARRAY_SIZE);
  size_t ret = 0;
  for (int32_t i = U32_ARRAY_SIZE - 1; i > -1; i--) {
    ret += Hex(byteArray[i]);
  }
  return ret;
}

size_t Bin::Hex(int32_t data) { return Hex(static_cast<uint32_t>(data)); }

size_t Bin::Hex(uint64_t data) {
#define U64_ARRAY_SIZE (sizeof(uint64_t))
  uint8_t byteArray[U64_ARRAY_SIZE];
  memcpy(byteArray, &data, U64_ARRAY_SIZE);
  size_t ret = 0;
  for (int32_t i = U64_ARRAY_SIZE - 1; i > -1; i--) {
    ret += Hex(byteArray[i]);
  }
  return ret;
}

size_t Bin::Hex(int64_t data) { return Hex(static_cast<uint64_t>(data)); }

size_t Bin::Hex(bool data) { return Hex(static_cast<uint8_t>(data)); }

size_t Bin::Hex(float data) {
#define FLOAT_ARRAY_SIZE (sizeof(float))
  uint8_t byteArray[FLOAT_ARRAY_SIZE];
  memcpy(byteArray, &data, FLOAT_ARRAY_SIZE);
  size_t ret = 0;
  for (int32_t i = FLOAT_ARRAY_SIZE - 1; i > -1; i--) {
    ret += Hex(byteArray[i]);
  }
  return ret;
}

size_t Bin::Hex(double data) {
#define DOUBLE_ARRAY_SIZE (sizeof(double))
  uint8_t byteArray[DOUBLE_ARRAY_SIZE];
  memcpy(byteArray, &data, DOUBLE_ARRAY_SIZE);
  size_t ret = 0;
  for (int32_t i = DOUBLE_ARRAY_SIZE - 1; i > -1; i--) {
    ret += Hex(byteArray[i]);
  }
  return ret;
}

size_t Bin::trimLeft(size_t sz) {
  if (sz > _size || sz == 0)
    return 0;
  if (sz >= length()) {
    size_t ret = length();
    begin();
    return ret;
  }
  // Calculate the Remaining bytes after cut and Point
  size_t remain = length() - sz;
  uint8_t *p = _buf + sz;
  memcpy(_buf, p, remain);
  // Update the Current
  _cur = _buf + remain;
  return sz;
}

size_t Bin::trimRight(size_t sz) {
  if (sz > _size || sz == 0)
    return 0;
  if (sz >= length()) {
    size_t ret = length();
    begin();
    return ret;
  }
  // Calculate the Remaining bytes after cut
  size_t remain = length() - sz;
  // Update the Current
  _cur = _buf + remain;
  return sz;
}

bool Bin::isString() {
  if (length() > 0 && *(_cur - 1) == '\0')
    return true;
  return false;
}

size_t Bin::trim() {
  if (length() == 0)
    return 0;
  // Delete the Last Null Character
  if (isString())
    --_cur;
  return length();
}