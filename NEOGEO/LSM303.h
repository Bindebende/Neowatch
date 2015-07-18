//
//  LSM303.h
//  NEOGEO
//
//  Created by Bendegúz Hoffmann on 2014. 11. 16..
//  Copyright (c) 2014. Bendegúz Hoffmann. All rights reserved.
//

#ifndef __NEOGEO__LSM303__
#define __NEOGEO__LSM303__

#define SCALE 2  // accel full-scale, should be 2, 4, or 8

/* LSM303 Address definitions */
#define LSM303_MAG  0x1E  // assuming SA0 grounded
#define LSM303_ACC  0x18  // assuming SA0 grounded

#define X 0
#define Y 1
#define Z 2

typedef struct vector
{
    //	float x, y, z;
    float x, y, z;
} vector;

/* LSM303 Register definitions */
#define CTRL_REG1_A         0x20
#define CTRL_REG2_A         0x21
#define CTRL_REG3_A         0x22
#define CTRL_REG4_A         0x23
#define CTRL_REG5_A         0x24
#define HP_FILTER_RESET_A   0x25
#define REFERENCE_A         0x26
#define STATUS_REG_A        0x27
#define OUT_X_L_A           0x28
#define OUT_X_H_A           0x29
#define OUT_Y_L_A           0x2A
#define OUT_Y_H_A           0x2B
#define OUT_Z_L_A           0x2C
#define OUT_Z_H_A           0x2D
#define INT1_CFG_A          0x30
#define INT1_SOURCE_A       0x31
#define INT1_THS_A          0x32
#define INT1_DURATION_A     0x33
#define CRA_REG_M           0x00
#define CRB_REG_M           0x01
#define MR_REG_M            0x02
#define OUT_X_H_M           0x03
#define OUT_X_L_M           0x04
#define OUT_Y_H_M           0x05
#define OUT_Y_L_M           0x06
#define OUT_Z_H_M           0x07
#define OUT_Z_L_M           0x08
#define SR_REG_M            0x09
#define IRA_REG_M           0x0A
#define IRB_REG_M           0x0B
#define IRC_REG_M           0x0C

void LSM303_init(void);

void getLSM303_accel(int * rawValues);
void getLSM303_mag(int * rawValues);
float getTiltHeading(int * magValue, float * accelValue);
float vector_dot(const vector *a, const vector *b);
void vector_normalize(vector *a);
void vector_cross(const vector *a, const vector *b, vector *out);
int get_heading(vector *a, vector *m, vector *p);
void compass_read_data(vector *a, vector *m);





#endif /* defined(__NEOGEO__LSM303__) */
