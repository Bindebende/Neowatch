//
//  GPS.c
//  NEOGEO
//
//  Created by Bendegúz Hoffmann on 2014. 11. 16..
//  Copyright (c) 2014. Bendegúz Hoffmann. All rights reserved.
//

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include "GPS.h"
#include "uart.h"
#include "MCP9808.h"
#include "LSM303.h"




void gps_init(void)
{
    uart_send_string(PMTK_SET_BAUD_9600);
    uart_send_string(PMTK_SET_NMEA_OUTPUT_ALLDATA);
    uart_send_string(PMTK_SET_NMEA_UPDATE_1HZ);

}
/*
 * neogeo.c
 *
 * Created: 2014.07.12. 20:08:47
 *  Author: Bende
 */



void array_NULLing(char* array)
{
    for(;*array !='\0';array++) *array=0;
}



uint8_t comma_counter(uint8_t comma, const char* message)
{
    uint8_t i=0;
    while(comma)						/* i variable will be the first index of the of the speed value when the                    while loop executes  */
    {
        if(*(message+i)==',')
        {
            comma--;
            i++;
        }
        i++;
    }
    return (i);
}

uint8_t copy_from_message(uint8_t i,char *message,char *destination)
{
    uint8_t index=0;
    while(1)
    {
        *(destination+index)=*(message+i);
        if (*(message+i)==',')return 0;
        i++;
        index++;
        
    }
    
}

uint8_t strlength(char *s)
{
    uint8_t i;
    for(i=0;*s !='\0';s++) i++;
    return (i-1);
}

void gps_send(char command[])
{
    uint8_t i=0,length=0;
    length=strlength(command);
    for(i=0;i<length;i++) avr_uart_send_byte(command[i]);
}

uint8_t gps_recive(char*time)                                                   /* time[10],Latitude[9],speed[6] array */
{
    uint8_t message[80];
    uint8_t i=0;
    
    
    for(i=0;i<80;i++) message[i]=0;
    
    for(i=0;message[i]=='<';i++) message[i]=avr_uart_receive_byte();                /* Itt will recive till'<'sign. (of end of message) */
    
    
    return 0;
    
}
/*$GPRMC,064951.000,A,2307.1256,N,12016.4438,E,0.03,165.48,260406,3.05,W,A*2C*/
void RMC_message_check(char *message, char *speed)
{
    if(message[3]=='R' && message[4]=='M' && message[5]=='C')
    {
        char *ptr ,speed1[6];
        ptr=speed1;
        array_NULLing(speed1);
        while( *speed !='\0')
        {
            *ptr= *speed;
            ptr++;
            speed++;
        }
        
    }
}

/*$GPGGA,064951.000,2307.1256,N,12016.4438,E,1,8,0.95,39.9,M,17.8,M,,*65*/
uint8_t GGA_message_check(char *message,char *time,char *Latitude,char *N_S_Indicator,char *Longitude,char *E_W_Indicator,char *altitude)
{
    uint8_t fix=0;
    char *ptr;
    if(message[3]=='G' && message[4]=='G' && message[5]=='A')                       /* check if we got the GGA protocol */
    {
                                                                                    /* write the time value in to time array */
        
        char message1[100],time1[10],Latitude1[10],Longitude1[10],altitude1[10];
        
        
        ptr=message1;
        array_NULLing(message1);
        while( *message !='\0')                                                     /* copy time, message arrays to time1, message1 */
        {
            *ptr= *message;
            ptr++;
            message++;
        }
        
        ptr=time1;
        array_NULLing(time1);
        while( *time !='\0')
        {
            *ptr= *time;
            ptr++;
            time++;
        }
        ptr=Latitude1;
        array_NULLing(Latitude1);
        while( *Latitude !='\0')
        {
            *ptr= *Latitude;
            ptr++;
            Latitude++;
        }
        
        ptr=Longitude1;
        array_NULLing(Longitude1);
        while( *Longitude !='\0')
        {
            *ptr= *time;
            ptr++;
            Longitude++;
        }
        ptr=altitude1;
        array_NULLing(altitude1);
        while( *Longitude !='\0')
        {
            *ptr= *altitude;
            ptr++;
            altitude++;
        }
        
        copy_from_message(comma_counter(1,message1),message1,time1);
        copy_from_message(comma_counter(2,message1),message1,Latitude1);
        copy_from_message(comma_counter(4,message1),message1,Longitude1);
        copy_from_message(comma_counter(9,message1),message1,altitude1);
        *N_S_Indicator=message[28];
        *E_W_Indicator=message[41];
        
        fix=message[44];
    }
    return(fix);
}
/*
 uint8_t main (void)
 {
 char message[80],time[10],Latitude[10],Longitude[10],altitude[10],speed[6];
 char N/S_Indicator=0;E/W_Indicator=0;
 
 gps_send("valami");
 gps_recive(message);
 
	if(message[3]=='R' && message[4]=='M' && message[5]=='C')	RMC_message_check(message,speed);
 
	if(message[3]=='G' && message[4]=='G' && message[5]=='A')	GGA_message_check(message,time,Latitude,N/S_Indicator,Longitude,E/W_Indicator,altitude);
 return 0;
 }
 */

void clock(void)
{
    /*clock fgv maga az ora mukodese */
/*
    second1++;
    
    if(second1>'9')
    {
        
        if(second2>'4' && second1>'9')
        {
            minute1++;
            if(minute1>'9')
            {
                if(minute2>'4' && minute1>'9')
                {
                    hour1++;
                    if(hour1>'3')
                    {
                        hour2++;
                        if(hour2>'2' && hour1>'3')hour2='0';
                        
                        
                        hour1='0';
                    }
                }
                
                minute2++;
                minute1='0';
            }
            
        second2='0';
        }
       
        second2++;
        second1='0';
    }
*/
}

void number_to_array(int number, uint8_t *array_ptr)
{
    uint8_t i;
    
    *(array_ptr+ 5)=number/100000;
    *(array_ptr+ 4)=number/10000%10;
    *(array_ptr+ 3)=number/1000%10;
    *(array_ptr+ 2)=number/100%10;
    *(array_ptr+ 1)=number%100/10;
    *(array_ptr+ 0)=number%10;
    
    for(i=0;i<6;i++)printf("array:%d\n",*(array_ptr+i));
}





