//
//  mcp9808temp.c
//  i2c_lcd
//
//  Created by Bendegúz Hoffmann on 2014. 11. 18..
//  Copyright (c) 2014. Bendegúz Hoffmann. All rights reserved.
//

#include "mcp9808.h"

#include "i2c.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <compat/twi.h>
#include "mcp9808.h"




/*config register(0x01)	bit: 8 shutdown mode 0 = Continuous conversion (power-up default),1 = Shutdown (Low-Power mode)
 bit: 7-6 must be 0 to enable shutdown mode
 bit: 5 this bit can not be set to ë1í in Shutdown mode, but it can be cleared after the device enters Shutdown mode.
 
 */
void mcp_init(char AddressByte)
{
    char UpperByte=0,LowerByte=0;
    
 
    
    //i2c_start(address);                                           // send START command
    
    i2c_write(AddressByte & 0xFE);                                  //WRITE Command (see Section 4.1.4 ìAddress Byteî)
    //also, make sure bit 0 is cleared ë0í
    i2c_write(0x01);                                                // Write CONFIG Register
    i2c_write(UpperByte);                                           // Write data
    i2c_write(LowerByte);                                           // Write data
    i2c_stop();                                                     // send STOP command
}




uint8_t MCP9808_read_temp(void)
{
    uint8_t upper=0,lower=0,temp=0;;
    
   
    i2c_start(0x30 & 0xFE);
    i2c_write(MCP9808_REG_AMBIENT_TEMP);                                /* Ta register address  */
    i2c_stop();
    i2c_start(0x30 | 0x01);                                             /* repstart for reading */
    
    //    temp=i2c_read_16(MCP9808_REG_AMBIENT_TEMP);
    
    
    upper=i2c_readAck();
    lower=i2c_readAck();
    
    upper=upper & 0x1F;                                                 /* clear flag bits      */
    
    if(upper & 0x10)
    {
        upper=upper & 0x0F;                                             /* clear sign           */
        
        temp=((upper<<4)+(lower>>4));
    }
    else
        temp=256-((upper<<4)+(lower>>4));
              
    return temp;
}

float Adafruit_MCP9808readTempC( void )
{
    uint16_t t = i2c_read_16(MCP9808_REG_AMBIENT_TEMP);
    
    float temp = t & 0x0FFF;
    temp /=  16.0;
    if (t & 0x1000) temp -= 256;
    
    return temp;
}




















