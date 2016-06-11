#include "Oled.h"
#include "SequenceCtrl.h"
#include "SteerDriver.h"
#include "MotorDriver.h"
#include "EncoderDriver.h"
#include "DebugerDriver.h"
#include "PID.h"
#include "Eagle_ov7725.h"
#include "Menu.h"
#include "ImgProcess.h"
#include "common.h"

/*     main function entrance    */

void main(void)
{  
	DisableInterrupts;
	OLED_Init();
	OLED_Clear();
	NVIC_Init();
	MainCtrl_Pit_Init();
	Steer_Init();
	Motor_Init();
	Encoder_Init();
	Keyboard_GPIO_Init();
	UART_Debuger_Init();
	LED_Debuger_Init();
	SpeedCtrler_Init();
	SteerCtrler_Init();
	DifferCtrler_Init();
	Camera_init();
	SDHC_Init();
	Menu_Data_Link();
	Menu_Show();
	EnableInterrupts;
	while (1)
	{
		if(imgSendFlag)
		{
		   	vcan_sendimg(imgbuff, CAMERA_SIZE);
		}
		//Keyboard_Locker();
		Get_Img();
		Get_MidLine();
		Mode_Change(steerCtrler, differCtrler);
		clearflag();
		OLED_ShowString(0,0,"MidAve");
		OLED_ShowNum(70,0,MidAve,3);
	}
}

