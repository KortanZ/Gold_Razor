/* 
*This file for motor driver
*include initial and control
*/

#include "common.h"

uint32 PWM_Expect = 3000;

void Motor_Init(void)
{
	/* Initial motor pwm */

	FTM_InitTypeDef motorInitStruct;

    motorInitStruct.FTM_Ftmx = FTM0;
    motorInitStruct.FTM_Mode = FTM_MODE_PWM;
    motorInitStruct.FTM_PwmFreq = MOTOR_FRE;

    LPLD_FTM_Init(motorInitStruct);
/*----------left motor backward initial--------*/
    LPLD_FTM_PWM_Enable(FTM0,
                        FTM_Ch0,
                        0,
                        MOTOR_LEFT_BACKWARD,  //PTA4
                        ALIGN_LEFT
                        );
/*----------left motor forward initial--------*/
    LPLD_FTM_PWM_Enable(FTM0,
                        FTM_Ch1,
                        PWM_Expect,
                        MOTOR_LEFT_FORWARD,  //PTA5
                        ALIGN_LEFT
                        );
/*----------right motor backward initial--------*/
    LPLD_FTM_PWM_Enable(FTM0,
                        FTM_Ch2,
                        0,
                        MOTOR_RIGHT_BACKWARD,  //PTA6
                        ALIGN_LEFT
                        );
/*----------righ motor forward initial--------*/
    LPLD_FTM_PWM_Enable(FTM0,
                        FTM_Ch3,
                        PWM_Expect,
                        MOTOR_RIGHT_FORWARD,  //PTA7
                        ALIGN_LEFT
                        );
}

void Motor_Duty_Change(MotorPosition motorPos, int32 tagetDuty)
{
	switch (motorPos)
	{
		case MOTOR_LEFT :
			LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch0, tagetDuty > 0 ? 0 : (uint32)fabs(tagetDuty));
			LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, tagetDuty > 0 ? (uint32)tagetDuty : 0);
			break;
		case MOTOR_RIGHT :
			LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch2, tagetDuty > 0 ? 0 : (uint32)fabs(tagetDuty));
			LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch3, tagetDuty > 0 ? (uint32)tagetDuty : 0);
	}
}