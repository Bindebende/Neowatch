//
//  ISRs.c
//  NEOGEO
//
//  Created by Bendegúz Hoffmann on 2014. 12. 20..
//  Copyright (c) 2014. Bendegúz Hoffmann. All rights reserved.
//
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay.h>
#include "uart.h"

volatile uint8_t mode=0;


ISR(USART1_RX_vect)
{
    uint8_t static value;
    value=UDR1;
    if(value=='\n')buffer_index=0 ;
    buffer[buffer_index]=value;
    buffer_index++;
}

ISR(PCINT0_vect)                                    //61. oldal vectortabla
{
    static uint8_t last_value;
    uint8_t value = PINB;                          // read current input bits on Port B
    uint8_t changed_bits = value ^ last_value;
    
    last_value = value;
    
    if ( changed_bits & (1<<4) )
    {
        if ( value & (1<<4) )
        {
            // pin is high
            
            mode++;
            if(mode>2)mode=0;
            
            
        }
        else
        {
            // pin is low
        }
    }
}