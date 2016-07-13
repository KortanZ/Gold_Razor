/* 
*This head file for debuger driver
*include UART and GPIO initial
*include timer initial
*/
#ifndef _MENU_H_
#define _MENU_H_

#include "common.h"

typedef enum{

	PID_STEER,
	PID_MOTOR,
	PID_DIFF,
	PID_DIS,
	BANGBANG,
	BROKEN_RESTART,
	SDHC_WRITE,
	SDHC_READ,
	CAMERA_SEND,

	STEER_ST,
	STEER_PSEST,
	STEER_CURV,

	STEER_ST_KP,
	STEER_ST_KD,
	STEER_ST_KI,
	STEER_PSEST_KP,
	STEER_PSEST_KD,
	STEER_PSEST_KI,
	STEER_CURV_KP,
	STEER_CURV_KD,
	STEER_CURV_KI,
	MOTOR_KP,
	MOTOR_KD,
	MOTOR_KI,
	DIS_KP,
	DIS_KD,
	DIS_KI,
	DIFF_KP,
	DIFF_KD,
	DIFF_KI,
	DIFF_EN,
	STEER_BB,
	MOTOR_BB,

	MOTOR_SPEED,

	STEER_MID,
}ListType;

typedef struct
{
	ListType previous;
	ListType next;
	ListType parent;
	ListType child;
	uint8 *str;
	void (*function)();
	void *data;
	uint8 indexInPage;
}MenuType;

extern ListType currentList;
extern MenuType menuList[];

void Menu_Show(void);
void Menu_Num_Show(ListType lst);
void Menu_Data_Link(void);
void Menu_Data_Increase(ListType lst);
void Menu_Data_Decrease(ListType lst);
void SDHC_Init(void);

void Img_Send_Change(void);
void Broken_Down_Restart(void);
void SDHC_Write_Data(void);
void SDHC_Read_Data(void);

#endif