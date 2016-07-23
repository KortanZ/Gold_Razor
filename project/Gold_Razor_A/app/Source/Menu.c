#include "Menu.h"
#include "oled.h"
#include "PID.h"
#include "MotorDriver.h"
#include "SteerDriver.h"
#include "SequenceCtrl.h"
#include "ImgProcess.h"
#include "common.h"

ListType currentList = PID_STEER;

uint8 sdhcMessage[][9] = {"OK", "ERROR", "WRPRT", "NOTRDY", "PARERR", "NONRSPNS"};	//sd卡状态返回值提示的显示

MenuType menuList[] = {

	{CAMERA_SEND, PID_MOTOR, PID_STEER, STEER_ST, "Steer", NULL, NULL, 0},
	{PID_STEER, PID_DIFF, PID_MOTOR, MOTOR_KP, "Motor", NULL, NULL, 1},
	{PID_MOTOR, PID_DIS, PID_DIFF, DIFF_KP, "Diff", NULL , NULL, 2},
	{PID_DIFF, BANGBANG, PID_DIS, DIS_KP, "Distance", NULL , NULL, 3},
	{PID_DIS, BROKEN_RESTART, BANGBANG, STEER_BB, "Bang-Bang", NULL , NULL, 4},
	{BANGBANG, SDHC_WRITE, BROKEN_RESTART, BROKEN_RESTART, "Restart", (*Broken_Down_Restart), NULL, 5},
	{BROKEN_RESTART, SDHC_READ, SDHC_WRITE, SDHC_WRITE, "Write Data", (*SDHC_Write_Data), NULL, 6},
	{SDHC_WRITE, CAMERA_SEND, SDHC_READ, SDHC_READ, "Read Data", (*SDHC_Read_Data), NULL, 7},
	{SDHC_READ, PID_STEER, CAMERA_SEND, CAMERA_SEND, "Img Send Stoped", (*Img_Send_Change), NULL, 8},

	{STEER_MID, STEER_PSEST, PID_STEER, STEER_ST_KP, "SteerSt", NULL, NULL, 0},
	{STEER_ST, STEER_CURV, PID_STEER, STEER_PSEST_KP, "SteerPseSt", NULL, NULL, 1},
	{STEER_PSEST, STEER_MID, PID_STEER, STEER_CURV_KP, "SteerCurv", NULL, NULL, 2},

	{STEER_ST_KI, STEER_ST_KD, STEER_ST, STEER_ST_KP, "ST_Kp:", NULL, NULL, 0},
	{STEER_ST_KP, STEER_ST_KI, STEER_ST, STEER_ST_KD, "ST_Kd:", NULL, NULL, 1},
	{STEER_ST_KD, STEER_ST_KP, STEER_ST, STEER_ST_KI, "ST_Ki:", NULL, NULL, 2},

	{STEER_PSEST_KI, STEER_PSEST_KD, STEER_PSEST, STEER_PSEST_KP, "PSEST_Kp:", NULL, NULL, 0},
	{STEER_PSEST_KP, STEER_PSEST_KI, STEER_PSEST, STEER_PSEST_KD, "PSEST_Kd:", NULL, NULL, 1},
	{STEER_PSEST_KD, STEER_PSEST_KP, STEER_PSEST, STEER_PSEST_KI, "PSEST_Ki:", NULL, NULL, 2},

	{STEER_CURV_KI, STEER_CURV_KD, STEER_CURV, STEER_CURV_KP, "CURV_Kp:", NULL, NULL, 0},
	{STEER_CURV_KP, STEER_CURV_KI, STEER_CURV, STEER_CURV_KD, "CURV_Kd:", NULL, NULL, 1},
	{STEER_CURV_KD, STEER_CURV_KP, STEER_CURV, STEER_CURV_KI, "CURV_Ki:", NULL, NULL, 2},

	{MOTOR_SPEED, MOTOR_KD, PID_MOTOR, MOTOR_KP, "Motro_Kp:", NULL, NULL, 0},
	{MOTOR_KP, MOTOR_KI, PID_MOTOR, MOTOR_KD, "Motor_Kd:", NULL, NULL, 1},
	{MOTOR_KD, MOTOR_SPEED, PID_MOTOR, MOTOR_KI, "Motor_Ki:", NULL, NULL, 2},

	{DIS_KI, DIS_KD, PID_DIS, DIS_KP, "Dis_Kp:", NULL, NULL, 0},
	{DIS_KP, DIS_KI, PID_DIS, DIS_KD, "Dis_Kd:", NULL, NULL, 1},
	{DIS_KD, DIS_KP, PID_DIS, DIS_KI, "Dis_Ki:", NULL, NULL, 2},

	{DIFF_EN, DIFF_KD, PID_DIFF, DIFF_KP, "Diff_Kp:", NULL, NULL, 0},
	{DIFF_KP, DIFF_KI, PID_DIFF, DIFF_KD, "Diff_Kd:", NULL, NULL, 1},
	{DIFF_KD, DIFF_EN, PID_DIFF, DIFF_KI, "Diff_Ki:", NULL, NULL, 2},
	{DIFF_KI, DIFF_KP, PID_DIFF, DIFF_EN, "Diff_En:", NULL, NULL, 3},

	{MOTOR_BB, MOTOR_BB, BANGBANG, STEER_BB, "Steer TH:", NULL, NULL, 0},
	{STEER_BB, STEER_BB, BANGBANG, MOTOR_BB, "Motor TH:", NULL, NULL, 1},
	
	{MOTOR_KI, MOTOR_KP, PID_MOTOR, MOTOR_SPEED, "Motor_Sp:", NULL, NULL, 3},

	{STEER_CURV, STEER_ST, PID_STEER, STEER_MID, "Steer_Mid:", NULL, NULL, 3},
};	//菜单

