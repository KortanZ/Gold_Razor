#include "Encoder_init.h"
#include "Eagle_ov7725.h"
#include "ImgDispose.h"
#include "oled.h"
#include "PWM_init.h"

FTM_InitTypeDef Left_Encoder_init_struct;
LPTMR_InitTypeDef Right_Encoder_init_param;
UART_InitTypeDef uartRazor_init_struct;
PIT_InitTypeDef pit3_init_struct;
NVIC_InitTypeDef nvickeyisrC_init_struct;
NVIC_InitTypeDef nvickeyisrD_init_struct;
NVIC_InitTypeDef nvicpit3_init_struct;
NVIC_InitTypeDef nvicporta_init_struct;
NVIC_InitTypeDef nvicdma0_init_struct;

GPIO_InitTypeDef gpioa_init_struct;
GPIO_InitTypeDef gpioe_init_struct;
GPIO_InitTypeDef keyC_init_struct;
GPIO_InitTypeDef keyD_init_struct;

void main_isr(void);
void Key_Isr(void);
uint16 qd_result_ftm, qd_result_lptmr;
float32 Left_Pulse, Right_Pulse, Motor_Speed;
uint8 TenMs_Flag = 0, pit_counter = 0;




void Button_Delay(uint16 n)
{
	uint16 i, j;
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<200; j++)
		{
			asm("nop");
		}
	}
}


void Encoder_init(void)
{
	//配置正交解码功能参数
	Left_Encoder_init_struct.FTM_Ftmx = FTM1;              //只有FTM1和FTM2有正交解码功能
	Left_Encoder_init_struct.FTM_Mode = FTM_MODE_QD;       //正交解码功能
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
	Right_Encoder_init_param.LPTMR_Isr = NULL;

	LPLD_LPTMR_Init(Right_Encoder_init_param);

}


/*------------------UART-------------------*/
void UART_init(void)
{
	uartRazor_init_struct.UART_Uartx = UART2; //使用UART5
	uartRazor_init_struct.UART_BaudRate = 115200; //设置波特率9600
	uartRazor_init_struct.UART_RxPin = PTD2;  //接收引脚为PTD2
	uartRazor_init_struct.UART_TxPin = PTD3;  //发送引脚为PTD3
	//初始化UART
	LPLD_UART_Init(uartRazor_init_struct);

	//--------------------K60_LED-------------------
	gpioa_init_struct.GPIO_PTx = PTA;
	gpioa_init_struct.GPIO_Pins = GPIO_Pin17;
	gpioa_init_struct.GPIO_Dir = DIR_OUTPUT;
	gpioa_init_struct.GPIO_Output = OUTPUT_H;
	gpioa_init_struct.GPIO_PinControl = IRQC_DIS;
	LPLD_GPIO_Init(gpioa_init_struct);   /* */
	//---------------------Razor_LED----------------
	gpioe_init_struct.GPIO_PTx = PTE;
	gpioe_init_struct.GPIO_Pins = GPIO_Pin10;
	gpioe_init_struct.GPIO_Dir = DIR_OUTPUT;
	gpioe_init_struct.GPIO_Output = OUTPUT_L;
	gpioe_init_struct.GPIO_PinControl = IRQC_DIS;
	LPLD_GPIO_Init(gpioe_init_struct);
	//---------------------Razor_Key-------------------
	/*keyC_init_struct.GPIO_PTx = PTC;
	keyC_init_struct.GPIO_Pins = GPIO_Pin14 | GPIO_Pin15;
	keyC_init_struct.GPIO_Dir = DIR_INPUT;
	//keyC_init_struct.GPIO_Output = INPUT_PULL_UP;
	keyC_init_struct.GPIO_PinControl = INPUT_PULL_UP|IRQC_FA;
	keyC_init_struct.GPIO_Isr = Key_Isr;
	LPLD_GPIO_Init(keyC_init_struct);

	keyD_init_struct.GPIO_PTx = PTD;
	keyD_init_struct.GPIO_Pins = GPIO_Pin10 | GPIO_Pin11 | GPIO_Pin12 | GPIO_Pin13;
	keyD_init_struct.GPIO_Dir = DIR_INPUT;
	//keyD_init_struct.GPIO_Output = INPUT_PULL_UP;
	keyD_init_struct.GPIO_PinControl = INPUT_PULL_UP|IRQC_FA;
	keyD_init_struct.GPIO_Isr = Key_Isr;
	LPLD_GPIO_Init(keyD_init_struct);*/
}
/*void Key_Isr(void)
{
if(LPLD_GPIO_IsPinxExt(PORTC, GPIO_Pin14) ||
LPLD_GPIO_IsPinxExt(PORTC, GPIO_Pin15) ||
LPLD_GPIO_IsPinxExt(PORTD, GPIO_Pin10) ||
LPLD_GPIO_IsPinxExt(PORTD, GPIO_Pin11) ||
LPLD_GPIO_IsPinxExt(PORTD, GPIO_Pin12) ||
LPLD_GPIO_IsPinxExt(PORTD, GPIO_Pin13)  )
{
Button_Delay(10000);
if(PTD12_I == 0)
{
OLED_NumClear(70,3,Num_Len);		//Steer_Kp++
Steer_Kp++;
OLED_ShowNum(70,3,Steer_Kp,Num_Len);
}
if(PTD13_I == 0)
{
OLED_NumClear(70,3,Num_Len);		//Steer_Kp--
Steer_Kp--;
OLED_ShowNum(70,3,Steer_Kp,Num_Len);
}
if(PTD10_I == 0)
{
OLED_NumClear(70,4,Num_Len);		//Steer_Kd++
Steer_Kd++;
OLED_ShowNum(70,4,Steer_Kd,Num_Len);
}
if(PTD11_I == 0)
{
OLED_NumClear(70,4,Num_Len);		//Steer_Kd--
Steer_Kd--;
OLED_ShowNum(70,4,Steer_Kd,Num_Len);
}
if(PTC14_I == 0)
{
}
if(PTC15_I == 0)
{
}
}
}*/

