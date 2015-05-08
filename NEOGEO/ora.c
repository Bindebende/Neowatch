//
//  ora.c
//  NEOGEO
//
//  Created by Bendegúz Hoffmann on 2014. 12. 20..
//  Copyright (c) 2014. Bendegúz Hoffmann. All rights reserved.
//
//

#include "ora.h"
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
volatile uint8_t second,minute,hour,old_second,old_hour;


void beolv(void)
{
    uint8_t j=1, temperature=0;
    uint8_t heading=0;
    uint8_t second1='A',minute1='B',hour1='C',second2='D',minute2='E',hour2='F';
    
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
            
            
            second=((second2-'0')*10);
            second+=second1-'0';
            
            minute=((minute2-'0')*10);
            minute+=minute1-'0';
            
            hour=((hour2-'0')*10);
            hour+=hour1-'0';
            
         
          //  lcd_data(hour2);
          //  lcd_data(hour1);
          //  lcd_data(':');
          //
          //  lcd_data(minute2);
          //  lcd_data(minute1);
          //  lcd_data(':');
            
          //  lcd_data(second2);
          //  lcd_data(second1);
            
          //  Send_string("        ");
            
        }
        
        
        //getLSM303_accel(accel);
        // getLSM303_mag(mag);
        
        //heading=getTiltHeading(mag, accel);
        
        //gotoXY(3, 15);
        
        //lcd_data((heading/100%10)+'0');
        //lcd_data((heading/10%10)+'0');
        //lcd_data((heading%10)+'0');
        
        //gotoXY(0, 0);
        
        
    }
}



