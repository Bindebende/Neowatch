//
//  MCP9808.c
//  NEOGEO
//
//  Created by Bendegúz Hoffmann on 2014. 11. 16..
//  Copyright (c) 2014. Bendegúz Hoffmann. All rights reserved.
//

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include "GPS.h"
#include "MCP9808.h"
#include "LSM303.h"


/*config register(0x01)	bit: 8 shutdown mode 0 = Continuous conversion (power-up default),1 = Shutdown (Low-Power mode)
 bit: 7-6 must be 0 to enable shutdown mode
 bit: 5 this bit can not be set to Ď1í in Shutdown mode, but it can be cleared after the device enters Shutdown mode.
 
 */
void mcp_init(void)
{
    char UpperByte=0,LowerByte=0;
    
    UpperByte |=0x0;
    LowerByte |=0x0;
    
    i2c_start(); 							// send START command
    i2c_write(AddressByte & 0xFE); 			//WRITE Command (see Section 4.1.4 ďAddress ByteĒ)
                                            //also, make sure bit 0 is cleared Ď0í
    i2c_write(0x01); 						// Write CONFIG Register
    i2c_write(UpperByte);  					// Write data
    i2c_write(LowerByte);					// Write data
    i2c_stop(); 							// send STOP command
}








char read_temperature(char AddressByte)
{
    char UpperByte=0,LowerByte=0,Temperature=0;
    i2c_start();					 		// send START command
    i2c_write (AddressByte & 0xFE); 		//WRITE Command (see Section 4.1.4 ďAddress ByteĒ)
                                            //also, make sure bit 0 is cleared Ď0í
    i2c_write(0x05); 						// Write TA Register Address
    i2c_start(); 							//Repeat START
    i2c_write(AddressByte | 0x01);			// READ Command (see Section 4.1.4 ďAddress ByteĒ)
                                            //also, make sure bit 0 is Set Ď1í
    UpperByte = i2c_read(ACK); 				// READ 8 bits
                                            //and Send ACK bit
    LowerByte = i2c_read(NAK); 				// READ 8 bits
                                            //and Send NAK bit
    i2c_stop(); 							// send STOP command
                                            //Convert the temperature data
                                            //First Check flag bits
    if ((UpperByte & 0x80) == 0x80)
    {                                       //TA 3 TCRIT
    }
    if ((UpperByte & 0x40) == 0x40)
    {                                       //TA > TUPPER
    }
    if ((UpperByte & 0x20) == 0x20)
    {                                       //TA < TLOWER
    }
    
    UpperByte = UpperByte & 0x1F;           //Clear flag bits
    if ((UpperByte & 0x10) == 0x10){        //TA < 0įC
        UpperByte = UpperByte & 0x0F;       //Clear SIGN
        Temperature = 256 - (UpperByte x 16 + LowerByte / 16);
    }else //TA 3 0įC
        Temperature = (UpperByte x 16 + LowerByte / 16);
    
    return (Temperature);
}