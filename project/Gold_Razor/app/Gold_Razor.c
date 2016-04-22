#include "common.h"

void main(void)
{
	DisableInterrupts;

	NVIC_Init();
	Steer_Init();
	MainCtrl_Pit_Init();
	Motor_Init();
	Encoder_Init();
	OLED_Init();
	OLED_Clear();
	Keyboard_GPIO_init();
	UART_Debuger_Init();
	Camera_init();

	SpeedCtrler_Init();

	EnableInterrupts;
	while (1)
	{
		//Keyboard_Scan();
	}
}

