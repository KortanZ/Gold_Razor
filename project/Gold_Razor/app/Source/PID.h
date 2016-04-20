#ifndef _PID_H_
#define _PID_H_

#include "common.h"

typedef struct{
	float32 Kp;
	float32 Kd;
	float32 Ki;
	float32 error[3];
	float32 u[3];
}PIDStruct;

extern PIDStruct *leftMotorCtrl;
extern PIDStruct *rightMororCtrl;

void Motor_Controller(PIDStruct *motorCtrler, float32 expect, float32 real);
PIDStruct *MotorCtrler_Init(void);

#endif	