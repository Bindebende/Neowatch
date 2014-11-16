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
#include "MCP9808.h"
#include "LSM303.h"


void gps_send(char[]);
int gps_recive(char *);
int strlen(char* );
int comma_counter(int,char*);
void array_NULLing(char*);
int copy_from_message(int, char *,char*);
int GGA_message_check(char *,char *,char *,char *,char *,char *,char *);
void RMC_message_check(char *,char *);