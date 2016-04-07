#ifndef _ENCODERDRIVER_
#define _ENCODERDRIVER_H_

#include "common.h"

enum EncoderPosition {Left, Right};

void Encoder_Init(void);
uint16 Encoder_GetPulseNum(EncoderPosition position);


#endif