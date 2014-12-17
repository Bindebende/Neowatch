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
#include <math.h>

void beolv(uint8_t*,uint8_t*,uint8_t*);

#define BAUD 9600

volatile uint8_t count=0,buffer[100],second,minute,hour,second1,minute1,hour1,old_second,old_minute,old_hour,second2,minute2,hour2;
volatile uint8_t value,buffer_index,temp,temp=0,temp1=0,temp2=0;


int main(void)
{
    second2=0;minute2=0;hour2=0;second=0;minute=0;hour=0;second1=0;minute1=0;hour1=0;old_second=0;old_minute=0;old_hour=0;
    const uint8_t led_numbers=12;
    
    uint8_t mcp9808[16], led_sec_index=0,led_min_index=0,led_hour_index=0,i; uint16_t temperature=0;
    buffer_index=0;

    
    lcd_init(0x02);                             //sima lcd initbol jon a 0x02;
    lcd_backlight(1);
    lcd_command(0x01);
    
    lcd_command(0x01);
    
    PCMSK0 |= (1<<PCINT4);                       // PCINT4 = PB4
    PCICR |= (1<<PCIE0);                        //Enable Pin change interrupt
    struct cRGB led[12];
    sei();
    
    
    for(i=0;i<12;i++)                       //minden ledet nullázni
    {
        led[i].r=00;led[i].g=00;led[i].b=00;
        ws2812_setleds(led,led_numbers);
    }

    
    
    CLKPR|=(1<<CLKPCE);
    CLKPR=0;                                    // set clock prescaler to 0
    
    
    avr_uart_init();
    gps_init();
   
    old_second=255;
    old_minute=255;
    old_hour=255;

    lcd_command(0x01);
  

   /* while (1)
    {
        //sprintf(mcp9808,"%lf",MCP9808_read_temp());
        //Send_string(mcp9808);
        
        
        Send_string("Temperature:");
        
        temperature=Adafruit_MCP9808readTempC();
        lcd_data(temperature/10%10+'0');
        lcd_data(temperature%10+'0');
        lcd_data('C');
        
        
        gotoXY(0,0);
    }*/
    
    while(1)
    {
        beolv(&led_sec_index,&led_min_index,&led_hour_index);
        
        
        if(old_hour!=hour)
        {
            switch (temp2)
            {
                case 0  : led_hour_index=11;break;
                case 1  : led_hour_index=0;break;
                case 2  : led_hour_index=1;break;
                case 3  : led_hour_index=2;break;
                case 4  : led_hour_index=3;break;
                case 5  : led_hour_index=4;break;
                case 6  : led_hour_index=5;break;
                case 7  : led_hour_index=6;break;
                case 8  : led_hour_index=7;break;
                case 9  : led_hour_index=8;break;
                case 10 : led_hour_index=9;break;
                case 11 : led_hour_index=10;break;
                case 12  : led_hour_index=11;break;
                case 13  : led_hour_index=0;break;
                case 14  : led_hour_index=1;break;
                case 15  : led_hour_index=2;break;
                case 16  : led_hour_index=3;break;
                case 17  : led_hour_index=4;break;
                case 18  : led_hour_index=5;break;
                case 19  : led_hour_index=6;break;
                case 20  : led_hour_index=7;break;
                case 21  : led_hour_index=8;break;
                case 22 : led_hour_index=9;break;
                case 23 : led_hour_index=10;break;
                    
                default : break;
            }
            old_hour=hour1;
            led_hour_index++;
        }

        
        if(old_minute!=minute1)
        {
            switch (temp1)
            {
                case 0  : led_min_index=11;break;
                case 1  : led_min_index=11;break;
                case 2  : led_min_index=11;break;
                case 3  : led_min_index=11;break;
                case 4  : led_min_index=11;break;
                case 5  : led_min_index=0;break;
                case 10 : led_min_index=1;break;
                case 15 : led_min_index=2;break;
                case 20 : led_min_index=3;break;
                case 25 : led_min_index=4;break;
                case 30 : led_min_index=5;break;
                case 35 : led_min_index=6;break;
                case 40 : led_min_index=7;break;
                case 45 : led_min_index=8;break;
                case 50 : led_min_index=9;break;
                case 55 : led_min_index=10;break;
                default : break;
                    
            }
            old_minute=minute1;
        }
        
        
        
        if(old_second!=second1)
        {
            switch (temp)
            {
                case 0  : led_sec_index=11;break;
                case 1  : led_sec_index=11;break;
                case 2  : led_sec_index=11;break;
                case 3  : led_sec_index=11;break;
                case 4  : led_sec_index=11;break;
                case 5  : led_sec_index=0;break;
                case 10 : led_sec_index=1;break;
                case 15 : led_sec_index=2;break;
                case 20 : led_sec_index=3;break;
                case 25 : led_sec_index=4;break;
                case 30 : led_sec_index=5;break;
                case 35 : led_sec_index=6;break;
                case 40 : led_sec_index=7;break;
                case 45 : led_sec_index=8;break;
                case 50 : led_sec_index=9;break;
                case 55 : led_sec_index=10;break;
                default : break;
            }
            for(i=0;i<12;i++)
            {
            led[i].r=0;led[i].g=0;led[i].b=0;
            }
            
            for(i=0;i<12;i++)
            {
                if(led_sec_index==i){led[i].r=0;led[i].g=25;led[i].b=0;}
            }
            
            for(i=0;i<12;i++)
            {
                if(led_min_index==i){led[i].r=0;led[i].g=0;led[i].b=25;}
            }
            
            for(i=0;i<12;i++)
            {
                if(led_hour_index==i){led[i].r=25;led[i].g=0;led[i].b=0;}
            }
            for(i=0;i<12;i++)
            {
                if(led_hour_index==led_min_index){led[led_min_index].r=25;led[led_min_index].g=25;led[led_min_index].b=25;}
                if(led_hour_index==led_sec_index){led[led_sec_index].r=25;led[led_sec_index].g=25;led[led_sec_index].b=25;}
                if(led_min_index==led_sec_index){led[led_min_index].r=25;led[led_min_index].g=25;led[led_min_index].b=25;}
            }
            
            ws2812_setleds(led, led_numbers);
            }

        old_second=second1;
        }
    

    
}

