/*
*该代码提供时中断优先级初始化函数
*提供时序控制初始化和核心控制函数
*/

#include "SequenceCtrl.h"
#include "ImgProcess.h"
#include "EncoderDriver.h"
#include "MotorDriver.h"
#include "SteerDriver.h"
#include "DebugerDriver.h"
#include "Oled.h"
#include "PID.h"
#include "VirtualOsc.h"
#include "math.h"

uint8 pitCounter = 0; //时序控制变量
uint8 imgSendFlag = 0;

/*     process functiong declare   */
void First_Process(void);
void Second_Process(void);
void Thrid_Process(void);

/*时序控制PIT初始化*/

void MainCtrl_Pit_Init(void)
{

	PIT_InitTypeDef pit3_init_struct;
	//配置PIT3参数
	pit3_init_struct.PIT_Pitx = PIT3;
	pit3_init_struct.PIT_PeriodMs = 20;//定时周期
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
	nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_3;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 3;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
	nvic_init_struct.NVIC_IRQChannelEnable = FALSE;
	LPLD_NVIC_Init(nvic_init_struct);
	//配置Key_Isr的NVIC分组
	nvic_init_struct.NVIC_IRQChannel = PORTC_IRQn;
	nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_3;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 2;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
	nvic_init_struct.NVIC_IRQChannelEnable = FALSE;
	LPLD_NVIC_Init(nvic_init_struct);

	nvic_init_struct.NVIC_IRQChannel = PORTD_IRQn;
	nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_3;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 2;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 0;
	nvic_init_struct.NVIC_IRQChannelEnable = FALSE;
	LPLD_NVIC_Init(nvic_init_struct);
	//配置PORTA的NVIC分组
	nvic_init_struct.NVIC_IRQChannel = PORTA_IRQn;
	nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_3;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 1;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
	nvic_init_struct.NVIC_IRQChannelEnable = FALSE;
	LPLD_NVIC_Init(nvic_init_struct);
	//配置DMA0的NVIC分组
	nvic_init_struct.NVIC_IRQChannel = DMA0_IRQn;
	nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_3;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
	nvic_init_struct.NVIC_IRQChannelEnable = FALSE;
	LPLD_NVIC_Init(nvic_init_struct);

}

/*时序控制核心函数*/

void Main_Isr(void)
{
	First_Process();

	Second_Process();
	
}

/*    process function prototype     */
void First_Process(void)
{
	
}

void Second_Process(void)
{
	int16 leftPulse, rightPulse;

	pitCounter = 0;

	leftPulse = Encoder_GetPulseNum(ENCODER_LEFT);
	rightPulse = Encoder_GetPulseNum(ENCODER_RIGHT);

	if(leftPulse < 0)
	{
		rightPulse = -rightPulse;
	}

	if (leftPulse + rightPulse)
	{
		Keyboard_Locker();
	}
	else
	{
		Keyboard_Unlocker();
	}

	if(!brokeDownFlag)
	{
		Speed_Controller(speedCtrler, PWM_To_Pulse(PWM_Expect), (leftPulse + rightPulse) / 2.0);
		Steer_Controller(steerCtrler, steerMidValue, MidAve);
	}
	else
	{
		Speed_Controller(speedCtrler, 0, (leftPulse + rightPulse) / 2.0);
		Steer_Controller(steerCtrler, steerMidValue, steerMidValue);
	}


	// VirtualSignal[0] = PWM_To_Pulse(PWM_Expect);
	// VirtualSignal[1] = (leftPulse + rightPulse) / 2.0;
 //    // VirtualSignal[2] = rightPulse;
 //    // VirtualSignal[3] = PWM_Expect;
 //    OutPut_Data();
}

void Third_Process(void)
{

}