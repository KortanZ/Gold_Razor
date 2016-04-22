#include "common.h"

void main(void)
{
	DisableInterrupts;

	OLED_Init();
	OLED_Clear();
	OLED_DrawBMP(0, 0, 128, 8, logo);
	NVIC_Init();
	MainCtrl_Pit_Init();
	Steer_Init();
	Motor_Init();
	Encoder_Init();
	Keyboard_GPIO_Init();
	UART_Debuger_Init();
	speedCtrler = SpeedCtrler_Init(3.2, 0.5, 0.8);
	Camera_init();
	Menu_Show();
	EnableInterrupts;
	while (1)
	{
		//Keyboard_Scan();
	}
}

