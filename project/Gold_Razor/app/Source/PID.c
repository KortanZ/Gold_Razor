#include "common.h"

PIDStruct *speedCtrler;

void Speed_Controller(PIDStruct *motorCtrler, float32 expect, float32 real)
{
	/* previous difference PID */

	float32 incrementU;

	motorCtrler -> error[0] = expect - real;
	incrementU = (motorCtrler -> Kp) * ((motorCtrler -> error[0]) - (motorCtrler -> error[1]))
						 + (motorCtrler -> Ki) * (motorCtrler -> error[0]) + (motorCtrler -> Kd) 
						 * ((motorCtrler -> u[0]) - 2 * (motorCtrler -> u[1]) + (motorCtrler -> u[2]))
						 - (motorCtrler -> Kd) * ((motorCtrler -> u[0]) - (motorCtrler -> u[1]));

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

	return;
}

PIDStruct *SpeedCtrler_Init(float32 setKp, float32 setKd, float32 setKi)
{
	/* Initial PID controller */
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
		controller -> Kd = setKd;
		controller -> Ki = setKi;
		for (i = 0; i < 3; ++i)
		{
			controller -> error[i] = 0;
			controller -> u[i] = PWM_To_Pulse(PWM_Expect);
		}		
	}

	return controller;
}