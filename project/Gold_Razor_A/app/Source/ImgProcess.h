/* 
*This head file for image processing
*include edge extacting
*include 
*/
#ifndef _IMGPROCESS_H_
#define _IMGPROCESS_H_

#include "common.h"
#include "Eagle_ov7725.h"

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
	_Bool LeftBlackLost;
	_Bool LeftWhiteLost;
	_Bool LeftLost;
	uint8 LeftTurn;
	_Bool LeftTurnFlag;
}LeftFlag_Struct;

typedef struct 
{
	_Bool RightBlackLost;
	_Bool RightWhiteLost;
	_Bool RightLost;
	uint8 RightTurn;
	_Bool RightTurnFlag;
}RightFlag_Struct;

extern int16 MidAve;
extern uint8 brokeDownFlag;

extern void Get_Img(void);
extern void Get_MidLine(void);


#endif