/*
*This head file for steer driver
*include initial and control
*/
#ifndef _STEERDRIVER_H
#define _STEERDRIVER_H

#include "common.h"

/* blank */
// #define STEER_MID_DUTY 705
// #define STEER_LEFT_DUTY 625
// #define STEER_RIGHT_DUTY 775
//#define STEER_MIDVALUE 85

/* red */
#define STEER_MID_DUTY 772
#define STEER_LEFT_DUTY 695
#define STEER_RIGHT_DUTY 850

extern uint8 steerMidValue;

extern void Steer_Init(void);
extern void Steer_Duty_Change(uint32 tagetDuty);


#endif