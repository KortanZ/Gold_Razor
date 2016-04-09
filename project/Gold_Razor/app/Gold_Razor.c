#include "common.h"

void main(void)
{
	DisableInterrupts;

	NVIC_Init();
	Steer_Init();
	MainCtrl_Pit_Init();
	Motor_Init();
	OLED_Init();
	OLED_Clear();
	Keyboard_GPIO_init();
	UART_Debuger_Init();
	Encoder_Init();
	Camera_init();
	EnableInterrupts;
	while (1)
	{
		Keyboard_Scan();
	}
}

