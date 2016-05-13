/*
*This head file for steer driver
*include initial and control
*/
#ifndef _STEERDRIVER_H
#define _STEERDRIVER_H

#include "common.h"

#define STEER_MID_DUTY 1635
#define STEER_LEFT_DUTY 1460
#define STEER_RIGHT_DUTY 1760
//#define STEER_MIDVALUE 85

extern uint8 steerMidValue;

extern void Steer_Init(void);
extern void Steer_Duty_Change(uint32 tagetDuty);


#endif