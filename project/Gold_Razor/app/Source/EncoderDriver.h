#ifndef _ENCODERDRIVER_H_
#define _ENCODERDRIVER_H_

#include "common.h"

typedef enum {
	ENCODER_LEFT, 
	ENCODER_RIGHT,
}EncoderPosition;

void Encoder_Init(void);
int16 Encoder_GetPulseNum(EncoderPosition position);
float32 PulseNum_To_PWM(float32 pulseNum);
float32 PWM_To_Pulse(uint32 pwm);


#endif