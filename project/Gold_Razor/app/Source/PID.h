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

extern PIDStruct *speedCtrler;

void Speed_Controller(PIDStruct *motorCtrler, float32 expect, float32 real);
PIDStruct *SpeedCtrler_Init(float32 setKp, float32 setKd, float32 setKi);

#endif	