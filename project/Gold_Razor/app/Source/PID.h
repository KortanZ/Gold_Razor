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
}PIDStruct;

extern PIDStruct *speedCtrler;

void Speed_Controller(PIDStruct *motorCtrler, float32 expect, float32 real);
void SpeedCtrler_Init(void);

#endif	