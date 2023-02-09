// Copyright 2003 m24h, see http://www.apache.org/licenses/LICENSE-2.0

#include "tools.h"

// delay in millisecond, specified by "ms"
// only for STC8A/F/G/H
void tools_delay_ms(u16 ms) __naked
{
	ms; // no "unreferenced" warning
	__asm
		; infact, no need to protect DPL1/DPH1 in current version of SDCC
		;push _DPL1
		;push _DPH1
		inc dpl
		inc dph
	00003$:	
		djnz dpl, 00001$
		djnz dph, 00001$
		;pop _DPH1
		;pop _DPL1
		ret
	00001$:	
		mov _DPH1, #((FOSC/3008+0xFF)>>8)
		mov _DPL1, #((FOSC/3008)&0xFF)
	00002$:  
		djnz _DPL1, 00002$ 
		djnz _DPH1, 00002$
		sjmp 00003$
	__endasm;

/*	
	while (ms--){
  	j = (u8)(FOSC/3008);
  	i = (u8)((FOSC/3008+0xFF)>>8);
		do {
			while (--j);
		} while (--i);		
	}
*/		
}




