//
//  LSM303.c
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
#include <math.h>


vector m_min = {-356, -563, -445};
vector m_max = {708, 470, 440};


#define PI 3.1415
void LSM303_init(void)
{
    //enable accelerometer
    i2c_start(0x30);
    i2c_write(0x20); // CTRL_REG1_A
    i2c_write(0x27); // normal power mode, 50 Hz data rate, all axes enabled
    i2c_stop();
    
    //enable magnetometer
    i2c_start(0x3C);// write mag
    i2c_write(0x02); // MR_REG_M
    i2c_write(0x00); // continuous conversion mode
    i2c_stop();
    
    
}


void compass_read_data(vector *a, vector *m)
{
    // read accelerometer values
    i2c_start(0x30);
    i2c_write(0xa8); // OUT_X_L_A, MSB set to enable auto-increment
    i2c_start(0x31);		  // repeated start
                    // read acc
    unsigned char axl = i2c_readAck();
    unsigned char axh = i2c_readAck();
    unsigned char ayl = i2c_readAck();
    unsigned char ayh = i2c_readAck();
    unsigned char azl = i2c_readAck();
    unsigned char azh = i2c_readNak();
    i2c_stop();
    
    // read magnetometer values
    i2c_start(0x3C);    // write mag
    i2c_write(0x03);    // OUTXH_M, MSB set to enable auto-increment
    i2c_start(0x3D);    // repeated start
                        // read mag
    unsigned char mxh = i2c_readAck();
    unsigned char mxl = i2c_readAck();
    unsigned char myh = i2c_readAck();
    unsigned char myl = i2c_readAck();
    unsigned char mzh = i2c_readAck();
    unsigned char mzl = i2c_readNak();
    i2c_stop();
    
    a->x = axh << 8 | axl;
    a->y = ayh << 8 | ayl;
    a->z = azh << 8 | azl;
    m->x = mxh << 8 | mxl;
    m->y = myh << 8 | myl;
    m->z = mzh << 8 | mzl;
}

int get_heading(vector *a, vector *m, vector *p)
{
    
    // shift and scale
    m->x = (m->x - m_min.x) / (m_max.x - m_min.x) * 2 - 1.0;
    m->y = (m->y - m_min.y) / (m_max.y - m_min.y) * 2 - 1.0;
    m->z = (m->z - m_min.z) / (m_max.z - m_min.z) * 2 - 1.0;
    
    
    vector E;
    vector N;
    
    // cross magnetic vector (magnetic north + inclination) with "down" (acceleration vector) to produce "east"
    vector_cross(m, a, &E);
    vector_normalize(&E);
    
    // cross "down" with "east" to produce "north" (parallel to the ground)
    vector_cross(a, &E, &N);
    vector_normalize(&N);
    
    // compute heading
    int heading = round(atan2(vector_dot(&E, p), vector_dot(&N, p)) * 180 / M_PI);
    if (heading < 0)
        heading += 360;
    return heading;
}


void vector_cross(const vector *a, const vector *b, vector *out)
{
    out->x = a->y * b->z - a->z * b->y;
    out->y = a->z * b->x - a->x * b->z;
    out->z = a->x * b->y - a->y * b->x;
}

float vector_dot(const vector *a, const vector *b)
{
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

void vector_normalize(vector *a)
{
    float mag = sqrt(vector_dot(a, a));
    a->x /= mag;
    a->y /= mag;
    a->z /= mag;
}












