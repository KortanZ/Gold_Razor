#ifndef _ENCODERDRIVER_H_
#define _ENCODERDRIVER_H_

#include "common.h"

typedef enum {
	Left, 
	Right
}EncoderPosition;

extern void Encoder_Init(void);
extern uint16 Encoder_GetPulseNum(EncoderPosition position);


#endif