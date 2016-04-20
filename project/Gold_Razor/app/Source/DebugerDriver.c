/* 
*This file for debuger driver
*include UART and GPIO initial
*include timer initial
*/
#include "common.h"

uint32 steerDebugDuty = 1431;

void UART_Debuger_Init(void)
{
	UART_InitTypeDef uartInitStruct;
	uartInitStruct.UART_Uartx = UART2; //使用UART2
	uartInitStruct.UART_BaudRate = 115200; //设置波特率115200
	uartInitStruct.UART_RxPin = PTD2;  //接收引脚为PTD2
	uartInitStruct.UART_TxPin = PTD3;  //发送引脚为PTD3
	//初始化UART
	LPLD_UART_Init(uartInitStruct);
}

void LED_Debuger_Init(void)
{
	GPIO_InitTypeDef gpioInitStruct;

	//--------------------K60_LED-------------------
	gpioInitStruct.GPIO_PTx = PTA;
	gpioInitStruct.GPIO_Pins = GPIO_Pin17;
	gpioInitStruct.GPIO_Dir = DIR_OUTPUT;
	gpioInitStruct.GPIO_Output = OUTPUT_H;
	gpioInitStruct.GPIO_PinControl = IRQC_DIS;
	LPLD_GPIO_Init(gpioInitStruct);   /* */
	//---------------------Razor_LED----------------
	gpioInitStruct.GPIO_PTx = PTE;
	gpioInitStruct.GPIO_Pins = GPIO_Pin10;
	gpioInitStruct.GPIO_Dir = DIR_OUTPUT;
	gpioInitStruct.GPIO_Output = OUTPUT_L;
	gpioInitStruct.GPIO_PinControl = IRQC_DIS;
	LPLD_GPIO_Init(gpioInitStruct);
}

void Keyboard_GPIO_init(void)
{
  	  GPIO_InitTypeDef keyboard_gpio_init_struct;

      keyboard_gpio_init_struct.GPIO_PTx = PTD;
      keyboard_gpio_init_struct.GPIO_Pins = GPIO_Pin10 | GPIO_Pin11 | GPIO_Pin12 | GPIO_Pin13;
      keyboard_gpio_init_struct.GPIO_Dir = DIR_INPUT;
      keyboard_gpio_init_struct.GPIO_Output = OUTPUT_L;
      keyboard_gpio_init_struct.GPIO_PinControl = IRQC_FA | INPUT_PULL_UP;
      keyboard_gpio_init_struct.GPIO_Isr = Keyboard_Isr;
      LPLD_GPIO_Init(keyboard_gpio_init_struct);
      LPLD_GPIO_EnableIrq(keyboard_gpio_init_struct);

      keyboard_gpio_init_struct.GPIO_PTx = PTC;
      keyboard_gpio_init_struct.GPIO_Pins = GPIO_Pin14 | GPIO_Pin15;
      keyboard_gpio_init_struct.GPIO_Dir = DIR_INPUT;
      keyboard_gpio_init_struct.GPIO_Output = OUTPUT_L;
      keyboard_gpio_init_struct.GPIO_PinControl = IRQC_FA | INPUT_PULL_UP;
      keyboard_gpio_init_struct.GPIO_Isr = Keyboard_Isr;
      LPLD_GPIO_Init(keyboard_gpio_init_struct);
      LPLD_GPIO_EnableIrq(keyboard_gpio_init_struct);
}

void Time_Counter_Start(void)
{
	/* Timer count start */
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;         //使能PIT时钟
	PIT->MCR &= ~(PIT_MCR_MDIS_MASK | PIT_MCR_FRZ_MASK);    //使能PIT定时器时钟 ，调试模式下继续运行
	PIT->CHANNEL[0].TCTRL &= ~(PIT_TCTRL_TEN_MASK);
	PIT->CHANNEL[0].LDVAL = ~0;							 //设置溢出中断时间
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
	PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;
	PIT->CHANNEL[0].TCTRL |= (0 | PIT_TCTRL_TEN_MASK);
}

uint32 Time_Counter_Get(void)
{
	/* Timer count end */
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

void Keybord_Delay(void)
{
	uint16 i, n;
	for (i = 0; i<15000; i++)
	{
		for (n = 0; n<50; n++)
		{
			asm("nop");
		}
	}
}

void Keyboard_Isr(void)
{
	if(LPLD_GPIO_IsPinxExt(PORTC, GPIO_Pin14))
  	{
  		//OLED_Clear();
  		OLED_ShowString(0, 1, "PTC14");
  	}
  	if(LPLD_GPIO_IsPinxExt(PORTC, GPIO_Pin15))
  	{
  		//OLED_Clear();
  		OLED_ShowString(0, 1, "PTC15");
  	}
  	if(LPLD_GPIO_IsPinxExt(PORTD, GPIO_Pin10))
	{
		//OLED_Clear();
	  	OLED_ShowString(0, 1, "PTD10");
	}
	if(LPLD_GPIO_IsPinxExt(PORTD, GPIO_Pin11))
	{
		//OLED_Clear();
	  	OLED_ShowString(0, 1, "PTD11");
	}
	if(LPLD_GPIO_IsPinxExt(PORTD, GPIO_Pin12))
	{
		//OLED_Clear();
	  	OLED_ShowString(0, 1, "PTD12");
	}
	if(LPLD_GPIO_IsPinxExt(PORTD, GPIO_Pin13))
	{  	
		//OLED_Clear();
		OLED_ShowString(0, 1, "PTD13");
	}
}

/*
void Keyboard_Scan(void)
{
	if (PTD12_I == 0)						//¶æ»úKdÔö
	{
		Keybord_Delay();
		if (PTD12_I == 0)
		{
			steerDebugDuty++;
		}
	}
	if (PTD13_I == 0)						//¶æ»úKd¼õ
	{
		Keybord_Delay();
		if (PTD13_I == 0)
		{
		  	steerDebugDuty--;
		}
	}

	if (PTD10_I == 0)						//¶æ»úKdÔö
	{
		Keybord_Delay();
		if (PTD10_I == 0)
		{
			
		}
	}
	if (PTD11_I == 0)						//¶æ»úKd¼õ
	{
		Keybord_Delay();
		if (PTD11_I == 0)
		{
		  	
		}
	}

	if (PTC14_I == 0)						//ËÙ¶ÈÔö
	{
		Keybord_Delay();
		if (PTC14_I == 0)
		{
			PWM_Expect += 50;
		}
	}
	if (PTC15_I == 0)						//ËÙ¶È¼õ
	{
		Keybord_Delay();
		if (PTC15_I == 0)
		{
		  	PWM_Expect -= 50;
		}
	}
}
*/