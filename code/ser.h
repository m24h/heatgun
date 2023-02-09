// Copyright 2003 m24h, see http://www.apache.org/licenses/LICENSE-2.0

#ifndef     __SER_H__
#define     __SER_H__

#include	"def.h"

// those are small and simple functions which need few or no registers
#pragma callee_saves ser_init,ser_ch,ser_h4,ser_h8,ser_h16,ser_h32

// init a send-only serial 1 using timer 2, t2cnt should be (65536 - FOSC/BAUDRATE/4)
void ser_init (u16 t2cnt);

// send a character
void ser_ch (char ch);

// send a NULL-ended string
void ser_str(char *p);

// send a 4bit hex number
void ser_h4(u8 u);

// send a 8bit hex number
void ser_h8 (u8 u);

// send a 16bit hex number
void ser_h16 (u16 u);

// send a 32bit hex number
void ser_h32 (u32 u);

// send a 32bit unsigned integer
void ser_u32 (u32 u);

// send a 32bit signed integer
void ser_i32 (i32 i);

#endif