/* 
*This head file for motor driver
*include initial and control
*/

#ifndef _MOTORDRIVER_H_
#define _MOTORDRIVER_H_ 

#include "common.h"

#define MOTOR_FRE 10000				
#define MOTOR_LEFT_BACKWARD PTA4
#define MOTOR_LEFT_FORWARD PTA5
#define MOTOR_RIGHT_BACKWARD PTA6
#define MOTOR_RIGHT_FORWARD PTA7

enum MotorPosition {left, right};

extern uint32 PWM_Expect;

extern void Motor_Init(void);
void Motor_Duty_Change(MotorPosition motorPos, int32 tagetDuty);

#endif