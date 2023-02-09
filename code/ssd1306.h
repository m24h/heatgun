// Copyright 2003 m24h, see http://www.apache.org/licenses/LICENSE-2.0

#ifndef     __SSD1306_H__
#define     __SSD1306_H__

#include "def.h"

// those are small and simple functions which need few or no registers
#pragma callee_saves ssd1306_cmd,ssd1306_mem,ssd1306_fill,ssd1306_rect

/*
    SSD1306 is a 128*64 OLED controller, which has 128 SEGs and 64 COMs.
    Every SEG can be located by a COL No. from 0-127.
    Every COM can be located by a PAGE No. from 0-7 and a BIT No. from 0 (LSB) to 7 (MSB).
    For example, a SEG:x/COM:y point in OLED screen corresponds to a COL:x/PAGE:int(y/8)/BIT:(y mod 8) bit  in OLED memory.
    Each Read/Write operation target must be at least a byte,  or 8 bits, or 8 OLED points. 
    This module is now support only default "Page addressing mode", that is, continuous OLED memory accessing is in COL direction, with a fixed PAGE No.
*/

// a SSD1306 device can be located by one of following IIC addresss
#define SSD1306_ADDR1   ((u8)0x78)  /* default */
#define SSD1306_ADDR2   ((u8)0x7A)

// SSD1306 commands
#define SSD1306_NOP     			((u8)0xE3) /* no operation */
#define SSD1306_CONTRAST		((u8)0x81) /* followed by a contrast byte 0-0xff */
#define SSD1306_ENTIRE_ON		((u8)0xA5) /* All points on */
#define SSD1306_ENTIRE_OFF		((u8)0xA4) /* All points follow memory content */
#define SSD1306_INVERSE_ON		((u8)0xA7) /* point on when bit is 0 */
#define SSD1306_INVERSE_OFF		((u8)0xA6) /* point on when bit is 1 */
#define SSD1306_DISPLAY_ON   	((u8)0xAF) /* normal display */
#define SSD1306_DISPLAY_OFF		((u8)0xAE) /* All points off, sleep mod */
#define SSD1306_ADRMODE		((u8)0x20) /* followed by an Addressing mode byte SSD1306_ADRMODE_XXX */
#define SSD1306_ADRMODE_HOR	((u8)0x0)  /* Horizontal Addressing mode */
#define SSD1306_ADRMODE_VER	((u8)0x1)  /* Vertical Addressing mode */
#define SSD1306_ADRMODE_PG	((u8)0x3)  /* Page Addressing mode */
#define SSD1306_SEG_NOMAP		((u8)0xA0) /* COL0 is mapped to SEG 0, ...,  COL127 is mapped to SEG 127 */
#define SSD1306_SEG_REMAP		((u8)0xA1) /* COL0 is mapped to SEG 127, ..., COL127 is mapped to SEG 0 */
#define SSD1306_COM_START		((u8)0x40) /* OR a memory start row 0-0x3F as final command No. , */
#define SSD1306_COM_OFFSET		((u8)0xD3) /* followed by a COM offset byte 0-0x3F */
#define SSD1306_COM_MUX		((u8)0xA8) /* followed by a MUX-1 No. 0x0F-0x3F */
#define SSD1306_COM_NOMAP		((u8)0xC0) /* Scan from COM0 to COM(MUX-1) */
#define SSD1306_COM_REMAP		((u8)0xC8) /* Scan from COM(MUX-1) to COM0 */
#define SSD1306_COM_PIN			((u8)0xDA) /* followed by COM pin hardware configure SSD1306_COM_PIN_XXXX */
#define SSD1306_COM_PIN_NOR	((u8)0x02) /* COM0-63 is neither mapped nor alternated */
#define SSD1306_COM_PIN_ALT		((u8)0x12) /* COM0-31 mapped to ROW0,2,4...62,  COM32-63 is mapped to ROW1,3,5...63*/
#define SSD1306_COM_PIN_LR		((u8)0x22) /* COM0-31 is mapped to ROW32-63, COM32-63 is mapped to ROW0-31 */
#define SSD1306_COM_PIN_ALT_LR	((u8)0x32) /* COM0-31 mapped to ROW1,3,5...63, COM32-63 is mapped to ROW2,4,6...62 */
#define SSD1306_SCROLL_OFF		((u8)0x2E) /* stop scorlling, after this, ram data needs to be rewriten */
#define SSD1306_SCROLL_ON		((u8)0x2F) /* start scorlling */
#define SSD1306_SCROLL_R_HOR	((u8)0x26) /* right horizontal scroll, followed by 6 bytes: 0x0 start_page time_interval stop_page 0x0 0xff */
#define SSD1306_SCROLL_L_HOR	((u8)0x27) /* left horizontal scroll, followed by 6 bytes: 0x0 start_page time_interval stop_page 0x0 0xff */
#define SSD1306_SCROLL_R_VER	((u8)0x29) /* vertical and right horizontal scroll, followed by 5 bytes: 0x0 start_page time_interval stop_page vertical offset */
#define SSD1306_SCROLL_L_VER	((u8)0x2A) /* vertical and left horizontal scroll, followed by 5 bytes: 0x0 start_page time_interval stop_page vertical offset */
#define SSD1306_SCROLL_AREA		((u8)0xA3) /* set vertical scroll area for vertical and right/left horizontal scroll, followed by 2 bytes: rows_fixed_at_top rows_in_scroll_area */ 
#define SSD1306_CHG_PUMP		((u8)0x8D) /* fowllowing a byte SSD1306_CHG_PUMP_XXX to enable/disbale charge pump, display should be off before this command */
#define SSD1306_CHG_PUMP_ON	((u8)0x14) /* enable charge pump when display on */
#define SSD1306_CHG_PUMP_OFF	((u8)0x10) /* disable charge pump */
#define CH1115_CHG_PUMP		((u8)0xAD) /* fowllowing a byte CH1115_CHG_PUMP_XX to enable/disbale charge pump (for CH1115 chip, which is similar to SSD1306) , display should be off before this command*/
#define CH1115_CHG_PUMP_ON	((u8)0x8B) /* enable CH1115 charge pump when display on */
#define CH1115_CHG_PUMP_OFF	((u8)0x8A) /* disable CH1115 charge pump */

extern u8 ssd1306_device;

// specify global-used device address of ssd1306 for compacting parameter passing, and SSD1306_ADDR1 is used be default
inline void ssd1306_dev(u8 addr)
{
	ssd1306_device=addr & (u8)0xfe;
}

// send command
void ssd1306_cmd(u8 cmd);

// init ssd1306 for normal usage, this will enable charge-pump, which is normally used in many modules
void ssd1306_init(u8 com_offset, __bit com_remap, __bit seg_remap);

// set OLED RAM start COL/PAGE for write/fill function 
void ssd1306_mem(u8 col, u8 page);

// write a buffer to OLED RAM, RAM COL isautomatically increased
void ssd1306_write(const u8 *p_dat, u8 len);

// fill OLED RAM by a specifed byte, RAM COL isautomatically increased
void ssd1306_fill(u8 dat, u8 len);

// fill a rectangle
void ssd1306_rect(u8 col, u8 page, u8 ncol, u8 npage, u8 dat);

// show a bitmap, p_dat should be a pointer to ncol*npage bytes 
void ssd1306_bitmap(u8 col, u8 page, u8 ncol, u8 npage, const u8 *p_dat);

#endif