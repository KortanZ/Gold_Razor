#ifndef _SEQUENCECTRL_H_
#define _SEQUENCECTRL_H_

#include "common.h"

void MainCtrl_Pit_Init(void);
void NVIC_Init(void);
void Main_Isr(void);

#endif