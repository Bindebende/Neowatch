//
//  uart.h
//  NEOGEO
//
//  Created by Bendegúz Hoffmann on 2014. 11. 19..
//  Copyright (c) 2014. Bendegúz Hoffmann. All rights reserved.
//
#ifndef __UART_H_
#define	__UART_H_

#include <avr/io.h>

#define UART0_DDR		DDRE
#define UART0_PORT		PORTE
#define	UART0_TX		PE1
#define UART0_RX		PE0

#define UART1_DDR		DDRD
#define UART1_PORT		PORTD
#define	UART1_TX		PD3
#define UART1_RX		PD2

void avr_uart_init(void);
void avr_uart_send_byte(uint8_t );

void uart_send_string(const uint8_t *p);
uint8_t avr_uart_receive_byte(void);
void avr_uart_send_byte(uint8_t tx_byte);


extern volatile uint8_t buffer[100],buffer_index;

#endif