/*菜单显示函数*/
void Menu_Show(void)
{
	uint8 i;
	ListType list = currentList;
	uint8 page = (uint8)(menuList[list].indexInPage / 4);	//按每页显示4条项，用页内索引计算应该显示在第几页
	/*将屏幕将要显示菜单的几行清屏*/
	for(i = 1; i < 5; i++)
	{
		OLED_ClearLine(i);
	}
	/*显示菜单*/
	do
	{
		if((uint8)(menuList[list].indexInPage / 4) == page)
		{
			OLED_ShowString(8, (menuList[list].indexInPage % 4) + 1, menuList[list].str);	//显示该项的字符
			Menu_Num_Show(list);	//显示该项的数据
		}
		list = menuList[list].next;
	}while(list != currentList);
	OLED_ShowChar(0, (menuList[currentList].indexInPage % 4) + 1, '>');	//显示指示符
}

/*数据显示*/
void Menu_Num_Show(ListType lst)
{

	if(NULL != menuList[lst].data)
	{
		if(lst >= STEER_ST_KP && lst <= DIFF_EN) //float32型的扩大100倍消除小数后再显示
			//数据链接时数据指针为统一方便存储全强转为void *，这里要按原来的类型还原
			OLED_ShowNum(70, (menuList[lst].indexInPage % 4) + 1, (int32)(*((float32 *)menuList[lst].data) * 100), Num_Len);
		else if(lst >= STEER_BB && lst <= MOTOR_BB)
		  	OLED_ShowNum(70, (menuList[lst].indexInPage % 4) + 1, (int32)(*((int16 *)menuList[lst].data)), Num_Len);
		else if(lst >= MOTOR_SPEED && lst <= MOTOR_SPEED)
		  	OLED_ShowNum(70, (menuList[lst].indexInPage % 4) + 1, (int32)(*((int32 *)menuList[lst].data)), Num_Len);
		else if(lst >= STEER_MID && lst <= STEER_MID)
			OLED_ShowNum(70, (menuList[lst].indexInPage % 4) + 1, (int32)(*((uint8 *)menuList[lst].data)), Num_Len);
	}
}