void led_set_Task(void)//uint8_t* led_sec_index,uint8_t* led_min_index,uint8_t* led_hour_index)
{
    uint8_t led_sec_index=0,led_min_index=0,led_hour_index=0,i=0;
    const uint8_t led_numbers=12,nullazas=12;
    
    if(old_second!=second)
        
    {
        switch (hour)
        {
            case 0  : led_hour_index=0;break;
            case 1  : led_hour_index=1;break;
            case 2  : led_hour_index=2;break;
            case 3  : led_hour_index=3;break;
            case 4  : led_hour_index=4;break;
            case 5  : led_hour_index=5;break;
            case 6  : led_hour_index=6;break;
            case 7  : led_hour_index=7;break;
            case 8  : led_hour_index=8;break;
            case 9  : led_hour_index=9;break;
            case 10 : led_hour_index=10;break;
            case 11 : led_hour_index=11;break;
                
                
            case 12  : led_hour_index=0;break;
            case 13  : led_hour_index=1;break;
            case 14  : led_hour_index=2;break;
            case 15  : led_hour_index=3;break;
            case 16  : led_hour_index=4;break;
            case 17  : led_hour_index=5;break;
            case 18  : led_hour_index=6;break;
            case 19  : led_hour_index=7;break;
            case 20  : led_hour_index=8;break;
            case 21  : led_hour_index=9;break;
            case 22  : led_hour_index=10;break;
            case 23  : led_hour_index=11;break;
            default : break;
                
        }

        switch (minute)
        {
            case 0  : led_min_index=11;break;
            case 1  : led_min_index=11;break;
            case 2  : led_min_index=11;break;
            case 3  : led_min_index=11;break;
            case 4  : led_min_index=11;break;
            case 5  : led_min_index=0;break;
            case 6  : led_min_index=0;break;
            case 7  : led_min_index=0;break;
            case 8  : led_min_index=0;break;
            case 9  : led_min_index=0;break;
            case 10 : led_min_index=1;break;
            case 11 : led_min_index=1;break;
            case 12 : led_min_index=1;break;
            case 13 : led_min_index=1;break;
            case 14 : led_min_index=1;break;
            case 15 : led_min_index=2;break;
            case 16 : led_min_index=2;break;
            case 17 : led_min_index=2;break;
            case 18 : led_min_index=2;break;
            case 19 : led_min_index=2;break;
            case 20 : led_min_index=3;break;
            case 21 : led_min_index=3;break;
            case 22 : led_min_index=3;break;
            case 23 : led_min_index=3;break;
            case 24 : led_min_index=3;break;
            case 25 : led_min_index=4;break;
            case 26 : led_min_index=4;break;
            case 27 : led_min_index=4;break;
            case 28 : led_min_index=4;break;
            case 29 : led_min_index=4;break;
            case 30 : led_min_index=5;break;
            case 31 : led_min_index=5;break;
            case 32 : led_min_index=5;break;
            case 33 : led_min_index=5;break;
            case 34 : led_min_index=5;break;
            case 35 : led_min_index=6;break;
            case 36 : led_min_index=6;break;
            case 37 : led_min_index=6;break;
            case 38 : led_min_index=6;break;
            case 39 : led_min_index=6;break;
            case 40 : led_min_index=7;break;
            case 41 : led_min_index=7;break;
            case 42 : led_min_index=7;break;
            case 43 : led_min_index=7;break;
            case 44 : led_min_index=7;break;
            case 45 : led_min_index=8;break;
            case 46 : led_min_index=8;break;
            case 47 : led_min_index=8;break;
            case 48 : led_min_index=8;break;
            case 49 : led_min_index=8;break;
            case 50 : led_min_index=9;break;
            case 51 : led_min_index=9;break;
            case 52 : led_min_index=9;break;
            case 53 : led_min_index=9;break;
            case 54 : led_min_index=9;break;
            case 55 : led_min_index=10;break;
            case 56 : led_min_index=10;break;
            case 57 : led_min_index=10;break;
            case 58 : led_min_index=10;break;
            case 59 : led_min_index=10;break;
            case 60 : led_min_index=10;break;
                
                
            default : break;
                
        }
        
        switch (second)
        {
            case 0  : led_sec_index=11;break;
            case 1  : led_sec_index=11;break;
            case 2  : led_sec_index=11;break;
            case 3  : led_sec_index=11;break;
            case 4  : led_sec_index=11;break;
            case 5  : led_sec_index=0;break;
            case 6  : led_sec_index=0;break;
            case 7  : led_sec_index=0;break;
            case 8  : led_sec_index=0;break;
            case 9  : led_sec_index=0;break;
            case 10 : led_sec_index=1;break;
            case 11 : led_sec_index=1;break;
            case 12 : led_sec_index=1;break;
            case 13 : led_sec_index=1;break;
            case 14 : led_sec_index=1;break;
            case 15 : led_sec_index=2;break;
            case 16 : led_sec_index=2;break;
            case 17 : led_sec_index=2;break;
            case 18 : led_sec_index=2;break;
            case 19 : led_sec_index=2;break;
            case 20 : led_sec_index=3;break;
            case 21 : led_sec_index=3;break;
            case 22 : led_sec_index=3;break;
            case 23 : led_sec_index=3;break;
            case 24 : led_sec_index=3;break;
            case 25 : led_sec_index=4;break;
            case 26 : led_sec_index=4;break;
            case 27 : led_sec_index=4;break;
            case 28 : led_sec_index=4;break;
            case 29 : led_sec_index=4;break;
            case 30 : led_sec_index=5;break;
            case 31 : led_sec_index=5;break;
            case 32 : led_sec_index=5;break;
            case 33 : led_sec_index=5;break;
            case 34 : led_sec_index=5;break;
            case 35 : led_sec_index=6;break;
            case 36 : led_sec_index=6;break;
            case 37 : led_sec_index=6;break;
            case 38 : led_sec_index=6;break;
            case 39 : led_sec_index=6;break;
            case 40 : led_sec_index=7;break;
            case 41 : led_sec_index=7;break;
            case 42 : led_sec_index=7;break;
            case 43 : led_sec_index=7;break;
            case 44 : led_sec_index=7;break;
            case 45 : led_sec_index=8;break;
            case 46 : led_sec_index=8;break;
            case 47 : led_sec_index=8;break;
            case 48 : led_sec_index=8;break;
            case 49 : led_sec_index=8;break;
            case 50 : led_sec_index=9;break;
            case 51 : led_sec_index=9;break;
            case 52 : led_sec_index=9;break;
            case 53 : led_sec_index=9;break;
            case 54 : led_sec_index=9;break;
            case 55 : led_sec_index=10;break;
            case 56 : led_sec_index=10;break;
            case 57 : led_sec_index=10;break;
            case 58 : led_sec_index=10;break;
            case 59 : led_sec_index=10;break;
            case 60 : led_sec_index=10;break;
                
            default : break;
        }
        old_second=second;
        
        led_ertekadas(nullazas, 0, 0, 0);
        
        led_ertekadas(led_sec_index, 0, 1, 0);
        
        led_ertekadas(led_hour_index, 1, 0, 0);
        
        
        led_ertekadas(led_min_index, 0, 0, 1);
        
        
        for(i=0;i<12;i++)
        {
            if(led_hour_index==led_min_index)led_ertekadas(led_min_index, 1, 1, 1);
            if(led_hour_index==led_sec_index)led_ertekadas(led_sec_index, 1, 1, 1);
            if(led_min_index==led_sec_index)led_ertekadas(led_sec_index, 1, 1, 1);
        }
        
        ws2812_setleds(led, led_numbers);
    }
}
void temperature_display_Task(void)
{
    const uint8_t nullazas=12;
    uint8_t temp=0,temperature=0,temperature_index=0,old_temp=255;
    //gotoXY(0, 0);
    //Send_string("Temperature:");
    
    
    temp=Adafruit_MCP9808readTempC();
    
    //lcd_data(temp/10%10+'0');
    //lcd_data(temp%10+'0');
    //lcd_data('C');
    //gotoXY(0, 0);
    
    temperature=(temp/10%10)*10;
    temperature+=temp%10;
    
    
    
    if(old_temp!=temperature)
    {
        //gotoXY(1,0);
        switch (temperature)
        {
            case 0  :  temperature_index=0;break;
            case 1  :  temperature_index=0;break;
            case 2  :  temperature_index=0;break;
            case 3  :  temperature_index=0;break;
            case 4  :  temperature_index=1;break;
            case 5  :  temperature_index=1;break;
            case 6  :  temperature_index=1;break;
            case 7  :  temperature_index=1;break;
            case 8  :  temperature_index=2;break;
            case 9  :  temperature_index=2;break;
            case 10  :  temperature_index=2;break;
            case 11  :  temperature_index=2;break;
            case 12 :  temperature_index=3;break;
            case 13 :  temperature_index=3;break;
            case 14 :  temperature_index=3;break;
            case 15 :  temperature_index=3;break;
            case 16 :  temperature_index=4;break;
            case 17 :  temperature_index=4;break;
            case 18 :  temperature_index=4;break;
            case 19 :  temperature_index=4;break;
            case 20 :  temperature_index=5;break;
            case 21 :  temperature_index=5;break;
            case 22 :  temperature_index=5;break;
            case 23 :  temperature_index=5;break;
            case 24 :  temperature_index=6;break;
            case 25 :  temperature_index=6;break;
            case 26 :  temperature_index=6;break;
            case 27 :  temperature_index=6;break;
            case 28 :  temperature_index=7;break;
            case 29 :  temperature_index=7;break;
            case 30 :  temperature_index=7;break;
            case 31 :  temperature_index=7;break;
            case 32 :  temperature_index=8;break;
            case 33 :  temperature_index=8;break;
            case 34 :  temperature_index=8;break;
            case 35 :  temperature_index=8;break;
            case 36 :  temperature_index=9;break;
            case 37 :  temperature_index=9;break;
            case 38 :  temperature_index=9;break;
            case 39 :  temperature_index=9;break;
            case 40 :  temperature_index=10;break;
            case 41 :  temperature_index=10;break;
            case 42 :  temperature_index=10;break;
            case 43 :  temperature_index=10;break;
            case 44 :  temperature_index=11;break;
            case 45 :  temperature_index=11;break;
            case 46 :  temperature_index=11;break;
            case 47 :  temperature_index=11;break;
                
            default : break;
            
        }
        
       // lcd_data((temperature/10%10)+'0');
       // lcd_data((temperature%10)+'0');
        
        //gotoXY(0, 0);
    
     led_ertekadas(nullazas, 0, 0, 0);
     led_ertekadas(temperature_index, 1, 0, 0);
        ws2812_setleds(led, 12);
        old_temp=temperature;
    }
}

