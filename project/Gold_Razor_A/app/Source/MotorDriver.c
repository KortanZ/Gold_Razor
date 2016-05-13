/*
*This file for motor driver
*include initial and control
*/

//#include "common.h"
#include "MotorDriver.h"
int32 PWM_Expect = 1800;

void Motor_Init(void)
{
	/* Initial motor pwm */

	FTM_InitTypeDef motorInitStruct;

    motorInitStruct.FTM_Ftmx = FTM0;
    motorInitStruct.FTM_Mode = FTM_MODE_PWM;
    motorInitStruct.FTM_PwmFreq = MOTOR_FRE;
    motorInitStruct.FTM_PwmDeadtimeCfg = DEADTIME_CH01;
    motorInitStruct.FTM_PwmDeadtimeDiv = DEADTIME_DIV1;
    motorInitStruct.FTM_PwmDeadtimeVal = 0;


    LPLD_FTM_Init(motorInitStruct);
/*----------left motor backward initial--------*/
    LPLD_FTM_PWM_Enable(FTM0,
                        FTM_Ch1,
                        0,
                        MOTOR_LEFT_BACKWARD,  //PTA4
                        ALIGN_LEFT
                        );
/*----------left motor forward initial--------*/
    LPLD_FTM_PWM_Enable(FTM0,
                        FTM_Ch2,
                        0,
                        MOTOR_LEFT_FORWARD,  //PTA5
                        ALIGN_LEFT
                        );
/*----------right motor backward initial--------*/
    LPLD_FTM_PWM_Enable(FTM0,
                        FTM_Ch3,
                        0,
                        MOTOR_RIGHT_BACKWARD,  //PTA6
                        ALIGN_LEFT
                        );
/*----------righ motor forward initial--------*/
    LPLD_FTM_PWM_Enable(FTM0,
                        FTM_Ch4,
                        0,
                        MOTOR_RIGHT_FORWARD,  //PTA7
                        ALIGN_LEFT
                        );
}

void Motor_Duty_Change(MotorPosition motorPos, int32 tagetDuty)
{

    /* Set motor threshold */
    if (tagetDuty > 9000)
    {
        tagetDuty = 9000;
    }
    else if (tagetDuty < -9000)
    {
        tagetDuty = -9000;
    }

	switch (motorPos)
	{
		case MOTOR_LEFT :
			LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, tagetDuty > 0 ? 0 : (uint32)(-tagetDuty));
			LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch2, tagetDuty > 0 ? (uint32)tagetDuty : 0);
			break;
		case MOTOR_RIGHT :
			LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch3, tagetDuty > 0 ? 0 : (uint32)(-tagetDuty));
			LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch4, tagetDuty > 0 ? (uint32)tagetDuty : 0);
            break;
	}
}
float32 PulseNum_To_PWM(float32 pulseNum)
{
	/* This function convert pulse number to rotational speed */

	float32 pwm;
	pwm = (pulseNum + 319.8) / 0.5724;
	return pwm;
}

float32 PWM_To_Pulse(uint32 pwm)
{
	float32 pulse;
	pulse = 0.5724 * pwm - 319.8;

	if (pulse < 0)
	{
		pulse = 0;
	}

	return pulse;
}