/*内存变量与菜单项链接*/
//统一强转为void方便统一存储
void Menu_Data_Link(void)
{

	menuList[STEER_ST_KP].data = (void *)(&(steerCtrlerStPara -> Kp));
	menuList[STEER_ST_KD].data = (void *)(&(steerCtrlerStPara -> Kd));
	menuList[STEER_ST_KI].data = (void *)(&(steerCtrlerStPara -> Ki));

	menuList[STEER_PSEST_KP].data = (void *)(&(steerCtrlerPseStPara -> Kp));
	menuList[STEER_PSEST_KD].data = (void *)(&(steerCtrlerPseStPara -> Kd));
	menuList[STEER_PSEST_KI].data = (void *)(&(steerCtrlerPseStPara -> Ki));

	menuList[STEER_CURV_KP].data = (void *)(&(steerCtrlerCurvPara -> Kp));
	menuList[STEER_CURV_KD].data = (void *)(&(steerCtrlerCurvPara -> Kd));
	menuList[STEER_CURV_KI].data = (void *)(&(steerCtrlerCurvPara -> Ki));

	menuList[MOTOR_KP].data = (void *)(&(speedCtrlerPara -> Kp));
	menuList[MOTOR_KD].data = (void *)(&(speedCtrlerPara -> Kd));
	menuList[MOTOR_KI].data = (void *)(&(speedCtrlerPara -> Ki));

	menuList[DIS_KP].data = (void *)(&(distancePara -> Kp));
	menuList[DIS_KD].data = (void *)(&(distancePara -> Kd));
	menuList[DIS_KI].data = (void *)(&(distancePara -> Ki));

	menuList[DIFF_KP].data = (void *)(&(differCtrlerCurvPara -> Kp));
	menuList[DIFF_KD].data = (void *)(&(differCtrlerCurvPara -> Kd));
	menuList[DIFF_KI].data = (void *)(&(differCtrlerCurvPara -> Ki));
	menuList[DIFF_EN].data = (void *)(&enhance);

	menuList[STEER_BB].data = (void *)(&(steerThersh));
	menuList[MOTOR_BB].data = (void *)(&(motorThersh));

	menuList[MOTOR_SPEED].data = (void *)(&PWM_Expect_Base);

	menuList[STEER_MID].data = (void *)(&steerMidValue);
	

}

/*数据增加*/
void Menu_Data_Increase(ListType lst)
{
	if(NULL != menuList[lst].data)
	{
		if(lst >= STEER_ST_KP && lst <= DIFF_EN)
			*((float32 *)menuList[lst].data) += 0.01;
		else if(lst >= STEER_BB && lst <= MOTOR_BB)
		  	*((int16 *)menuList[lst].data) += 1;
		else if(lst >= MOTOR_SPEED && lst <= MOTOR_SPEED)
		  	*((int32 *)menuList[lst].data) += 100;
		else if(lst >= STEER_MID && lst <= STEER_MID)
			*((uint8 *)menuList[lst].data) += 1;
	}
}

/*数据减小*/
void Menu_Data_Decrease(ListType lst)
{
	if(NULL != menuList[lst].data)
	{
		if(lst >= STEER_ST_KP && lst <= DIFF_EN)
			*((float32 *)menuList[lst].data) -= 0.01;
		else if(lst >= STEER_BB && lst <= MOTOR_BB)
		  	*((int16 *)menuList[lst].data) -= 1;
		else if(lst >= MOTOR_SPEED && lst <= MOTOR_SPEED)
		  	*((int32 *)menuList[lst].data) -= 100;
		else if(lst >= STEER_MID && lst <= STEER_MID)
			*((uint8 *)menuList[lst].data) -= 1;
	}
}

/*图像发送和停止*/
void Img_Send_Change(void)
{
	imgSendFlag = ~imgSendFlag;
	if(0 == imgSendFlag)
		menuList[currentList].str = "Img Send Stoped";
	else
		menuList[currentList].str = "Img Send Begin";
}

/*停车重启*/
void Broken_Down_Restart(void)
{
	brokeDownFlag = 0;
	OLED_ClearLine(5);
}

/*sd卡初始化*/
void SDHC_Init(void)
{
	SDHCRES sd_state;
	sd_state = (SDHCRES)LPLD_SDHC_InitCard();
	if(sd_state)
	{
		OLED_ClearLine(5);
		OLED_ShowString(0, 5, sdhcMessage[sd_state]);
	}
}

