// Copyright 2003 m24h, see http://www.apache.org/licenses/LICENSE-2.0

#include "ssd1306.h"

#include "iic.h"

u8 ssd1306_device;

// send commands 
void ssd1306_cmd(u8 cmd)
{
	iic_start(ssd1306_device);
	iic_send(0x00);
	iic_send(cmd);
	iic_stop();
}

// init ssd1306 for normal usage, this will enable charge-pump, which is normally used in many modules
void ssd1306_init(u8 com_offset, __bit com_remap, __bit seg_remap)
{
	ssd1306_cmd(SSD1306_DISPLAY_OFF);
	ssd1306_cmd(SSD1306_SCROLL_OFF);
	ssd1306_cmd(seg_remap?SSD1306_SEG_REMAP:SSD1306_SEG_NOMAP);
	ssd1306_cmd(com_remap?SSD1306_COM_REMAP:SSD1306_COM_NOMAP);
	ssd1306_cmd(SSD1306_COM_OFFSET);	ssd1306_cmd(com_offset);
	ssd1306_cmd(SSD1306_ENTIRE_OFF);
	ssd1306_cmd(SSD1306_INVERSE_OFF);
	ssd1306_cmd(SSD1306_ADRMODE); ssd1306_cmd(SSD1306_ADRMODE_PG);
	ssd1306_cmd(SSD1306_CHG_PUMP); ssd1306_cmd(SSD1306_CHG_PUMP_ON);
	ssd1306_cmd(CH1115_CHG_PUMP); ssd1306_cmd(CH1115_CHG_PUMP_ON);
	ssd1306_rect(0,0,128,8,0); // clear all memory
	ssd1306_cmd(SSD1306_DISPLAY_ON);
}

// set OLED RAM start COL/PAGE for write/fill function 
void ssd1306_mem(u8 col, u8 page)
{
	iic_start(ssd1306_device);
	iic_send(0x00);
	iic_send(0x0f & col);
	iic_send(0x10 | (col>>4));
	iic_send(0xB0 | (page & 0x07));
	iic_stop();
}

// write a buffer to OLED RAM, RAM COL isautomatically increased
void ssd1306_write(const u8 *p_dat, u8 len)
{
	if (!len) return;
	
	iic_start(ssd1306_device);
	iic_send(0x40);
	do {
		iic_send(*(p_dat++));
	} while (--len);
	iic_stop();	
}

// fill OLED RAM by a specifed byte, RAM COL isautomatically increased
void ssd1306_fill(u8 dat, u8 len)
{
	if (!len) return;

	iic_start(ssd1306_device);
	iic_send(0x40);
	do {
		iic_send(dat);
	} while (--len);
	iic_stop();	
}

// fill a rectangle
void ssd1306_rect(u8 col, u8 page, u8 ncol, u8 npage, u8 dat)
{
	if (!npage) return;

	do {
		ssd1306_mem(col, page);
		ssd1306_fill(dat, ncol);
		page++;
	} while (--npage);
}

// show a bitmap, p_dat should be a pointer to ncol*npage bytes 
void ssd1306_bitmap(u8 col, u8 page, u8 ncol, u8 npage, const u8 *p_dat)
{
	if (!npage) return;
	
	do {
		ssd1306_mem(col, page);
		ssd1306_write(p_dat, ncol);
		page++;
		p_dat+=ncol;
	} while (--npage);
}


