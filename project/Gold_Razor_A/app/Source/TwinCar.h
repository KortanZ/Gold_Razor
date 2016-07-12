#ifndef _TWINCAR_H_
#define _TWINCAR_H_
#include "common.h"
typedef enum {
	US_RI, 
	US_FA,
}UltrasoundState;
extern void Ultrasound_GPIO_Init(void);
extern void Ultrasound_Isr(void);
extern uint32 carDistance;
#endif