/*sd卡写数据*/
void SDHC_Write_Data(void)
{

	uint8 i, flag = 0;
	SDHCRES sd_state;
	uint8 *sdhcBuff = (uint8 *)malloc(sizeof(512));		//一次写512字节

	if (NULL == sdhcBuff)	//调用malloc函数必须判断内存是否申请成功，否则为危险操作
	{
		OLED_ClearLine(5);
		OLED_ShowString(0, 5, "SDHC alloc Failed");
	}
	else	//为了方便操作和统一管理，用了一种比较占空间的方法，每个数据都强转为float32型存储，存储在512字节的前4字节，
			//也就是每个数据占用512字节，后期可以改成把数据写入缓冲区在写进sd卡，这样就只用512字节就可以存下所有数据
	{
		for (i = PID_STEER; i < STEER_MID; ++i)
		{
			if(NULL != menuList[i].data)
			{
				if(i >= STEER_ST_KP && i <= MOTOR_BB)
				{
					*((float32 *)sdhcBuff) = (float32)(*((float32 *)(menuList[i].data)));
					sd_state = LPLD_SDHC_WriteBlocks((uint8 *)sdhcBuff, i, 1);
				}
				else if(i >= MOTOR_SPEED && i <= MOTOR_SPEED)
				{
					*((float32 *)sdhcBuff) = (float32)(*((int32 *)(menuList[i].data)));
					sd_state = LPLD_SDHC_WriteBlocks((uint8 *)sdhcBuff, i, 1);
				}
				else if(i >= STEER_MID && i <= STEER_MID)
				{
					*((float32 *)sdhcBuff) = (float32)(*((uint8 *)(menuList[i].data)));
					sd_state = LPLD_SDHC_WriteBlocks((uint8 *)sdhcBuff, i, 1);
				}

				if(sd_state)	//判断每次写数据是否成功，一次不成功就将标志位置位
				{
					flag = 1;
				}
			}
		}

		if (flag)
		{
			OLED_ClearLine(5);
			OLED_ShowString(0, 5, "SDHC Write Failed");
		}
		else
		{
			OLED_ClearLine(5);
			OLED_ShowString(0, 5, "SDHC Write Ok");
		}

		free(sdhcBuff);		//malloc后不用了一定要free，不然会内存溢出
	}

}

/*sd卡读数据*/
void SDHC_Read_Data(void)
{

	uint8 i, flag = 0;
	SDHCRES sd_state;
	uint8 *sdhcBuff = (uint8 *)malloc(sizeof(512));

	if (NULL == sdhcBuff)
	{
		OLED_ClearLine(5);
		OLED_ShowString(0, 5, "SDHC alloc Failed");
	}
	else
	{
		for (i = PID_STEER; i < STEER_MID; ++i)
		{
			if(NULL != menuList[i].data)
			{
				if(i >= STEER_ST_KP && i <= MOTOR_BB)
				{
					sd_state = LPLD_SDHC_ReadBlocks((uint8 *)sdhcBuff, i, 1);
					*((float32 *)(menuList[i].data)) = (float32)(*((float32 *)sdhcBuff));
				}
				else if(i >= MOTOR_SPEED && i <= MOTOR_SPEED)
				{
					sd_state = LPLD_SDHC_ReadBlocks((uint8 *)sdhcBuff, i, 1);
					*((int32 *)(menuList[i].data)) = (int32)(*((float32 *)sdhcBuff));
				}
				else if(i >= STEER_MID && i <= STEER_MID)
				{
					sd_state = LPLD_SDHC_ReadBlocks((uint8 *)sdhcBuff, i, 1);
					*((uint8 *)(menuList[i].data)) = (uint8)(*((float32 *)sdhcBuff));
				}

				if(sd_state)
				{
					flag = 1;
				}
			}
		}

		if (flag)
		{
			OLED_ClearLine(5);
			OLED_ShowString(0, 5, "SDHC Read Failed");
		}
		else
		{
			OLED_ClearLine(5);
			OLED_ShowString(0, 5, "SDHC Read Ok");
		}

		free(sdhcBuff);
	}

}