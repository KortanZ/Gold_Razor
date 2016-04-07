/* 
*This head file for steer driver
*include initial and control
*/
#ifndef _STEERDRIVER_H
#define _STEERDRIVER_H 

#include "common.h"

#define MIDLINE_EXPECT_DUTY 1432

extern void Steer_Init(void);
extern void Steer_Duty_Change(uint32 tagetDuty);

#endif