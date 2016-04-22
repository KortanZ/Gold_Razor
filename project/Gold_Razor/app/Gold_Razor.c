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
	All_PID_Init();
	Camera_init();
	OLED_Clear();
	Menu_Data_Link();
	Menu_Show();
	EnableInterrupts;
	while (1);
}

