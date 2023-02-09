// Copyright 2003 m24h, see http://www.apache.org/licenses/LICENSE-2.0

#ifndef     __IIC_H__
#define     __IIC_H__

#include "def.h"

// all are small and simple functions which need few or no registers
#pragma callee_saves iic_init,iic_wait,iic_start,iic_stop,iic_send,iic_recv_ack,iic_recv_nak

// init IIC as master, spd should be ((FOSC/2/IIC_FREQ)-4)/2
void iic_init(u8 spd);

// wait IIC command OK	
void iic_wait();

// send IIC START, device address, wait for ACK
void iic_start(u8 dev);

// send IIC STOP
void iic_stop();

// send an IIC 8bit data
void iic_send(u8 dat);

// receive an IIC 8bit data and send ACK
u8 iic_recv_ack();

// receive an IIC 8bit data and send NAK, means it's the last data need
u8 iic_recv_nak();


#endif