#include "common.h"

PIDStruct *leftMotorCtrl;
PIDStruct *rightMororCtrl;


void Motor_Controller(PIDStruct *motorCtrler, float32 expect, float32 real)
{
	motorCtrler -> error[0] = real - expect;
	motorCtrler -> u[0] = (motorCtrler -> Kp) * ((motorCtrler -> error[0]) - (motorCtrler -> error[1]))
						 + (motorCtrler -> Ki) * (motorCtrler -> error[0]) + (motorCtrler -> Kd) 
						 * ((motorCtrler -> u[0]) - 2 * (motorCtrler -> u[1]) + (motorCtrler -> u[2]))
						 - (motorCtrler -> Kd) * ((motorCtrler -> u[0]) - (motorCtrler -> u[1])) + (motorCtrler -> u[1]);
	motorCtrler -> u[2] = motorCtrler -> u[1];
	motorCtrler -> u[1] = motorCtrler -> u[0];
	motorCtrler -> error[1] = motorCtrler -> error[0]; 
}

PIDStruct *MotorCtrler_Init(void)
{
	int8 i;

	PIDStruct *controller = (PIDStruct *)malloc(sizeof(PIDStruct));

	if (NULL == controller)
	{
		printf("Memory alloc faild!\n");
		OLED_ShowString(0, 5, "Memory alloc faild!");
	}
	else
	{
		controller -> Kp = 1;
		controller -> Kd = 0;
		controller -> Ki = 0;
		for (i = 0; i < 3; ++i)
		{
			controller -> error[i] = 0;
			controller -> u[i] = 0;
		}
		controller -> u[0] = PWM_Expect;
	}

	return controller;
}