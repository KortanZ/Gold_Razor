/* 
*This file for steer driver
*include initial and control
*/
#include "SteerDriver.h"

uint8 steerMidValue = 85;
void Steer_Init(void)
{

	FTM_InitTypeDef steerInitStruct;

    steerInitStruct.FTM_Ftmx = FTM2;
    steerInitStruct.FTM_Mode = FTM_MODE_PWM;
    steerInitStruct.FTM_PwmFreq = 100;
    steerInitStruct.FTM_PwmDeadtimeCfg = DEADTIME_CH01;
    steerInitStruct.FTM_PwmDeadtimeDiv = DEADTIME_DIV1;
    steerInitStruct.FTM_PwmDeadtimeVal = 0;

    LPLD_FTM_Init(steerInitStruct);

    LPLD_FTM_PWM_Enable(FTM2, //使用FTM2
                        FTM_Ch0, //使能Ch0通道
                        STEER_MID_DUTY, //初始化角度0度  100HZ为1432  MAX=1570,Min=1250
                        PTA10, //使用Ch0通道的PTD0引脚
                        ALIGN_LEFT        //脉宽左对齐
                        );
}

void Steer_Duty_Change(uint32 tagetDuty)
{
	if(tagetDuty < STEER_LEFT_DUTY)
    {
        tagetDuty = STEER_LEFT_DUTY;
    }
    else if(tagetDuty > STEER_RIGHT_DUTY)
    {
        tagetDuty = STEER_RIGHT_DUTY;
    }
    
    LPLD_FTM_PWM_ChangeDuty(FTM2, FTM_Ch0, tagetDuty);
}
