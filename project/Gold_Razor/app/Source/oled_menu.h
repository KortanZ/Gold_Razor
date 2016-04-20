#ifndef _OLED_MENU_H_
#define _OLED_MENU_H_
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

MenuType menuList[] = {
	{RACE, RACE, DEBUG, PID_STEER, "Debug Mode", NULL, 0}, 			//调试模式
	{DEBUG, DEBUG, RACE, RACE, "Race Mode", NULL, 1}, 					//比赛模式

	{PID_DIFF, PID_MOTOR, DEBUG, STEER_KP, "Steer", NULL, 0},
	{PID_STEER, PID_DIFF, DEBUG, MOTOR_KP, "Motor", NULL, 1},
	{PID_MOTOR, PID_STEER, DEBUG, DIFF_KP, "Diff", NULL, 2},

	{STEER_KI, STEER_KD, PID_STEER, STEER_KP, "Steer_Kp:", NULL, 0},
	{STEER_KP, STEER_KI, PID_STEER, STEER_KD, "Steer_kd:", NULL, 1},
	{STEER_KD, STEER_KP, PID_STEER, STEER_KI, "Steer_Ki:", NULL, 2},

	{MOTOR_KI, MOTOR_KD, PID_MOTOR, MOTOR_KP, "MOTOR_Kp:", NULL, 0},
	{MOTOR_KP, MOTOR_KI, PID_MOTOR, MOTOR_KD, "MOTOR_kd:", NULL, 1},
	{MOTOR_KD, MOTOR_KP, PID_MOTOR, MOTOR_KI, "MOTOR_Ki:", NULL, 2},
	
	{DIFF_KI, DIFF_KD, PID_DIFF, DIFF_KP, "DIFF_Kp:", NULL, 0},
	{DIFF_KP, DIFF_KI, PID_DIFF, DIFF_KD, "DIFF_kd:", NULL, 1},
	{DIFF_KD, DIFF_KP, PID_DIFF, DIFF_KI, "DIFF_Ki:", NULL, 2},
}


#endif