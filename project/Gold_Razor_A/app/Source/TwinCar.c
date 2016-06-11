#include "TwinCar.h"
#include "common.h"
#include "DebugerDriver.h"

int8 ultraSoundFlag = 0;
GPIO_InitTypeDef ultraSoundStruct;
uint32 carDistance = 0;

void UltraSound_GPIO_Init(void)
{
	
	ultraSoundStruct.GPIO_PTx = PTC;
	ultraSoundStruct.GPIO_Dir = DIR_INPUT;
	ultraSoundStruct.GPIO_Pins = GPIO_Pin11;
	ultraSoundStruct.GPIO_PinControl = IRQC_RI | INPUT_PULL_DOWN | INPUT_PF_EN;
	ultraSoundStruct.GPIO_Isr = Keyboard_Isr;
	LPLD_GPIO_Init(ultraSoundStruct);
}