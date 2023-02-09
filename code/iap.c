// Copyright 2003 m24h, see http://www.apache.org/licenses/LICENSE-2.0

#include "iap.h"

#ifndef IAP_USE_MOVC
// read a byte from flash
u8 iap_read(u16 addr) 
{
	IAP_CONTR = 0x80;
	IAP_TPS=((u8)((FOSC+500000UL)/1000000UL)>31)?31:(u8)((FOSC+500000UL)/1000000UL);
	IAP_CMD = 1;
	IAP_ADDRL = addr;
	IAP_ADDRH = addr >> 8;
	IAP_TRIG = 0x5a;
	IAP_TRIG = 0xa5;
	_nop();
	IAP_CONTR=0;
	IAP_CMD = 0;
	return IAP_DATA;
}
#endif

// write a bye to flash
void iap_write(u16 addr, u8 dat)
{
	IAP_CONTR = 0x80;
	IAP_TPS=((u8)((FOSC+500000UL)/1000000UL)>31)?31:(u8)((FOSC+500000UL)/1000000UL);
	IAP_CMD = 2;
	IAP_ADDRL = addr;
	IAP_ADDRH = addr >> 8;
	IAP_DATA = dat;
	IAP_TRIG = 0x5a;
	IAP_TRIG = 0xa5;
	_nop();
	IAP_CONTR=0;
	IAP_CMD = 0;
}

// erase a page in flash, use an address in that page as address 
void iap_erase(u16 addr)
{
	IAP_CONTR = 0x80;
	IAP_TPS=((u8)((FOSC+500000UL)/1000000UL)>31)?31:(u8)((FOSC+500000UL)/1000000UL);
	IAP_CMD = 3;
	IAP_ADDRL = addr;
	IAP_ADDRH = addr>>8;
	IAP_TRIG = 0x5a;
	IAP_TRIG = 0xa5;
	_nop();
	IAP_CONTR=0;
	IAP_CMD = 0;
}

// load data from a whole EEPROM page into xdata ram, p should be a buffer with size of EEPROM_PAGE_SIZE
void iap_load (__xdata u8 *p, u8 page) 
{
	u16 n=EEPROM_PAGE_SIZE;
	u16 addr=(u16)page<<EEPROM_PAGE_SCALE;
	do {
		*p++=iap_read(addr++);
	} while (--n);
}

// save data of a whole page to EEPROM page after erasing, p should be a buffer with size of EEPROM_PAGE_SIZE
void iap_save (__xdata u8 *p, u8 page) 
{
	u16 n=EEPROM_PAGE_SIZE;
	u16 addr=(u16)page<<EEPROM_PAGE_SCALE;
	iap_erase(addr);
	do {
		iap_write(addr++, *p++);
	} while (--n);
}