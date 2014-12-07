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

 char aa[5], a,value;

#define BAUD 9600

volatile uint8_t binary_semaphore_button ,count=0;

 char value,buffer[100],lati_value[15],longi_value[15],lati_dir,longi_dir;

int i,j;

int main(void)
{

    i=0;j=0;a=0;
    binary_semaphore_button=0;
    
    
    
    lcd_init(0x02);                 //sima lcd initbol jon a 0x02;
    lcd_backlight(1);
    lcd_command(0x01);
    
    lcd_command(0x01);
    
    PCMSK0 |= (1<<PCINT4);  // PCINT6 = PB6
    PCICR |= (1<<PCIE0);   //Enable Pin change interrupt
    sei();
   // struct cRGB led[12];
    
   // CLKPR=_BV(CLKPCE);
    //CLKPR=0;			  // set clock prescaler
    
    
    avr_uart_init();
    gps_init();
   
 
lcd_command(0x01);
    
    while(1)
    {
    }

}

ISR(USART1_RX_vect)
{
      value=UDR1;
    if()
    lcd_data(value);
}



ISR(PCINT0_vect)
{
   if(count%2)binary_semaphore_button=1;
   else{binary_semaphore_button=0;}
    count++;
}

