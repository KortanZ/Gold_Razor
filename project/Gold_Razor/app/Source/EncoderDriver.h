#ifndef _ENCODERDRIVER_H_
#define _ENCODERDRIVER_H_

#include "common.h"

typedef enum {
	ENCODER_LEFT, 
	ENCODER_RIGHT,
}EncoderPosition;

void Encoder_Init(void);
uint16 Encoder_GetPulseNum(EncoderPosition position);
float32 PulseNum_To_Speed(uint16 pulseNum);


#endif