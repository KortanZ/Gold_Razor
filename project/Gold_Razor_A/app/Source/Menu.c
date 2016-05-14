#include "Menu.h"
#include "oled.h"
#include "PID.h"
#include "MotorDriver.h"
#include "SteerDriver.h"
#include "SequenceCtrl.h"
#include "ImgProcess.h"

ListType currentList = DEBUG;

MenuType menuList[] = {
	{RACE, RACE, DEBUG, PID_STEER, "Debug Mode", NULL, NULL, 0}, 			//调试模式
	{DEBUG, DEBUG, RACE, RACE, "Race Mode", NULL, NULL, 1}, 					//比赛模式

	{BROKEN_RESTART, PID_MOTOR, DEBUG, STEER_KP, "Steer", NULL, NULL, 0},
	{PID_STEER, PID_DIFF, DEBUG, MOTOR_KP, "Motor", NULL, NULL, 1},
	{PID_MOTOR, IMG_WEIGHT, DEBUG, DIFF_KP, "Diff", NULL , NULL, 2},
	{PID_DIFF, CAMERA_SEND, DEBUG, BLOCK0, "Img Weight", NULL , NULL, 3},
	{IMG_WEIGHT, BROKEN_RESTART, DEBUG, CAMERA_SEND, "Img Send Stoped", (*Img_Send_Change), NULL, 4},
	{CAMERA_SEND, PID_STEER, DEBUG, BROKEN_RESTART, "Restart", (*Broken_Down_Restart), NULL, 5},

	{STEER_MID, STEER_KD, PID_STEER, STEER_KP, "Steer_Kp:", NULL, NULL, 0},
	{STEER_KP, STEER_KI, PID_STEER, STEER_KD, "Steer_Kd:", NULL, NULL, 1},
	{STEER_KD, STEER_MID, PID_STEER, STEER_KI, "Steer_Ki:", NULL, NULL, 2},

	{MOTOR_SPEED, MOTOR_KD, PID_MOTOR, MOTOR_KP, "Motro_Kp:", NULL, NULL, 0},
	{MOTOR_KP, MOTOR_KI, PID_MOTOR, MOTOR_KD, "Motor_Kd:", NULL, NULL, 1},
	{MOTOR_KD, MOTOR_SPEED, PID_MOTOR, MOTOR_KI, "Motor_Ki:", NULL, NULL, 2},

	{DIFF_EN, DIFF_KD, PID_DIFF, DIFF_KP, "Diff_Kp:", NULL, NULL, 0},
	{DIFF_KP, DIFF_KI, PID_DIFF, DIFF_KD, "Diff_Kd:", NULL, NULL, 1},
	{DIFF_KD, DIFF_EN, PID_DIFF, DIFF_KI, "Diff_Ki:", NULL, NULL, 2},
	{DIFF_KI, DIFF_KP, PID_DIFF, DIFF_EN, "Diff_En:", NULL, NULL, 3},

	{BLOCK3, BLOCK1, IMG_WEIGHT, BLOCK0, "BLOCK0:", NULL, NULL, 0},
	{BLOCK0, BLOCK2, IMG_WEIGHT, BLOCK1, "BLOCK1:", NULL, NULL, 1},
	{BLOCK1, BLOCK3, IMG_WEIGHT, BLOCK2, "BLOCK2:", NULL, NULL, 2},
	{BLOCK2, BLOCK0, IMG_WEIGHT, BLOCK3, "BLOCK3:", NULL, NULL, 3},
	
	{MOTOR_KI, MOTOR_KP, PID_MOTOR, MOTOR_SPEED, "Motor_Sp:", NULL, NULL, 3},

	{STEER_KI, STEER_KP, PID_STEER, STEER_MID, "Steer_Mid:", NULL, NULL, 3},
};

void Menu_Show(void)
{
	uint8 i;
	ListType list = currentList;
	uint8 page = (uint8)(menuList[list].indexInPage / 4);
	for(i = 1; i < 5; i++)
	{
		OLED_ClearLine(i);
	}
	do
	{
		if((uint8)(menuList[list].indexInPage / 4) == page)
		{
			OLED_ShowString(8, (menuList[list].indexInPage % 4) + 1, menuList[list].str);
			Menu_Num_Show(list);
		}
		list = menuList[list].next;
	}while(list != currentList);
	OLED_ShowChar(0, (menuList[currentList].indexInPage % 4) + 1, '>');
}

