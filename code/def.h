// Copyright 2003 m24h, see http://www.apache.org/licenses/LICENSE-2.0

#ifndef     __DEF_H__
#define     __DEF_H__

#include	"stc8g_sdcc.h"

// paramters for this MCU in this program
#define FOSC          22118400  /* system clock, should use this for STC-ISP burning/downloading */
#define VCC	     5000	  /* power voltage of MCU, in mV */
#define EEPROM_PAGES      4  /* totally EEPROM pages, totally 2k bytes, 512 bytes per page, should use this setting when STC-ISP burning/downloading */
#define EEPROM_PAGE_SCALE  9
#define EEPROM_PAGE_SIZE (1<<EEPROM_PAGE_SCALE)
#define EEPROM_OFFSET   (17*1024-EEPROM_PAGES*512)

// make iap.c use "movc a,@a+dptr" instead of IAP registers operations
#define IAP_USE_MOVC

#define _nop()    __asm NOP __endasm
#define _push(x) __asm push _##x  __endasm
#define _pop(x)  __asm pop  _##x  __endasm

// SMALL-ENDIAN
typedef struct {
	unsigned char ll;
	unsigned char lh;
	unsigned char hl;
	unsigned char hh;
} u32s;

typedef struct {
	unsigned char l;
	unsigned char h;
} u16s;

#define _mk_u16(p, h, l) do { \
	*(u8*)(p)=(l); \
	*((u8*)(p)+1)=(h); \
} while(0)
	
#define _mk_u32(p, hh, hl, lh, ll) do { \
	*(u8*)(p)=(ll); \
	*((u8*)(p)+1)=(lh); \
	*((u8*)(p)+2)=(hl); \
	*((u8*)(p)+3)=(hh); \
} while(0)

typedef 	unsigned char	u8;
typedef 	unsigned int	u16;
typedef 	unsigned long	u32;

typedef 	signed char	i8;
typedef 	signed int		i16;
typedef 	signed long	i32;

#define _ea_clr_() \
	do { \
		_push_(IE);\
		EA=0; \
		_nop_(); \
		_nop_();

#define _ea_set_() \
	do { \
		_push_(IE);\
		_nop_(); \
		EA=1;
	
#define _ea_pop_() \
		_nop_(); \
		_pop_(IE); \
		_nop_(); \
		_nop_(); \
  } while(0);

#endif

