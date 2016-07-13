#ifndef _TWINCAR_H_
#define _TWINCAR_H_
#include "common.h"
typedef enum {
	US_RI, 
	US_FA,
}UltrasoundState;
void Ultrasound_GPIO_Init(void);
void Ultrasound_Isr(void);
extern uint32 carDistance;
extern uint32 expDistance;
#endif