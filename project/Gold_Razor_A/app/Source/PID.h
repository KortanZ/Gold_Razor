#ifndef _PID_H_
#define _PID_H_

#include "common.h"

#define U_MAX 4800

typedef struct
{
	float32 Kp;
	float32 Kd;
	float32 Ki;
}PIDParaStruct;

typedef struct{
	PIDParaStruct *para;
	float32 error[3];
	float32 u[3];
}PIDStruct;

extern PIDStruct *speedCtrler;
extern PIDParaStruct *speedCtrlerPara;

extern PIDStruct *steerCtrler;
extern PIDParaStruct *steerCtrlerStPara;
extern PIDParaStruct *steerCtrlerCurvPara;

extern PIDStruct *differCtrler;
extern PIDParaStruct *differCtrlerStPara;
extern PIDParaStruct *differCtrlerCurvPara;
extern float32 enhance;

extern int16 motorThersh;
extern int16 steerThersh;

void Speed_Controller(PIDStruct *motorCtrler, float32 expect, float32 real);
void Steer_Controller(PIDStruct *SteerCon_Data, float32 expect, float32 real);

void SpeedCtrler_Init(void);
void SteerCtrler_Init(void);
void DifferCtrler_Init(void);

#endif