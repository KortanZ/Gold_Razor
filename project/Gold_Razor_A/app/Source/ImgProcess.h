/* 
*This head file for image processing
*include edge extacting
*include 
*/
#ifndef _IMGPROCESS_H_
#define _IMGPROCESS_H_

#include "common.h"
#include "Eagle_ov7725.h"
#include "PID.h"

#define Black 0
#define White 255

#define LeftimgS -5
#define RightimgS 5

typedef struct 
{
	int16 LeftLine[PICTURE_H];
	int16 RightLine[PICTURE_H];
	uint8 MidLine[PICTURE_H];
	uint8 TrackWidth;
}TrackInf_DataStruct;

typedef struct
{
	uint8 pic[PICTURE_W * PICTURE_H];
	int16 LeftLine[PICTURE_H];
	int16 RightLine[PICTURE_H];
	int16 MidLine[PICTURE_H];
	uint8 TrackWidth[PICTURE_H];
}PIC_DateStruct;

typedef struct
{
	uint8 LeftCrossStart_H;
	uint8 LeftCrossStart_L;
	uint8 LeftCrossEnd_H;
	uint8 LeftCrossEnd_L;

	uint8 RightCrossStart_H;
	uint8 RightCrossStart_L;
	uint8 RightCrossEnd_H;
	uint8 RightCrossEnd_L;

	uint8 SpeCross;
} CrossInf_Struct;

typedef struct
{
	_Bool LeftBlackLost;
	_Bool LeftWhiteLost;
	_Bool LastLeftWhiteLost;
	_Bool LeftLost;
	uint8 LeftTurn;
	_Bool LeftTurnFlag;

	_Bool LeftIncrease;
	_Bool Leftreduce;
	_Bool Left_1Con;
	_Bool LeftCrossFlag;
}LeftFlag_Struct;

typedef struct
{
	_Bool RightBlackLost;
	_Bool RightWhiteLost;
	_Bool LastRightWhiteLost;
	_Bool RightLost;
	uint8 RightTurn;
	_Bool RightTurnFlag;

	_Bool RightIncrease;
	_Bool Rightreduce;
	_Bool Right_1Con;
	_Bool RightCrossFlag;
}RightFlag_Struct;


typedef enum{
	STRAIGHT, //直道
	PSE_ST, //伪直道
	CURV, //弯道
}RoadMode;

extern int16 MidAve;
extern uint8 brokeDownFlag;
extern float32 weight[];
extern float32 midLine[];
extern PIC_DateStruct PIC_DateBlock;
extern LeftFlag_Struct LeftFlag_Switch;
extern RightFlag_Struct RightFlag_Switch;

void Get_Img_Start(void);
void Get_Img_Wait(void);
void Get_MidLine(void);
uint8 Bef_Scan(uint8 *pic_buff);
void TwinLine_Deal(uint8 *pic_buff,int8 Row_buff);
void LinerFitting(int16 *Tar,uint8 Start_H,uint8 End_H,uint8 End_L);
void CrossDeal(void);
void BlackDeal(int8 Row_Buff);
void Get_MidAve(int16 *MidLine_Buff,float32 Coe_1,float32 Coe_2,float32 Coe_3,float32 Coe_4);
void clearflag(void);
void Cross_StartCheck(int8 Row_buff);

RoadMode Road_Check(int16 *MidLine_Buff, uint8 y);
void Mode_Change(PIDStruct *steerCtrler, PIDStruct *differCtrler);

#endif