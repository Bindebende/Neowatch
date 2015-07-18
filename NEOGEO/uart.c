//
//  uart.c
//  NEOGEO
//
//  Created by Bendegúz Hoffmann on 2014. 11. 19..
//  Copyright (c) 2014. Bendegúz Hoffmann. All rights reserved.
//
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

#define BAUDRATE 9600
#define UBRR_VALUE ((F_CPU / (BAUDRATE * 16UL)))

// Initialize the UART
void avr_uart_init(void)
{

    UBRR1L = UBRR_VALUE;
    UBRR1H = (UBRR_VALUE>>8);//4
    
#if USE_2X
    UCSR1A |= _BV(U2X1);
#else
    UCSR1A &= ~(_BV(U2X1));
#endif
    
    UCSR1C = (1<<UCSZ11) | (1<<UCSZ10); /* 8-bit data */
    UCSR1B = (1<<RXEN1) | (1<<TXEN1) | (1<<RXCIE1) | (1<<TXCIE1);   /* Enable RX and TX */

}

// Send one char (blocking)
void avr_uart_send_byte(uint8_t tx_byte)
{
    // Wait to be able to transmit
    while((UCSR1A & _BV(UDRE1)) == 0)
        asm volatile("nop"::);
    // Put the data into the send buffer
    UDR1 = tx_byte;
}


// Get one char if available, otherwise -1
uint8_t avr_uart_receive_byte(void)
{
    if((UCSR1A & _BV(RXC1)) != 0)
    {
        return UDR1;
    }
    else
    {
        return -1;
    }
}
    
void uart_send_string(const uint8_t *p)
{
    while(*p)
    {
        avr_uart_send_byte(*p);
        p++;
    }
}




ISR(USART1_TX_vect)
{
//    UDR1='\n';
//    UCSR1B&=~(1<<TXCIE1);
    
}



