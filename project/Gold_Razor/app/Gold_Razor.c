#include "common.h"

int16 test = -399;

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
	SpeedCtrler_Init();
	Camera_init();
	OLED_Clear();
	Menu_Show();
	OLED_ShowNum(0, 5, test, Num_Len);
	EnableInterrupts;
	while (1);
}

