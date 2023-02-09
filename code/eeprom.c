// Copyright 2003 m24h, see http://www.apache.org/licenses/LICENSE-2.0

#include "def.h"
#include "eeprom.h"

#include "iap.h"

// find start address of last written slot in eeprom pages specified by "page_start" and "page_num"
// page_num is at least 2, but if page size is not divisible by "slot_size", it will be at least 3, since some slot  are over 2 pages
// slot_size must be less then  page size
// if 0xFFFF is returned, no valid slot was found
// IMPORTANT: first byte in slot can not be 0xFF
u16 eeprom_load (u16 slot_size, u8 page_start, u8 page_num)
{
	u16 end=(u16)(page_start+page_num)<<EEPROM_PAGE_SCALE;
	u16 p=(u16)page_start<<EEPROM_PAGE_SCALE;
	u16 q=p+slot_size;	
	while (q<=end) {
		if (iap_read(p)!=0xFF) {
			p=q+slot_size;
			while (p<=end) {
				if (iap_read(q)==0xFF)
					break;
				q=p;
				p+=slot_size;
			}
			return q-slot_size;
		}
		p=q;
		q+=slot_size;
	}
	return 0xFFFF;
}	

// get a start address for writing in eeprom, and it's pre-wiped
// "last" is last start address returned by eeprom_load() or  eeprom_save()
// IMPORTANT: first byte in slot can not be 0xFF
u16 eeprom_save (u16 last, u16 slot_size, u8 page_start, u8 page_num)
{
	u16 start=(u16)page_start<<EEPROM_PAGE_SCALE;
	u16 end=(u16)(page_start+page_num)<<EEPROM_PAGE_SCALE;
	u16 nextaddr;
	
	// maybe it's not in valid address
	if (last<start || last>=end)
		last=end-slot_size;
		
	// make sure next page of scaned is wiped
	nextaddr=(last+EEPROM_PAGE_SIZE) & (0xFFFF<<EEPROM_PAGE_SCALE);
	if (nextaddr>=end)
		nextaddr=page_start<<EEPROM_PAGE_SCALE;
	if (iap_read(nextaddr)!=0xFF)
		iap_erase(nextaddr);
	
	nextaddr=last+slot_size;
	if (nextaddr+slot_size>end)
		nextaddr=page_start<<EEPROM_PAGE_SCALE;
	return nextaddr;	
}

