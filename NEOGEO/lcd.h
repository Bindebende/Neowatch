//
//  lcd.h
//  NEOGEO
//
//  Created by Bendegúz Hoffmann on 2014. 11. 28..
//  Copyright (c) 2014. Bendegúz Hoffmann. All rights reserved.
//

#ifndef __NEOGEO__lcd__
#define __NEOGEO__lcd__

#include <inttypes.h>

#define RS 0
#define RW 1
#define EN 2
#define BL 3
#define PCF8574 0x40
#define INIT_MODE 0x80
#define CMD_MODE 0x00
#define DATA_MODE 0x01

static uint8_t backlight, lcd_line;




static uint8_t lcd_wr_val_mode(uint8_t , uint8_t );
void lcd_backlight(uint8_t );
void lcd_command(uint8_t );
void lcd_data(uint8_t );
void lcd_init(uint8_t );
void Send_string(const uint8_t *p);
void gotoXY(uint8_t ,uint8_t );
void goto_row(uint8_t );


#endif /* defined(__NEOGEO__lcd__) */
