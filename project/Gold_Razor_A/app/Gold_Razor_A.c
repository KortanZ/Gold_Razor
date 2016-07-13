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
#include "twinCar.h"

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
	SDHC_Init();
	Encoder_Init();
	//UART_Debuger_Init();
	UART_Blooth_Init();
	LED_Debuger_Init();
	DebugMode_GPIO_Init();
	SpeedCtrler_Init();
	SteerCtrler_Init();
	DifferCtrler_Init();
	Distance_Ctrler_Init();
	Menu_Data_Link();
	if (!PTC9_I)
	{
	  	Keyboard_GPIO_Init();
	}
	else
	{
		Ultrasound_GPIO_Init();
		OLED_ShowString(0, 5, "Reading Data...");
		SDHC_Read_Data();
	}
	Camera_init();
	Menu_Show();
	EnableInterrupts;
	while (1)
	{
		if(imgSendFlag)
		{
		   	vcan_sendimg(imgbuff, CAMERA_SIZE);
		}
		Get_Img_Wait();
		Get_MidLine();
		Mode_Change(steerCtrler, differCtrler);
		clearflag();
		OLED_ShowString(0,0,"MidAve");
		OLED_ShowNum(70,0,MidAve,3);
	}
}

