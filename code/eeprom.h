// Copyright 2003 m24h, see http://www.apache.org/licenses/LICENSE-2.0

#ifndef     __EEPROM_H__
#define     __EEPROM_H__

#include	"def.h"

// find start address of last written slot in eeprom pages specified by "page_start" and "page_num"
// page_num is at least 2, but if page size is not divisible by "slot_size", it will be at least 3, since some slot  are over 2 pages
// slot_size must be less then  page size
// if 0xFFFF is returned, no valid slot was found
// IMPORTANT: first byte in slot can not be 0xFF
u16 eeprom_load (u16 slot_size, u8 page_start, u8 page_num);

// get a start address for writing in eeprom, and it's pre-wiped
// "last" is last start address returned by eeprom_load() or  eeprom_save()
// IMPORTANT: first byte in slot can not be 0xFF
u16 eeprom_save (u16 last, u16 slot_size, u8 page_start, u8 page_num);

#endif
