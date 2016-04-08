#include "common.h"

void main(void)
{
	DisableInterrupts;


	Keyboard_GPIO_init();
	MainCtrl_Pit_Init();
	NVIC_Init();
	OLED_Init();
	OLED_Clear();
	
	Camera_init();
	//OLED_ShowNum(70, 5, PWM_Expect, Num_Len);
	EnableInterrupts;

	
	while (1)
	{
	  	
		Keyboard_Scan();
	}
}

