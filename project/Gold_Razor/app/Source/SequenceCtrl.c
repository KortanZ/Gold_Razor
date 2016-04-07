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
	LPLD_NVIC_Init(nvic_init_struct);
	//配置PORTA的NVIC分组
	nvic_init_struct.NVIC_IRQChannel = PORTA_IRQn;
	nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_2;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 1;
	LPLD_NVIC_Init(nvic_init_struct);
	//配置DMA0的NVIC分组
	nvic_init_struct.NVIC_IRQChannel = DMA0_IRQn;
	nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_2;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0;
	LPLD_NVIC_Init(nvic_init_struct);

}

/*时序控制核心函数*/

void Main_Isr(void)
{
	
	static uint8 pitCounter = 0;
	pitCounter++;
	if ((pitCounter % 20) == 1)
	{
		ov7725_eagle_img_flag = IMG_START;                   //开始采集图像
		PORTA->ISFR = ~0;
		enable_irq((IRQn_Type)(PORTA_IRQn));
		while (ov7725_eagle_img_flag != IMG_FINISH)
		{
			if (ov7725_eagle_img_flag == IMG_FAIL)            //假如图像采集错误，则重新开始采集
			{
				ov7725_eagle_img_flag = IMG_START;           //开始采集图像
				PORTA->ISFR = 0xFFFFFFFFu;                //写1清中断标志位(必须的，不然回导致一开中断就马上触发中断)
				enable_irq(PORTA_IRQn);                 //允许PTA的中断
			}
		}
	}
	if ((pitCounter % 2) == 0)
	{
		//qd_result_ftm += LPLD_FTM_GetCounter(FTM1);
		//qd_result_lptmr += LPLD_LPTMR_GetPulseAcc();
	  	
	}
	if ((pitCounter % 20) == 0)
	{
		//if(qd_result_ftm < 0)  qd_result_ftm = -qd_result_ftm;
		//if(qd_result_lptmr < 0) qd_result_lptmr = -qd_result_lptmr;

		//Left_Pulse = (float32)qd_result_ftm/(10.0*256.0);
		//Right_Pulse = (float32)qd_result_lptmr/(10.0*256.0);

		//Motor_Speed = ((Left_Pulse + Right_Pulse)/2.0)*1000.0;	//此处PID函数有错误
	  
		
		//OLED_ShowNum(70, 5, PWM_Expect, Num_Len);
	  	


		//LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch2, PWM_Expect);
		//LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch4, PWM_Expect);
		
		pitCounter = 0;
	}

}