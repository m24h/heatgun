// Copyright 2003 m24h, see http://www.apache.org/licenses/LICENSE-2.0

#ifndef     __K_H__
#define     __K_H__

#include	"def.h"
// get temperature in 1/32 Celsius degree (a fixed-5-point float) of K-thermocouple with input in uV
// return 0xFFFF when out of range
u16 K_temp(u16 uv);

// get uV from temperature, input temperature is in 1/32 Celsius degree (5bit fixed-point)
// return 0xFFFF when out of range
u16 K_uv(u16 temp);
	
#endif