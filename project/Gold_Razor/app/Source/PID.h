#ifndef _PID_H_
#define _PID_H_

#include "common.h"

#define U_MAX 4800

typedef struct{
	float32 Kp;
	float32 Kd;
	float32 Ki;
	float32 error[3];
	float32 u[3];
	uint16 uMax;
}PIDStruct;

extern PIDStruct *motorCtrler;
extern PIDStruct *steerCtrler;
extern PIDStruct *diffCtrler;

void PID_Calc(PIDStruct *motorCtrler, float32 expect, float32 real);
PIDStruct *PID_Init(float32 setKp, float32 setKi, float32 setKd, uint16 threshold);
void All_PID_Init(void);

#endif	