ISR(USART1_RX_vect)
{
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
        }
        else
        {
            // pin is low
        }
    }
}

void beolv(uint8_t* led_sec_index,uint8_t* led_min_index,uint8_t* led_hour_index )
{
    uint8_t j=1,k=1,l=1, temperature=0;
    

    if(buffer[buffer_index]=='$')
    {
        
        
        for(j=0;j<100;j++) if(buffer[j]=='G' && buffer[j+1]=='G' && buffer[j+2]=='A')
        {
            
            hour2=buffer[j+4];
            hour1=buffer[j+5];
            minute2=buffer[j+6];
            minute1=buffer[j+7];
            second2=buffer[j+8];
            second1=buffer[j+9];
            
            hour=(hour2*10);
            hour+=hour1;
            minute=(minute2*10);
            minute+=minute1;
            second=(second2*10);
            second+=second1;
            
            if(j)
            {
                temp=((second2-'0')*10);
                temp+=second1-'0';
                
                *led_sec_index=temp/5;
                *led_sec_index-=1;
                j=0;
            }
            
            if(k)
            {
                temp1=((minute2-'0')*10);
                temp1+=minute1-'0';
                
                *led_min_index=temp1/5;
                *led_min_index-=1;
                k=0;
            }
            if(l)
            {
                temp2=((hour2-'0')*10);
                temp2+=hour1-'0';
                
                *led_hour_index=temp2/5;
                *led_hour_index-=1;
                l=0;
            }
            
        }
        
        
        lcd_data(hour2);
        lcd_data(hour1);
        lcd_data(':');
        
        lcd_data(minute2);
        lcd_data(minute1);
        lcd_data(':');
        
        lcd_data(second2);
        lcd_data(second1);
        
        
        gotoXY(1, 0);
        
        Send_string("Temperature:");
        
        temperature=Adafruit_MCP9808readTempC();
        lcd_data(temperature/10%10+'0');
        lcd_data(temperature%10+'0');
        lcd_data('C');
        
        

        
        gotoXY(0, 0);
        
        
    }


}