/*--------------------PIT--------------------*/
void pit_init(void)
{


	//配置PIT1参数
	pit3_init_struct.PIT_Pitx = PIT3;
	pit3_init_struct.PIT_PeriodMs = 1;//定时周期
	pit3_init_struct.PIT_Isr = main_isr;  //设置中断函数
	//初始化PIT1
	LPLD_PIT_Init(pit3_init_struct);
	LPLD_PIT_EnableIrq(pit3_init_struct);
}

void pit0_time_start(void)
{
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;         //使能PIT时钟
	PIT->MCR &= ~(PIT_MCR_MDIS_MASK | PIT_MCR_FRZ_MASK);    //使能PIT定时器时钟 ，调试模式下继续运行
	PIT->CHANNEL[0].TCTRL &= ~(PIT_TCTRL_TEN_MASK);
	PIT->CHANNEL[0].LDVAL = ~0;							 //设置溢出中断时间
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
	PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;
	PIT->CHANNEL[0].TCTRL |= (0 | PIT_TCTRL_TEN_MASK);
}

uint32 pit0_time_get(void)
{
	uint32 val;
	val = (~0) - PIT->CHANNEL[0].CVAL;
	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK)
	{
		PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
		PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;
		return ~0;
	}
	if (val == (~0))
	{
		val--;              //确保 不等于 ~0
	}
	return val;
}

void NVIC_init(void)
{
	//配置PIT3的NVIC分组
	nvicpit3_init_struct.NVIC_IRQChannel = PIT3_IRQn;
	nvicpit3_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_2;
	nvicpit3_init_struct.NVIC_IRQChannelPreemptionPriority = 2;
	LPLD_NVIC_Init(nvicpit3_init_struct);
	//配置PORTA的NVIC分组
	nvicporta_init_struct.NVIC_IRQChannel = PORTA_IRQn;
	nvicporta_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_2;
	nvicporta_init_struct.NVIC_IRQChannelPreemptionPriority = 1;
	LPLD_NVIC_Init(nvicporta_init_struct);
	//配置DMA0的NVIC分组
	nvicdma0_init_struct.NVIC_IRQChannel = DMA0_IRQn;
	nvicdma0_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_2;
	nvicdma0_init_struct.NVIC_IRQChannelPreemptionPriority = 0;
	LPLD_NVIC_Init(nvicdma0_init_struct);

}



void main_isr(void)
{
	pit_counter++;
	//pit_counter = 1;
	if ((pit_counter % 20) == 1)              //&& (IMG_Ready==1)
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
		//IMG_Ready = 0;
	}
	if ((pit_counter % 2) == 0)
	{
		//qd_result_ftm += LPLD_FTM_GetCounter(FTM1);
		//qd_result_lptmr += LPLD_LPTMR_GetPulseAcc();
	  	
	}
	if ((pit_counter % 20) == 0)
	{
		//if(qd_result_ftm < 0)  qd_result_ftm = -qd_result_ftm;
		//if(qd_result_lptmr < 0) qd_result_lptmr = -qd_result_lptmr;

		//Left_Pulse = (float32)qd_result_ftm/(10.0*256.0);
		//Right_Pulse = (float32)qd_result_lptmr/(10.0*256.0);

		//Motor_Speed = ((Left_Pulse + Right_Pulse)/2.0)*1000.0;	//此处PID函数有错误
	  
		
		//OLED_ShowNum(70, 5, PWM_Expect, Num_Len);
	  	


		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch2, PWM_Expect);
		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch4, PWM_Expect);
		
		pit_counter = 0;
	}

}
