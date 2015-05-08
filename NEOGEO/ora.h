//
//  ora.h
//  NEOGEO
//
//  Created by Bendegúz Hoffmann on 2014. 12. 20..
//  Copyright (c) 2014. Bendegúz Hoffmann. All rights reserved.
//

#ifndef __NEOGEO__ora__
#define __NEOGEO__ora__

#include <stdio.h>

void beolv(void);
void led_set_Task(void);//uint8_t* ,uint8_t* ,uint8_t* );
void temperature_display_Task(void);
void compass_Task(void);

extern volatile uint8_t mode;

#endif /* defined(__NEOGEO__ora__) */
