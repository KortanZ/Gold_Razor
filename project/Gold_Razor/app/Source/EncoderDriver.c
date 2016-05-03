#include "common.h"

LPTMR_InitTypeDef Right_Encoder_init_param;
/*编码器初始化*/
void Encoder_Init(void)
{
	
	FTM_InitTypeDef Left_Encoder_init_struct;

	//配置正交解码功能参数
	Left_Encoder_init_struct.FTM_Ftmx = FTM1;              //只有FTM1和FTM2有正交解码功能
	Left_Encoder_init_struct.FTM_Mode = FTM_MODE_QD;       //正交解码功能
	Left_Encoder_init_struct.FTM_PwmFreq = 0;

	Left_Encoder_init_struct.FTM_QdMode = QD_MODE_PHAB;    //AB相输入模式
	//初始化FTM
	LPLD_FTM_Init(Left_Encoder_init_struct);
	//使能AB相输入通道
	//PTB0引脚接A相输入、PTB1引脚接B相输入
	LPLD_FTM_QD_Enable(FTM1, PTA12, PTA13);

	//LPTMR_MODE_PLACC脉冲累加模式
	//LPTMR_ALT2的输入口为PTC5
	//禁用中断
	//无中断函数
	Right_Encoder_init_param.LPTMR_Mode = LPTMR_MODE_PLACC;
	Right_Encoder_init_param.LPTMR_PluseAccInput = LPTMR_ALT2;
	Right_Encoder_init_param.LPTMR_IntEnable = FALSE;
	Right_Encoder_init_param.LPTMR_Isr = NULL;

	LPLD_LPTMR_Init(Right_Encoder_init_param);

}

/*获取编码器值*/

//参数position：Left左编码器；Right右编码器

int16 Encoder_GetPulseNum(EncoderPosition position)
{
	int16 result;
	
	switch (position)
	{
		case ENCODER_LEFT: 
			result = -LPLD_FTM_GetCounter(FTM1); 
			LPLD_FTM_ClearCounter(FTM1);
			break;	//左编码器反转
		case ENCODER_RIGHT: 
			result = 4 * LPLD_LPTMR_GetPulseAcc();
			LPLD_LPTMR_ResetCounter();       //复位LPTMR0 counter 
    		LPLD_LPTMR_Init(Right_Encoder_init_param);
    		break;
	}

	return result;
}

float32 PulseNum_To_PWM(float32 pulseNum)
{
	/* This function convert pulse number to pwm */

	float32 pwm;
	pwm = (pulseNum + B_CONST) / B_COF;
	return pwm;
}

float32 PWM_To_Pulse(uint32 pwm)
{
	/* This function convert pwm to pulse number */

	float32 pulse;
	pulse = B_COF * pwm - B_CONST;

	if (pulse < 0)
	{
		pulse = 0;
	}

	return pulse;
}