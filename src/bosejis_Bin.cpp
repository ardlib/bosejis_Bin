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

size_t Bin::write(char b) { return write((uint8_t)b); }

size_t Bin::write(int8_t b) { return write((uint8_t)b); }

size_t Bin::write(uint16_t b) {
  if ((_cur + sizeof(b)) < (_buf + _size)) {
    memcpy(_cur, &b, sizeof(b));
    _cur += sizeof(b);
    return sizeof(b);
  }
  return 0;
}

size_t Bin::write(int16_t b) { return write((uint16_t)b); }

size_t Bin::write(uint32_t b) {
  if ((_cur + sizeof(b)) < (_buf + _size)) {
    memcpy(_cur, &b, sizeof(b));
    _cur += sizeof(b);
    return sizeof(b);
  }
  return 0;
}

size_t Bin::write(int32_t b) { return write((uint32_t)b); }

size_t Bin::write(uint64_t b) {
  if ((_cur + sizeof(b)) < (_buf + _size)) {
    memcpy(_cur, &b, sizeof(b));
    _cur += sizeof(b);
    return sizeof(b);
  }
  return 0;
}

size_t Bin::write(int64_t b) { return write((uint64_t)b); }

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