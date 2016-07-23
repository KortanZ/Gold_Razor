#include "TwinCar.h"
#include "common.h"
#include "DebugerDriver.h"
#include "oled.h"
#include "VirtualOsc.h"
#include "ImgProcess.h"

GPIO_InitTypeDef ultrasoundStruct;
UART_InitTypeDef uartInitStruct;
uint32 carDistance = 0;
uint32 expDistance = 103;
UltrasoundState usState = US_RI;
TwincarState tcState = TWINCAR_FORMER;
uint8 recv = 0;

/*超声波模块引脚初始化*/
void Ultrasound_GPIO_Init(void)
{
	
	ultrasoundStruct.GPIO_PTx = PTC;
	ultrasoundStruct.GPIO_Dir = DIR_INPUT;
	ultrasoundStruct.GPIO_Pins = GPIO_Pin11;
	ultrasoundStruct.GPIO_PinControl = IRQC_RI | INPUT_PULL_DOWN | INPUT_PF_EN;		//上升沿触发中断
	ultrasoundStruct.GPIO_Isr = Ultrasound_Isr;
	LPLD_GPIO_Init(ultrasoundStruct);
	LPLD_GPIO_EnableIrq(ultrasoundStruct);
}

/*超声波中断服务函数*/
void Ultrasound_Isr(void)
{
	//更改触发方式，上升沿触发改为下降沿触发，下降沿改为上升沿
	if (US_RI == usState)
	{
		Time_Counter_Start();	//上升沿触发则启动定时器
		ultrasoundStruct.GPIO_PinControl = IRQC_FA | INPUT_PULL_DOWN | INPUT_PF_EN;
		LPLD_GPIO_Init(ultrasoundStruct);
		LPLD_GPIO_EnableIrq(ultrasoundStruct);
		usState = US_FA;
	}
	else
	{
		carDistance = Time_Counter_Get();	//下降沿触发则取定时器值
		ultrasoundStruct.GPIO_PinControl = IRQC_RI | INPUT_PULL_DOWN | INPUT_PF_EN;
		LPLD_GPIO_Init(ultrasoundStruct);
		LPLD_GPIO_EnableIrq(ultrasoundStruct);
		usState = US_RI;
	}
	// VirtualSignal[0] = carDistance / 1000;
	// OutPut_Data();
	//printf("%d\n", carDistance / 100);
}

/*双车通信蓝牙初始化*/
void Bluetooth_Twincar_Init(void)
{
	uartInitStruct.UART_Uartx = UART2; //use UART2
	uartInitStruct.UART_BaudRate = 115200; //set baude 115200
	uartInitStruct.UART_RxPin = PTD2;  //RXD PTD2
	uartInitStruct.UART_TxPin = PTD3;  //TXD PTD3
	uartInitStruct.UART_RxIntEnable = TRUE;
	uartInitStruct.UART_RxIsr = Bluetooth_Twincar_Isr;
	//init UART
	LPLD_UART_Init(uartInitStruct);
	LPLD_UART_EnableIrq(uartInitStruct);
}

/*蓝牙通信奇偶校验*/
uint8 Bluetooth_ParityCheck(uint8 data)
{
	uint8 parity = 0x00;	//odd check
	while (data)
	{
	  parity = ~parity;
	  data = data & (data - 1);	//number of '1' in "data" decreased in every loop
	}

	return parity;
}

/*蓝牙通信中断服务函数*/
void Bluetooth_Twincar_Isr(void)
{
	uint8 recvTmp;
  	recvTmp = (uint8)LPLD_UART_GetChar(UART2);	//获取收到的蓝牙数据
  	if (Bluetooth_ParityCheck(recvTmp))		//奇偶校验通过则传出，否则弃用
  	{
  		recv = recvTmp;
  	}

}

/*延时*/
void Twincar_Delay(uint8 t)
{
	uint16 i, j;
	for (i = 0; i < (800 * t); ++i)
	{
		for (j = 0; j < 900; ++j);
	}
			
}

/*双车发车*/
void Twincar_Launch(void)
{
	uint8 SHAKE = 0x01;		//握手信息
	uint8 READY = 0x83;		//发车信息
	if (TWINCAR_FORMER == tcState)	//前车
	{
		while(0xFE != recv)		//发送握手信息直到收到回应
		{
			LPLD_UART_PutChar(UART2, SHAKE);
			Twincar_Delay(1);
		}
		while(0x7C != recv)		//发送发车信号直到收到回应
		{
			LPLD_UART_PutChar(UART2, READY);
			Twincar_Delay(1);
		}
		//OLED_ShowString(0, 5, "F Launched");

	}
	else	//后车
	{
		while(SHAKE != recv);	//等待前车信号
		LPLD_UART_PutChar(UART2, ~SHAKE);	//回应
		while(READY != recv);	//等待前车发车信号
		LPLD_UART_PutChar(UART2, ~READY);	//回应
		Twincar_Delay(8);
		//OLED_ShowString(0, 5, "B Launched");
	}
	LPLD_UART_DisableIrq(uartInitStruct);	//关闭蓝牙中断以防后边扰乱时序
}