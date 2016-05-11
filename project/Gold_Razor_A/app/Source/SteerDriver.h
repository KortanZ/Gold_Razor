/*
*This head file for steer driver
*include initial and control
*/
#ifndef _STEERDRIVER_H
#define _STEERDRIVER_H

#include "common.h"

#define STEER_MID_DUTY 1420
#define STEER_LEFT_DUTY 1225
#define STEER_RIGHT_DUTY 1560
#define STEER_MIDVALUE 80

extern void Steer_Init(void);
extern void Steer_Duty_Change(uint32 tagetDuty);

#endif