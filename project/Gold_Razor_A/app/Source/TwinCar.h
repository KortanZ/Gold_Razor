#ifndef _TWINCAR_H_
#define _TWINCAR_H_
#include "common.h"
#include "Eagle_ov7725.h"
extern void UltraSound_GPIO_Init(void);
extern int8 ultraSoundFlag;
extern GPIO_InitTypeDef ultraSoundStruct;
extern uint32 carDistance;
#endif