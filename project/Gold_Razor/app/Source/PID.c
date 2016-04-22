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

void SpeedCtrler_Init(void)
{
	/* Initial PID speedCtrler */
	int8 i;

	speedCtrler = (PIDStruct *)malloc(sizeof(PIDStruct));

	if (NULL == speedCtrler)
	{
		printf("Memory alloc faild!\n");
		OLED_ShowString(0, 5, "Memory alloc faild!");
	}
	else
	{
		speedCtrler -> Kp = 3.2;
		speedCtrler -> Kd = 0.5;
		speedCtrler -> Ki = 0.8;
		for (i = 0; i < 3; ++i)
		{
			speedCtrler -> error[i] = 0;
			speedCtrler -> u[i] = PWM_To_Pulse(PWM_Expect);
		}		
	}

}