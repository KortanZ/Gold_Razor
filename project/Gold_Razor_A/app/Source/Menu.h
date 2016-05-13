/* 
*This head file for debuger driver
*include UART and GPIO initial
*include timer initial
*/
#ifndef _MENU_H_
#define _MENU_H_

#include "common.h"

typedef enum{
	DEBUG,
	RACE,
	
	PID_STEER,
	PID_MOTOR,
	PID_DIFF,
	CAMERA_SEND,
	BROKEN_RESTART,
	STEER_KP,
	STEER_KD,
	STEER_KI,
	MOTOR_KP,
	MOTOR_KD,
	MOTOR_KI,
	DIFF_KP,
	DIFF_KD,
	DIFF_KI,
	
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

void Img_Send_Change(void);
void Broken_Down_Restart(void);

#endif