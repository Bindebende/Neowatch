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
    
    UpperByte |=0x0;
    LowerByte |=0x0;
    
    //i2c_start(address);                                           // send START command
    
    i2c_write(AddressByte & 0xFE);                                  //WRITE Command (see Section 4.1.4 ìAddress Byteî)
    //also, make sure bit 0 is cleared ë0í
    i2c_write(0x01);                                                // Write CONFIG Register
    i2c_write(UpperByte);                                           // Write data
    i2c_write(LowerByte);                                           // Write data
    i2c_stop();                                                     // send STOP command
}








char read_temperature(char AddressByte)
{
    
    unsigned char UpperByte=0,LowerByte=0,Temperature=0;
    //i2c_start(address);                                           // send START command
    i2c_write (AddressByte & 0xFE);                                     //WRITE Command (see Section 4.1.4 ìAddress Byteî)
    //also, make sure bit 0 is cleared ë0í
    i2c_write(0x05);                                                // Write TA Register Address
    //i2c_start(address);                                           //Repeat START
    i2c_write(AddressByte | 0x01);                                      // READ Command (see Section 4.1.4 ìAddress Byteî)
    //also, make sure bit 0 is Set ë1í
    UpperByte =i2c_readAck;                                         // READ 8 bits
    //and Send ACK bit
    LowerByte = i2c_readNak();                                      // READ 8 bits
    //and Send NAK bit
    i2c_stop();                                                     // send STOP command
    //Convert the temperature data
    //First Check flag bits
    if ((UpperByte & 0x80) == 0x80)
    {
        //TA 3 TCRIT
    }
    if ((UpperByte & 0x40) == 0x40)
    {
        //TA > TUPPER
    }
    if ((UpperByte & 0x20) == 0x20)
    {
        //TA < TLOWER
    }
    
    UpperByte = UpperByte & 0x1F;                                   //Clear flag bits
    if ((UpperByte & 0x10) == 0x10)
    { //TA < 0∞C
        UpperByte = UpperByte & 0x0F;                               //Clear SIGN
        Temperature = 256 - (UpperByte * 16 + LowerByte / 16);
    }
    else //TA 3 0∞C
        Temperature = (UpperByte * 16 + LowerByte / 16);
    
    return (Temperature);
}