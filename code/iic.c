// Copyright 2003 m24h, see http://www.apache.org/licenses/LICENSE-2.0

#include "iic.h"

// init IIC as master, spd should be ((FOSC/2/IIC_FREQ)-4)/2
void iic_init(u8 spd)
{
	I2CMSCR &= 0b01110000;  // no intr., no command now
	I2CMSAUX &= 0b11111110;  // no auto-send
	I2CCFG = 0b11000000 | spd;  // enabled as master, bus speed=Fosc/2/(x*2+4) 
	I2CMSST &= 0b00111100; // clear status
}

// wait IIC command OK	
void iic_wait ()
{
	while (!(I2CMSST & 0b01000000)); 
	I2CMSST &= 0b10111111;
}

// send IIC START, device address, wait for ACK
void iic_start(u8 dev)
{
	I2CTXD = dev;                               
	I2CMSCR = (I2CMSCR & 0b01110000) | 0b00001001;                            
	iic_wait();
}

// send IIC STOP
void iic_stop()
{
	I2CMSCR = (I2CMSCR & 0b01110000) | 0b00000110;
	iic_wait();
}

// send an IIC 8bit data
void iic_send(u8 dat)
{
	I2CTXD = dat;                               
	I2CMSCR = (I2CMSCR & 0b01110000) | 0b00001010;                            
	iic_wait();
}

// receive an IIC 8bit data and send ACK
u8 iic_recv_ack()
{
	I2CMSCR = (I2CMSCR & 0b01110000) | 0b00001011;                             
	iic_wait();
	return I2CRXD;
}

// receive an IIC 8bit data and send NAK, means it's the last data need
u8 iic_recv_nak()
{
	I2CMSCR = (I2CMSCR & 0b01110000) | 0b00001100;                             
	iic_wait();
	return I2CRXD;
}
