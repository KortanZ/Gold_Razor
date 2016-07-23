#ifndef _TWINCAR_H_
#define _TWINCAR_H_
#include "common.h"
typedef enum {
	US_RI, 
	US_FA,
}UltrasoundState;	//超声波中断出发方式状态
typedef enum {
	TWINCAR_FORMER,
	TWINCAR_BACK,
}TwincarState;		//双车车位状态
extern void Ultrasound_GPIO_Init(void);
extern void Bluetooth_Twincar_Init(void);
extern void Twincar_Launch(void);
void Bluetooth_Twincar_Isr(void);
void Ultrasound_Isr(void);
void Bluetooth_Twincar_Isr(void);
extern uint32 carDistance;
extern uint32 expDistance;
#endif