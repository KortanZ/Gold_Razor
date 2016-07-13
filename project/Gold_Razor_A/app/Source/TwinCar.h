#ifndef _TWINCAR_H_
#define _TWINCAR_H_
#include "common.h"
typedef enum {
	US_RI, 
	US_FA,
}UltrasoundState;
typedef enum {
	TWINCAR_FORMER,
	TWINCAR_BACK,
}TwincarState;
extern void Ultrasound_GPIO_Init(void);
extern void Bluetooth_Twincar_Init(void);
extern void Twincar_Launch(void);
void Bluetooth_Twincar_Isr(void);
void Ultrasound_Isr(void);
void Bluetooth_Twincar_Isr(void);
extern uint32 carDistance;
#endif