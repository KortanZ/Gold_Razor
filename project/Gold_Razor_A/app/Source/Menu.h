/* 
*This head file for debuger driver
*include UART and GPIO initial
*include timer initial
*/
#ifndef _MENU_H_
#define _MENU_H_

#include "common.h"

/*菜单内容索引枚举*/
typedef enum{

	PID_STEER,			//舵机pid
	PID_MOTOR,			//电机pid
	PID_DIFF,			//差速pid
	PID_DIS,			//距离pid
	BANGBANG,			//棒棒阈值
	BROKEN_RESTART,		//停车重启
	SDHC_WRITE,			//sd卡写数据
	SDHC_READ,			//sd卡读数据
	CAMERA_SEND,		//向上位机发送图像

	STEER_ST,			//直道舵机pid
	STEER_PSEST,		//伪直道舵机pid
	STEER_CURV,			//弯道舵机pid

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
	DIFF_EN,			//差速增强因子
	STEER_BB,			//舵机棒棒阈值
	MOTOR_BB,			//电机棒棒阈值

	MOTOR_SPEED,		//电机速度

	STEER_MID,			//期望中线值
}ListType;

/*菜单结构体*/
typedef struct
{
	ListType previous;	//前一项索引
	ListType next;		//后一项索引
	ListType parent;	//父项索引
	ListType child;		//子项索引
	uint8 *str;			//当前项显示的字符
	void (*function)();	//当前项执行的功能
	void *data;			//当前项的数据
	uint8 indexInPage;	//当前显示页内的索引，与标号枚举的索引不同
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