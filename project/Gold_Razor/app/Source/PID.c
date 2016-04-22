#include "common.h"

PIDStruct *motorCtrler = NULL;
PIDStruct *steerCtrler = NULL;
PIDStruct *diffCtrler = NULL;

void PID_Calc(PIDStruct *controller, float32 expect, float32 real)
{
	/* previous difference PID */

	float32 incrementU;

	controller -> error[0] = expect - real;

	incrementU = (controller -> Kp) * ((controller -> error[0]) - (controller -> error[1]))
					 + (controller -> Ki) * (controller -> error[0]) + (controller -> Kd) 
					 * ((controller -> u[0]) - 2 * (controller -> u[1]) + (controller -> u[2]))
					 - (controller -> Kd) * ((controller -> u[0]) - (controller -> u[1]));

	/* anti-windup */
					 
	if ((controller -> u[1]) > (controller -> uMax) || (controller -> u[1]) < -(controller -> uMax))
	{
		incrementU -= (controller -> Ki) * (controller -> error[0]);
	}

	controller -> u[0] = (controller -> u[1]) + incrementU; 

	controller -> u[2] = controller -> u[1];
	controller -> u[1] = controller -> u[0];
	controller -> error[1] = controller -> error[0]; 

	/* standard PID */

	// controller -> error[0] = expect - real;
	// incrementU = (controller -> Kp) * ((controller -> error[0]) - (controller -> error[1]))
	// 					+ (controller -> Ki) * (controller -> error[0]) + (controller -> Kd)
	// 					* ((controller -> error[0]) - 2 * (controller -> error[1]) + (controller -> error[2]));

	// controller -> u[0] = (controller -> u[1]) + incrementU; 
	
	// controller -> u[2] = controller -> u[1];
	// controller -> u[1] = controller -> u[0];
	// controller -> error[2] = controller -> error[1];
	// controller -> error[1] = controller -> error[0];
}

PIDStruct *PID_Init(float32 setKp, float32 setKi, float32 setKd, uint16 threshold)
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
		controller -> uMax = threshold;
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
	motorCtrler = PID_Init(3.2, 0.8, 0.5, 4800);
	steerCtrler = PID_Init(3.2, 0.8, 0.5, 4800);
	diffCtrler = PID_Init(3.2, 0.8, 0.5, 4800);
}