void Menu_Num_Show(ListType lst)
{

	if(NULL != menuList[lst].data)
	{
		if(lst >= STEER_KP && lst <= DIFF_EN)
			OLED_ShowNum(70, (menuList[lst].indexInPage % 4) + 1, (int32)(*((float32 *)menuList[lst].data) * 10), Num_Len);
		else if(lst >= BLOCK0 && lst <= BLOCK3)
			OLED_ShowNum(70, (menuList[lst].indexInPage % 4) + 1, (int32)(*((float32 *)menuList[lst].data) * 100), Num_Len);
		else if(lst >= MOTOR_SPEED && lst <= MOTOR_SPEED)
		  	OLED_ShowNum(70, (menuList[lst].indexInPage % 4) + 1, (int32)(*((int32 *)menuList[lst].data)), Num_Len);
		else if(lst >= STEER_MID && lst <= STEER_MID)
			OLED_ShowNum(70, (menuList[lst].indexInPage % 4) + 1, (int32)(*((uint8 *)menuList[lst].data)), Num_Len);
	}
}

void Menu_Data_Link(void)
{
	menuList[MOTOR_KP].data = (void *)(&(speedCtrler -> Kp));
	menuList[MOTOR_KD].data = (void *)(&(speedCtrler -> Kd));
	menuList[MOTOR_KI].data = (void *)(&(speedCtrler -> Ki));

	menuList[STEER_KP].data = (void *)(&(steerCtrler -> Kp));
	menuList[STEER_KD].data = (void *)(&(steerCtrler -> Kd));
	menuList[STEER_KI].data = (void *)(&(steerCtrler -> Ki));

	menuList[DIFF_KP].data = (void *)(&(differCtrler -> Kp));
	menuList[DIFF_KD].data = (void *)(&(differCtrler -> Kd));
	menuList[DIFF_KI].data = (void *)(&(differCtrler -> Ki));
	menuList[DIFF_EN].data = (void *)(&enhance);

	menuList[BLOCK0].data = (void *)(&weight[0]);
	menuList[BLOCK1].data = (void *)(&weight[1]);
	menuList[BLOCK2].data = (void *)(&weight[2]);
	menuList[BLOCK3].data = (void *)(&weight[3]);
	
	menuList[MOTOR_SPEED].data = (void *)(&PWM_Expect);

	menuList[STEER_MID].data = (void *)(&steerMidValue);
	

}

void Menu_Data_Increase(ListType lst)
{
	if(NULL != menuList[lst].data)
	{
		if(lst >= STEER_KP && lst <= DIFF_EN)
			*((float32 *)menuList[lst].data) += 0.1;
		else if(lst >= BLOCK0 && lst <= BLOCK3)
		  	*((float32 *)menuList[lst].data) += 0.01;
		else if(lst >= MOTOR_SPEED && lst <= MOTOR_SPEED)
		  	*((int32 *)menuList[lst].data) += 100;
		else if(lst >= STEER_MID && lst <= STEER_MID)
			*((uint8 *)menuList[lst].data) += 1;
	}
}

void Menu_Data_Decrease(ListType lst)
{
	if(NULL != menuList[lst].data)
	{
		if(lst >= STEER_KP && lst <= DIFF_EN)
			*((float32 *)menuList[lst].data) -= 0.1 ;
		else if(lst >= BLOCK0 && lst <= BLOCK3)
		  	*((float32 *)menuList[lst].data) -= 0.01;
		else if(lst >= MOTOR_SPEED && lst <= MOTOR_SPEED)
		  	*((int32 *)menuList[lst].data) -= 100;
		else if(lst >= STEER_MID && lst <= STEER_MID)
			*((uint8 *)menuList[lst].data) -= 1;
	}
}

void Img_Send_Change(void)
{
	imgSendFlag = ~imgSendFlag;
	if(0 == imgSendFlag)
		menuList[currentList].str = "Img Send Stoped";
	else
		menuList[currentList].str = "Img Send Begin";
}

void Broken_Down_Restart(void)
{
	brokeDownFlag = 0;
	OLED_ClearLine(5);
}