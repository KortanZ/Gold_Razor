#include "TwinCar.h"
#include "common.h"
#include "DebugerDriver.h"
#include "oled.h"
#include "VirtualOsc.h"

GPIO_InitTypeDef ultrasoundStruct;
uint32 carDistance = 0;
uint32 expDistance;
UltrasoundState usState = US_RI;

void Ultrasound_GPIO_Init(void)
{
	
	ultrasoundStruct.GPIO_PTx = PTC;
	ultrasoundStruct.GPIO_Dir = DIR_INPUT;
	ultrasoundStruct.GPIO_Pins = GPIO_Pin11;
	ultrasoundStruct.GPIO_PinControl = IRQC_RI | INPUT_PULL_DOWN | INPUT_PF_EN;
	ultrasoundStruct.GPIO_Isr = Ultrasound_Isr;
	LPLD_GPIO_Init(ultrasoundStruct);
	LPLD_GPIO_EnableIrq(ultrasoundStruct);
}

void Ultrasound_Isr(void)
{
	if (US_RI == usState)
	{
		Time_Counter_Start();
		ultrasoundStruct.GPIO_PinControl = IRQC_FA | INPUT_PULL_DOWN | INPUT_PF_EN;
		LPLD_GPIO_Init(ultrasoundStruct);
		LPLD_GPIO_EnableIrq(ultrasoundStruct);
		usState = US_FA;
	}
	else
	{
		carDistance = Time_Counter_Get();
		ultrasoundStruct.GPIO_PinControl = IRQC_RI | INPUT_PULL_DOWN | INPUT_PF_EN;
		LPLD_GPIO_Init(ultrasoundStruct);
		LPLD_GPIO_EnableIrq(ultrasoundStruct);
		usState = US_RI;
	}
	// VirtualSignal[0] = carDistance / 100;
	// OutPut_Data();
}




