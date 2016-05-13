#ifndef _SEQUENCECTRL_H_
#define _SEQUENCECTRL_H_

#include "common.h"

extern void MainCtrl_Pit_Init(void);
extern void NVIC_Init(void);
extern void Main_Isr(void);

extern uint8 imgSendFlag;

#endif