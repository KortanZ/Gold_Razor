//#include "common.h"
#include "PID.h"
#include "Oled.h"
#include "Menu.h"
#include "MotorDriver.h"
#include "ImgProcess.h"
#include "SteerDriver.h"

float32 Differ_Controller(PIDStruct *, float32, float32);

PIDStruct *speedCtrler;
PIDParaStruct *speedCtrlerPara;

PIDStruct *steerCtrler;
PIDParaStruct *steerCtrlerStPara;
PIDParaStruct *steerCtrlerCurvPara;
PIDParaStruct *steerCtrlerPseStPara;

PIDStruct *differCtrler;
PIDParaStruct *differCtrlerStPara;
PIDParaStruct *differCtrlerCurvPara;
PIDParaStruct *differCtrlerPseStPara;

float32 enhance = 0;

int16 motorThersh = 250;
int16 steerThersh = 28;

void Speed_Controller(PIDStruct *motorCtrler, float32 expect, float32 real)
{
	float32 PWMoutput_1 , PWMoutput_2;
	/* previous difference PID */

	float32 incrementU;

	motorCtrler -> error[0] = expect - real;

	incrementU = (motorCtrler -> para -> Kp) * ((motorCtrler -> error[0]) - (motorCtrler -> error[1]))
					 + (motorCtrler -> para-> Ki) * (motorCtrler -> error[0]) + (motorCtrler -> para -> Kd)
					 * ((motorCtrler -> u[0]) - 2 * (motorCtrler -> u[1]) + (motorCtrler -> u[2]))
					 - (motorCtrler -> para -> Kd) * ((motorCtrler -> u[0]) - (motorCtrler -> u[1]));

	/* anti-windup */

	if ((motorCtrler -> u[1]) > U_MAX || (motorCtrler -> u[1]) < -U_MAX)
	{
		incrementU -= (motorCtrler -> para -> Ki) * (motorCtrler -> error[0]);
	}

	motorCtrler -> u[0] = (motorCtrler -> u[1]) + incrementU;

	motorCtrler -> u[2] = motorCtrler -> u[1];
	motorCtrler -> u[1] = motorCtrler -> u[0];
	motorCtrler -> error[1] = motorCtrler -> error[0];

	if(motorCtrler -> error[0] > motorThersh)
	{
		Motor_Duty_Change(MOTOR_LEFT, 6500);
		Motor_Duty_Change(MOTOR_RIGHT, 6500);
	}
	else if(motorCtrler -> error[0] < -motorThersh)
	{
		Motor_Duty_Change(MOTOR_LEFT, -6500);
		Motor_Duty_Change(MOTOR_RIGHT, -6500);
	}
	else
	{
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
}

void SpeedCtrler_Init(void)
{
	/* Initial PID speedCtrler */
	int8 i;

	speedCtrler = (PIDStruct *)malloc(sizeof(PIDStruct));
	speedCtrlerPara = (PIDParaStruct *)malloc(sizeof(PIDParaStruct));

	if (!speedCtrler || !speedCtrlerPara)
	{
		printf("Memory alloc faild!\n");
		OLED_ShowString(0, 5, "Memory alloc faild!");
	}
	else
	{
		speedCtrlerPara -> Kp = 4.8;
		speedCtrlerPara -> Kd = 0.2;
		speedCtrlerPara -> Ki = 0.8;
		speedCtrler -> para = speedCtrlerPara;
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

	incrementU = (SteerCon_Data -> para -> Kp) * ((SteerCon_Data -> error[0]))           
			   + (SteerCon_Data -> para -> Kd) * ((SteerCon_Data -> error[0]) - (SteerCon_Data -> error[1]));

	SteerCon_Data -> u[0] = STEER_MID_DUTY + incrementU;

	if (SteerCon_Data -> error[0] > steerThersh && SteerCon_Data -> useBang)
	{
		Steer_Duty_Change(STEER_RIGHT_DUTY);
	}
	else if(SteerCon_Data -> error[0] < -steerThersh && SteerCon_Data -> useBang)
	{
		Steer_Duty_Change(STEER_LEFT_DUTY);
	}
	else
	{
		Steer_Duty_Change((uint32)SteerCon_Data -> u[0]);
	}

	//Steer_Duty_Change(STEER_MID_DUTY);
}
void SteerCtrler_Init(void)
{
	int8 i;
	steerCtrler = (PIDStruct *)malloc(sizeof(PIDStruct));
	steerCtrlerStPara = (PIDParaStruct *)malloc(sizeof(PIDParaStruct));
	steerCtrlerPseStPara = (PIDParaStruct *)malloc(sizeof(PIDParaStruct));
	steerCtrlerCurvPara = (PIDParaStruct *)malloc(sizeof(PIDParaStruct));
	if (!steerCtrlerStPara || !steerCtrlerCurvPara || !steerCtrler || !steerCtrlerPseStPara)
	{
		printf("Memory alloc faild!\n");
		OLED_ShowString(0, 5, "Memory alloc faild!");
	}
	else
	{
		steerCtrlerStPara -> Kp = 1.3;
		steerCtrlerStPara -> Kd = 0.44;
		steerCtrlerStPara -> Ki = 0;

		steerCtrlerPseStPara -> Kp = 4.3;
		steerCtrlerPseStPara -> Kd = 0.48;
		steerCtrlerPseStPara -> Ki = 0;

		steerCtrlerCurvPara -> Kp = 5.716;
		steerCtrlerCurvPara -> Kd = 0.704;
		steerCtrlerCurvPara -> Ki = 0;

		steerCtrler -> para = steerCtrlerStPara;
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

	incrementU = (DifferCon_Data -> para -> Kp) * ((DifferCon_Data -> error[0]) 		
										 - (DifferCon_Data -> error[1]))		
				+ (DifferCon_Data -> para -> Kd) * ((DifferCon_Data -> error[0])
											- 2 * (DifferCon_Data -> error[1]) 	
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
	differCtrlerStPara = (PIDParaStruct *)malloc(sizeof(PIDParaStruct));
	differCtrlerCurvPara = (PIDParaStruct *)malloc(sizeof(PIDParaStruct));
	differCtrlerPseStPara = (PIDParaStruct *)malloc(sizeof(PIDParaStruct));
	if (!differCtrler || !differCtrlerStPara || !differCtrlerCurvPara)
	{
		printf("Memory alloc faild!\n");
		OLED_ShowString(0, 5, "Memory alloc faild!");
	}
	else
	{
		differCtrlerStPara -> Kp = 0;
		differCtrlerStPara -> Kd = 0;
		differCtrlerStPara -> Ki = 0;

		differCtrlerPseStPara -> Kp = 0;
		differCtrlerPseStPara -> Kd	= 0;
		differCtrlerPseStPara -> Ki = 0;

		differCtrlerCurvPara -> Kp = 0;
		differCtrlerCurvPara -> Kd = 0;
		differCtrlerCurvPara -> Ki = 0;

		differCtrler -> para = differCtrlerStPara;
		for(i = 0;i < 3; i++)
		{
			differCtrler -> error[i] = 0;
			differCtrler -> u[i] = 0;
		}
	}
}