/*
*This head file for steer driver
*include initial and control
*/
#ifndef _STEERDRIVER_H
#define _STEERDRIVER_H

#include "common.h"
/* red */
#define STEER_MID_DUTY 790
#define STEER_LEFT_DUTY 710
#define STEER_RIGHT_DUTY 890

extern uint8 steerMidValue;

extern void Steer_Init(void);
extern void Steer_Duty_Change(uint32 tagetDuty);


#endif