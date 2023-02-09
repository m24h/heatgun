// Copyright 2003 m24h, see http://www.apache.org/licenses/LICENSE-2.0

#include	"ser.h"

// init a send-only serial 1 using timer 2, t2cnt should be (65536 - FOSC/BAUDRATE/4)
void ser_init (u16 t2cnt)
{
	PCON &= 0b00111111; // default
	SCON = 0b01000000;  // mode 1 (8bit), can not recv.
	IE2 &= 0b11111011; // disable T2 intr.
	INTCLKO &= 0b11111011; // T2 no clock port output
	TM2PS = 0; // pre-div = 1
	T2L = t2cnt;
	T2H = t2cnt >> 8;
	ES=0; // disable serial 1 intr.
	AUXR = AUXR & 0b11000010 | 0b00010101; // start and use T2, T2 use FOSC/1, T2 as timer
}

// send a character
void ser_ch (char ch)
{
	SBUF=ch;
	while (!TI);
	TI=0;	
}

// send a NULL-ended string
void ser_str(char *p)
{
	while (*p) 
		ser_ch(*p++);
}

// send a 4bit hex number
void ser_h4(u8 u)
{
	u &= 0x0f;
	u += u>9?(u8)('A'-10):(u8)'0';
	ser_ch(u);
}

// send a 8bit hex number
void ser_h8 (u8 u)
{
	ser_h4(u>>4);
	ser_h4(u);
}

// send a 16bit hex number
void ser_h16 (u16 u)
{
	ser_h8(u>>8);
	ser_h8(u);
}

// send a 32bit hex number
void ser_h32 (u32 u)
{
	ser_h16(u>>16);
	ser_h16(u);
}

// send a 32bit unsigned integer
void ser_u32 (u32 u)
{
	u8 s [11];
	u8 i=0;
	u32 t;
	do  {
		t=u/10;
		s[i++]=u-t*10;
		u=t;
	} while (u);
	
	do {
		ser_h4(s[--i]);
	} while (i);
}

// send a 32bit signed integer
void ser_i32 (i32 i)
{
	if (i<0) {
		ser_ch('-');
		i=-i;
	}
	ser_u32(i);
}

