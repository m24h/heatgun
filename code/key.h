// Copyright 2003 m24h, see http://www.apache.org/licenses/LICENSE-2.0

#ifndef     __KEY_H__
#define     __KEY_H__

#include "def.h"

// a key filter, ignore pulse which width is less then "cnt" (8bit)
// "name" is the __bit parameters name, must be defined outside
// "bit" is input __bit parameters name
#define KEY_LEVEL(name, bit, cnt)  \
	static u8    name##_flt=0;\
	if (name==(bit)) name##_flt=0; \
	else if (name##_flt==(cnt)) name=!name; \
	else name##_flt++;

// a button with long-press detection, use logical "1" as button down/pressed
// "name" "bit" "cnt" are as same as those in KEY_FILTER(), but "name" is already defined inside
// e_xxx is __bit event which is set when button is down/click/long-press
// cnt_long(16bit) is the interval for long-press detection, 0/0xFFFF means no long-press detection
// if long-press event is set, no more click event will be set util key is released and pressed again
#define KEY_BUTTON(name, bit, cnt, e_dwn, e_clk, e_long, cnt_long) \
	static __bit name=0; \
	static __bit name##_last=0; \
	static u16 name##_ldet=0; \
	KEY_LEVEL(name, bit, cnt); \
	if (!name##_last) {  \
		if (name) { \
			name##_ldet=1; \
			(e_dwn)=1; \
		} \
	} else if (name##_ldet) { \
		if (name) { \
			if (name##_ldet==(cnt_long)) { \
				name##_ldet=0; \
				(e_long)=1; \
		 	} else \
		 		name##_ldet++; \
		} else  \
			 (e_clk)=1; \
	} \
	name##_last=name; 

// a 1-step-1-pulse rotary encoder
// "name_x" "bit_x""cnt" are as same as those in KEY_FILTER(), but "name" is already defined inside
// e_xxx is __bit which is set when rotary encoder is turned left/right
#define KEY_ROT1(name_a, name_b, bit_a, bit_b, cnt, e_left, e_right) \
	static __bit name_a=0; \
	static __bit name_b=0; \
	static __bit name_a##_last=0; \
	static __bit name_b##_last=0; \
	static __bit name_a##_good=0; \
	static __bit name_b##_good=0; \
	KEY_LEVEL(name_a, bit_a, cnt);  \
	KEY_LEVEL(name_b, bit_b, cnt); \
	if (name_a##_last && !name_a) { \
		name_a##_good=1; \
		name_b##_good=0; \
	} else if (!name_a##_last && name_a) { \
		if (name_a##_good && name_b##_good) { \
			if (name_b) e_right=1; \
			else e_left=1; \
		} \
		name_a##_good=1; \
		name_b##_good=0; \
	} \
	if (name_b!=name_b##_last) name_b##_good=1; \
	name_a##_last=name_a; \
	name_b##_last=name_b; 

// a 2-step-1-pulse rotary encoder
// "name_x" "bit_x""cnt" are as same as those in KEY_FILTER()
// e_xxx is __bit which is set when rotary encoder is turned left/right	
#define KEY_ROT2(name_a, name_b, bit_a, bit_b, cnt, e_left, e_right) \
	static __bit name_a=0; \
	static __bit name_b=0; \
	static __bit name_a##_last=0; \
	static __bit name_b##_last=0; \
	static __bit name_a##_good=0; \
	static __bit name_b##_good=0; \
	KEY_LEVEL(name_a, bit_a, cnt);  \
	KEY_LEVEL(name_b, bit_b, cnt); \
	if (name_a##_last && !name_a) { \
		if (name_a##_good && name_b##_good) { \
			if (!name_b) e_right=1; \
			else e_left=1; \
		} \
		name_a##_good=1; \
		name_b##_good=0; \
	} else if (!name_a##_last && name_a) { \
		if (name_a##_good && name_b##_good) { \
			if (name_b) e_right=1; \
			else e_left=1; \
		} \
		name_a##_good=1; \
		name_b##_good=0; \
	} \
	if (name_b!=name_b##_last) name_b##_good=1; \
	name_a##_last=name_a; \
	name_b##_last=name_b;

// detect short interval repeated event, if an "e_in" occurs quickly swallow "e_in" and send "e_out"
#define KEY_QUICK(name, e_in, e_out, cnt) \
	static u8 name=0xFF; \
	if (e_in) { \
		if (name<(u8)(cnt)) { e_in=0;  e_out=1; } \
		name=0; \
	} else if (name!=0xFF) name++; 





#endif