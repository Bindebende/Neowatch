//
//  lcd.c
//  NEOGEO
//
//  Created by Bendegúz Hoffmann on 2014. 11. 28..
//  Copyright (c) 2014. Bendegúz Hoffmann. All rights reserved.
//

//
//  lcd.c
//  i2c_lcd
//
//  Created by Bendegúz Hoffmann on 2014. 11. 18..
//  Copyright (c) 2014. Bendegúz Hoffmann. All rights reserved.
//

#include "lcd.h"
#include "i2c.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <compat/twi.h>

static uint8_t lcd_wr_val_mode(uint8_t c, uint8_t mode)
{
    uint8_t port = backlight;
    if (mode == DATA_MODE)
        port |= (1<<RS);
    if (i2c_start(PCF8574) != 0)
        return 1;                             // BAD or MISSING
    i2c_write((c & 0xF0) | port | (1<<EN));   // high nybble
    i2c_write((c << 4) | port | (0<<EN));
    if (mode == INIT_MODE)
        _delay_ms(5);
    i2c_write((c << 4) | port | (1<<EN));     // low nybble
    i2c_write(port | (0<<EN));
    i2c_stop();
    if (mode == CMD_MODE && c <= 2) {
        lcd_line = 0;
        _delay_ms(2);            // CLRHOME or HOME
    }
    return 0;                   // GOOD return
}

void lcd_backlight(uint8_t on)
{
    if (on) backlight = (1<<BL);
    else backlight = 0;
}

void lcd_command(uint8_t c)
{
    lcd_wr_val_mode(c, CMD_MODE);
}

void lcd_data(uint8_t c)
{
    lcd_wr_val_mode(c, DATA_MODE);
}

void lcd_init(uint8_t dispAttr)
{
    i2c_init();
    _delay_ms(50);               // time to power up
    lcd_wr_val_mode(0x33, INIT_MODE);   // delay between nybbles
    lcd_wr_val_mode(0x32, CMD_MODE);
    lcd_command(0x28);          // 4-bit mode
    lcd_command(0x0c);          // display on
    lcd_command(0x06);          // cursor right
    lcd_command(0x01);          // CLRHOME
    lcd_command(dispAttr);
}

void Send_string(const uint8_t *p)
{
    while(*p)
    {
        lcd_data(*p);
        p++;
    }
}

void gotoXY(uint8_t y,uint8_t x)
{
    switch(y)
    {
        case 0: {y=0x00+0x80+x;break;}
        case 1: {y=0x40+0x80+x;break;}
        case 2: {y=0x10+0x80+x;break;}
        case 3: {y=0x50+0x80+x;break;}
            
        default:break;
    }
    
    lcd_command(y);
}
