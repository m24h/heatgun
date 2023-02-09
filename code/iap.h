// Copyright 2003 m24h, see http://www.apache.org/licenses/LICENSE-2.0

#ifndef     __IAP_H__
#define     __IAP_H__

#include	"def.h"

// all are small and simple functions which need few or no registers
#pragma callee_saves iap_write,iap_erase

// read a byte from flash
#ifdef IAP_USE_MOVC
	#define iap_read(addr) (*(__code u8 *)((u16)EEPROM_OFFSET+(addr)))
#else
#pragma callee_saves iap_read
u8 iap_read(u16 addr);
#endif

// write a bye to flash
void iap_write(u16 addr, u8 dat);

// erase a page in flash, use an address in that page as address 
void iap_erase(u16 addr);

// load data from a whole EEPROM page into xdata ram, p should be a buffer with size of EEPROM_PAGE_SIZE
void iap_load (__xdata u8 *p, u8 page); 

// save data of a whole page to EEPROM page after erasing, p should be a buffer with size of EEPROM_PAGE_SIZE
void iap_save (__xdata u8 *p, u8 page) ;

#endif