void compass_Task(void)
{
    const uint8_t nullazas=12;
    int old_heading=0;
    
    vector a= {0,0,0};
    vector m= {0,0,0};
    vector p= {0, -1, 0};
    int heading = 0;
    
    compass_read_data(&a, &m);
    heading = get_heading(&a,&m,&p);
    
    led_ertekadas(nullazas, 0, 0, 0);
    
    if(heading != old_heading)
    {
        
        if((0<heading)   && (heading<=30))     led_ertekadas(11, 0, 1, 0);
        if((30<heading)  && (heading<=60))     led_ertekadas(0, 0, 1, 0);
        if((60<heading)  && (heading<=90))     led_ertekadas(1, 0, 1, 0);
        if((90<heading)  && (heading<=120))    led_ertekadas(2, 0, 1, 0);
        if((120<heading) && (heading<=150))    led_ertekadas(3, 0, 1, 0);
        if((150<heading) && (heading<=180))    led_ertekadas(4, 0, 1, 0);
        if((180<heading) && (heading<=210))    led_ertekadas(5, 0, 1, 0);
        if((210<heading) && (heading<=240))    led_ertekadas(6, 0, 1, 0);
        if((240<heading) && (heading<=270))    led_ertekadas(7, 0, 1, 0);
        if((270<heading) && (heading<=300))    led_ertekadas(8, 0, 1, 0);
        if((300<heading) && (heading<=330))    led_ertekadas(9, 0, 1, 0);
        if((330<heading) && (heading<=360))    led_ertekadas(10, 0, 1, 0);
    
        ws2812_setleds(led, 12);
        old_heading=heading;
    }


}














