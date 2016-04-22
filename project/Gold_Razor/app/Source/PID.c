#include "common.h"

PIDStruct *speedCtrler = NULL;
PIDStruct *steerCtrler = NULL;
PIDStruct *diffCtrler = NULL;

void Speed_PID_Calc(PIDStruct *motorCtrler, float32 expect, float32 real)
{
	/* previous difference PID */

	float32 incrementU;

	motorCtrler -> error[0] = expect - real;

	incrementU = (motorCtrler -> Kp) * ((motorCtrler -> error[0]) - (motorCtrler -> error[1]))
					 + (motorCtrler -> Ki) * (motorCtrler -> error[0]) + (motorCtrler -> Kd) 
					 * ((motorCtrler -> u[0]) - 2 * (motorCtrler -> u[1]) + (motorCtrler -> u[2]))
					 - (motorCtrler -> Kd) * ((motorCtrler -> u[0]) - (motorCtrler -> u[1]));

	/* anti-windup */
					 
	if ((motorCtrler -> u[1]) > U_MAX || (motorCtrler -> u[1]) < -U_MAX)
	{
		incrementU -= (motorCtrler -> Ki) * (motorCtrler -> error[0]);
	}

	motorCtrler -> u[0] = (motorCtrler -> u[1]) + incrementU; 

	motorCtrler -> u[2] = motorCtrler -> u[1];
	motorCtrler -> u[1] = motorCtrler -> u[0];
	motorCtrler -> error[1] = motorCtrler -> error[0]; 

	/* standard PID */

	// motorCtrler -> error[0] = expect - real;
	// incrementU = (motorCtrler -> Kp) * ((motorCtrler -> error[0]) - (motorCtrler -> error[1]))
	// 					+ (motorCtrler -> Ki) * (motorCtrler -> error[0]) + (motorCtrler -> Kd)
	// 					* ((motorCtrler -> error[0]) - 2 * (motorCtrler -> error[1]) + (motorCtrler -> error[2]));

	// motorCtrler -> u[0] = (motorCtrler -> u[1]) + incrementU; 
	
	// motorCtrler -> u[2] = motorCtrler -> u[1];
	// motorCtrler -> u[1] = motorCtrler -> u[0];
	// motorCtrler -> error[2] = motorCtrler -> error[1];
	// motorCtrler -> error[1] = motorCtrler -> error[0];
}

PIDStruct *PID_Init(float32 setKp, float32 setKi, float32 setKd)
{
	/* Initial PID speedCtrler */
	int8 i;

	PIDStruct *controller = (PIDStruct *)malloc(sizeof(PIDStruct));

	if (NULL == controller)
	{
		printf("Memory alloc faild!\n");
		OLED_ShowString(0, 5, "Memory alloc faild!");
	}
	else
	{
		controller -> Kp = setKp;
		controller -> Ki = setKi;
		controller -> Kd = setKd;
		for (i = 0; i < 3; ++i)
		{
			controller -> error[i] = 0;
			controller -> u[i] = PWM_To_Pulse(PWM_Expect);
		}
	}

	return controller;
}

void All_PID_Init(void)
{
	speedCtrler = PID_Init(3.2, 0.8, 0.5);
	steerCtrler = PID_Init(3.2, 0.8, 0.5);
	diffCtrler = PID_Init(3.2, 0.8, 0.5);
}