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
	STEER_KP,
	STEER_KD,
	STEER_KI,
	MOTOR_KP,
	MOTOR_KD,
	MOTOR_KI,
	DIFF_KP,
	DIFF_KD,
	DIFF_KI,
}ListType;

typedef struct
{
	ListType previous;
	ListType next;
	ListType parent;
	ListType child;
	uint8 *str;
	void (*function);
	uint8 indexInPage;
}MenuType;

extern ListType currentList;
extern const MenuType menuList[];
extern const unsigned char logo[];

void Menu_Show(void);

#endif