//
//  i2c.h
//  NEOGEO
//
//  Created by Bendegúz Hoffmann on 2014. 11. 19..
//  Copyright (c) 2014. Bendegúz Hoffmann. All rights reserved.
//

#ifndef __NEOGEO__i2c__
#define __NEOGEO__i2c__

void i2c_init(void);
unsigned char i2c_start(unsigned char adress);
void i2c_start_wait(unsigned char address);	//addig cimez amig nem valaszol a slave
unsigned char i2c_rep_start(unsigned char address);
void i2c_stop(void);
unsigned char i2c_write( unsigned char data);
unsigned char i2c_readAck(void);
unsigned char i2c_readNak(void);
uint16_t i2c_read_16(uint8_t reg);

#endif /* defined(__NEOGEO__i2c__) */
