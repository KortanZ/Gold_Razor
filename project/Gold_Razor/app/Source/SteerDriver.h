/* 
*This head file for steer driver
*include initial and control
*/
#ifndef _STEERDRIVER_H
#define _STEERDRIVER_H 

#include "common.h"

#define STEER_MID_DUTY 1428
#define STEER_LEFT_DUTY 1312
#define STEER_RIGHT_DUTY 1547

extern void Steer_Init(void);
extern void Steer_Duty_Change(uint32 tagetDuty);

#endif