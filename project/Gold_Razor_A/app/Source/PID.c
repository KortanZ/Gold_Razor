//#include "common.h"
#include "PID.h"
#include "Oled.h"
#include "Menu.h"
#include "MotorDriver.h"
#include "ImgProcess.h"
#include "SteerDriver.h"

float32 Differ_Controller(PIDStruct *, float32 , float32 );

PIDStruct *speedCtrler;
PIDStruct *steerCtrler;
PIDStruct *differCtrler;
float32 enhance = 2.0;

void Speed_Controller(PIDStruct *motorCtrler, float32 expect, float32 real)
{
	float32 PWMoutput_1 , PWMoutput_2;
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

	/*          Differ PID Control  Block      */
	float32 Differ_Temp = 0;
	Differ_Temp = enhance * Differ_Controller(differCtrler , \
					 					steerMidValue , \
	 				 					MidAve);
	PWMoutput_1 = motorCtrler -> u[0] + Differ_Temp;
	PWMoutput_2 = motorCtrler -> u[0] - Differ_Temp;


	Motor_Duty_Change(MOTOR_LEFT, (int32)PulseNum_To_PWM(PWMoutput_1));
	Motor_Duty_Change(MOTOR_RIGHT, (int32)PulseNum_To_PWM(PWMoutput_2));
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

void Steer_Controller(PIDStruct *SteerCon_Data, float32 expect, float32 real)
{
	float32 incrementU;

	SteerCon_Data -> error[2] = SteerCon_Data -> error[1];
	SteerCon_Data -> error[1] = SteerCon_Data -> error[0];
	SteerCon_Data -> error[0] = real - expect;

	incrementU = (SteerCon_Data -> Kp) * ((SteerCon_Data -> error[0])           \
										   - (SteerCon_Data -> error[1]))  		\
			   + (SteerCon_Data -> Kd) * ((SteerCon_Data -> error[0])      		\
											- 2 * (SteerCon_Data -> error[1])   \
											+ (SteerCon_Data -> error[2]));

	SteerCon_Data -> u[2] = SteerCon_Data -> u[1];
	SteerCon_Data -> u[1] = SteerCon_Data -> u[0];
	SteerCon_Data -> u[0] = SteerCon_Data -> u[1] + incrementU;

	Steer_Duty_Change((uint32)SteerCon_Data -> u[0]);
}
void SteerCtrler_Init(void)
{
	int8 i;
	steerCtrler = (PIDStruct *)malloc(sizeof(PIDStruct));
	if (NULL == steerCtrler)
	{
		printf("Memory alloc faild!\n");
		OLED_ShowString(0, 5, "Memory alloc faild!");
	}
	else
	{
		steerCtrler -> Kp = 4.5;
		steerCtrler -> Kd = 1.5;
		steerCtrler -> Ki = 0;
		for(i = 0; i < 3; i++)
		{
			steerCtrler -> error[i] = 0;
			steerCtrler -> u[i] = STEER_MID_DUTY;
		}
	}
}

float32 Differ_Controller(PIDStruct *DifferCon_Data, float32 expect, float32 real)
{
	float32 incrementU;

	DifferCon_Data -> error[2] = DifferCon_Data -> error[1];
	DifferCon_Data -> error[1] = DifferCon_Data -> error[0];
	DifferCon_Data -> error[0] = real - expect;

	incrementU = (DifferCon_Data -> Kp) * ((DifferCon_Data -> error[0]) 		\
										 - (DifferCon_Data -> error[1]))		\
				+ (DifferCon_Data -> Kd) * ((DifferCon_Data -> error[0]) 		\
											- 2 * (DifferCon_Data -> error[1]) 	\
											+ (DifferCon_Data -> error[2]));

	DifferCon_Data -> u[2] = DifferCon_Data -> u[1];
	DifferCon_Data -> u[1] = DifferCon_Data -> u[0];
	DifferCon_Data -> u[0] = DifferCon_Data -> u[1] + incrementU;

	(DifferCon_Data -> u[0] > 3000) ? (DifferCon_Data -> u[0] = 3000) : (NULL);
	(DifferCon_Data -> u[0] < -3000) ? (DifferCon_Data -> u[0] = -3000) : (NULL);

	return (DifferCon_Data -> u[0]);
}
void DifferCtrler_Init(void)
{
	uint8 i;
	differCtrler = (PIDStruct *)malloc(sizeof(PIDStruct));
	if (NULL == differCtrler)
	{
		printf("Memory alloc faild!\n");
		OLED_ShowString(0, 5, "Memory alloc faild!");
	}
	else
	{
		differCtrler -> Kp = 29;
		differCtrler -> Kd = 6;
		differCtrler -> Ki = 0;
		for(i = 0;i < 3; i++)
		{
			differCtrler -> error[i] = 0;
			differCtrler -> u[i] = 0;
		}
	}
}