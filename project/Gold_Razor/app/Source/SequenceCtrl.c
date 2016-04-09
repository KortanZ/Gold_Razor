/*
*该代码提供时中断优先级初始化函数
*提供时序控制初始化和核心控制函数
*/

#include "common.h"


/*时序控制PIT初始化*/

void MainCtrl_Pit_Init(void)
{

	PIT_InitTypeDef pit3_init_struct;
	//配置PIT3参数
	pit3_init_struct.PIT_Pitx = PIT3;
	pit3_init_struct.PIT_PeriodMs = 1;//定时周期
	pit3_init_struct.PIT_PeriodUs = 0;
	pit3_init_struct.PIT_PeriodS = 0;
	pit3_init_struct.PIT_Isr = Main_Isr;  //设置中断函数
	//初始化PIT3
	LPLD_PIT_Init(pit3_init_struct);
	LPLD_PIT_EnableIrq(pit3_init_struct);
}


/*中断优先级初始化*/

void NVIC_Init(void)
{
	NVIC_InitTypeDef nvic_init_struct;
	
	//配置PIT3的NVIC分组
	nvic_init_struct.NVIC_IRQChannel = PIT3_IRQn;
	nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_2;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 2;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
	nvic_init_struct.NVIC_IRQChannelEnable = FALSE;
	LPLD_NVIC_Init(nvic_init_struct);
	//配置PORTA的NVIC分组
	nvic_init_struct.NVIC_IRQChannel = PORTA_IRQn;
	nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_2;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 1;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
	nvic_init_struct.NVIC_IRQChannelEnable = FALSE;
	LPLD_NVIC_Init(nvic_init_struct);
	//配置DMA0的NVIC分组
	nvic_init_struct.NVIC_IRQChannel = DMA0_IRQn;
	nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_2;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
	nvic_init_struct.NVIC_IRQChannelEnable = FALSE;
	LPLD_NVIC_Init(nvic_init_struct);

}

/*时序控制核心函数*/

void Main_Isr(void)
{
	
	static uint8 pitCounter = 0;
	pitCounter++;
	if ((pitCounter % 20) == 1)
	{
		Get_Img();
	}
	if ((pitCounter % 2) == 0)
	{
		//qd_result_ftm += LPLD_FTM_GetCounter(FTM1);
		//qd_result_lptmr += LPLD_LPTMR_GetPulseAcc();
	  	
	}
	if ((pitCounter % 20) == 0)
	{

		//Left_Pulse = (float32)qd_result_ftm/(10.0*256.0);
		//Right_Pulse = (float32)qd_result_lptmr/(10.0*256.0);

		//Motor_Speed = ((Left_Pulse + Right_Pulse)/2.0)*1000.0;	//此处PID函数有错误


	  	
		
		OLED_ShowNum(0, 3, PulseNum_To_Speed(Encoder_GetPulseNum(ENCODER_RIGHT)), Num_Len);
		//Encoder_GetPulseNum(ENCODER_LEFT);
		//OLED_ShowNum(0, 3, Encoder_GetPulseNum(ENCODER_RIGHT), Num_Len);
	  	
	  	Steer_Duty_Change(steerDebugDuty);

		Motor_Duty_Change(MOTOR_LEFT, PWM_Expect);
		Motor_Duty_Change(MOTOR_RIGHT, PWM_Expect);

		pitCounter = 0;
	}

}