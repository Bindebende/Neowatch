#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay.h>
#include "GPS.h"
#include "MCP9808.h"
#include "LSM303.h"
#include "uart.h"
#include "i2c.h"
#include "lcd.h"
#include "neopixel.h"
#include "ora.h"
#include <math.h>






volatile uint8_t buffer[100], buffer_index, mode;


int main(void)
{
    second=0;minute=0;hour=0;
    old_second=255;old_hour=255;
    
    const uint8_t led_numbers=12,nullazas=12;
    buffer_index=0;
    

    
    
    LSM303_init();
    avr_uart_init();
    gps_init();
    led_ertekadas(nullazas, 0, 0, 0);
    ws2812_setleds(led,led_numbers);

    
    
    
   // lcd_init(0x02);                                     //sima lcd initbol jon a 0x02;
   // lcd_backlight(1);
   // lcd_command(0x01);
   // lcd_command(0x01);
    
    
    PCMSK0 |= (1<<PCINT4);                              // PCINT4 = PB4
    PCICR  |= (1<<PCIE0);                               //Enable Pin change interrupt
    
    sei();
    
    //lcd_command(0x01);
    
    while(1)
    {
        beolv();
        
        switch(mode)
        {
            case 0 : led_set_Task();break;
            case 1 : temperature_display_Task();break;
            case 2 : compass_Task();
        }
        
    }
    
}
    



/*
 
 */







