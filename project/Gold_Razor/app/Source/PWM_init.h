#ifndef _PWM_INIT_H
#define _PWM_INIT_H

#include "common.h"

#define Motor_Fre 10000
#define LeftMotor_Negative PTA4
#define LeftMotor_Forward PTA5
#define RightMotor_Negative PTA6
#define RightMotor_Forward PTA7
/*#define Speed_Kp 2
#define Speed_Ki 0
#define Speed_Kd 0*/
extern uint32 PWM_Expect;

extern void Motor_init(void);
extern void Steer_init(void);
extern void MotorDuty_Change(uint32 Duty1,uint32 Duty2,uint32 Duty3,uint32 Duty4);
extern void Speed_Control(void);
extern uint32 angle_to_period(int8 deg);

#endif