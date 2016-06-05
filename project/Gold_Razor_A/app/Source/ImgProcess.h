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
	TrackInf_DataStruct TrackInf_DataBlock;
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
	_Bool RightLost;
	uint8 RightTurn;
	_Bool RightTurnFlag;

	_Bool RightIncrease;
	_Bool Rightreduce;
	_Bool Right_1Con;
	_Bool RightCrossFlag;	
}RightFlag_Struct;

typedef enum{
	STRAIGHT,
	PSE_ST,
	CURV,
}RoadMode;

extern int16 MidAve;
extern uint8 brokeDownFlag;
extern float32 weight[];
extern float32 midLine[];
extern PIC_DateStruct PIC_DateBlock;
extern LeftFlag_Struct LeftFlag_Switch;
extern RightFlag_Struct RightFlag_Switch;

extern void Get_Img(void);
extern void Get_MidLine(void);
float32 Calc_Curv(uint8 *MidLine_Buff, uint8 index);
float32 Carmark_InvSqrt(float32 x);
float32 InvSlope_Calc(uint8 *MidLine_Buff, uint8 y1, uint8 y2);
RoadMode Road_Check(uint8 *MidLine_Buff, uint8 y);
void Mode_Change(PIDStruct *steerCtrler, PIDStruct *differCtrler);


#endif