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

typedef enum {
	MOTOR_LEFT, 
	MOTOR_RIGHT,
}MotorPosition;

extern int32 PWM_Expect_Base;
extern int32 PWM_Expect;

void Motor_Init(void);
void Motor_Duty_Change(MotorPosition motorPos, int32 tagetDuty);
float32 PulseNum_To_PWM(float32 pulseNum);
float32 PWM_To_Pulse(uint32 pwm);
#endif