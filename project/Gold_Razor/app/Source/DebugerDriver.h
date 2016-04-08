/* 
*This head file for debuger driver
*include UART and GPIO initial
*include timer initial
*/
#ifndef _DEBUGERDRIVER_H_
#define _DEBUGERDRIVER_H_

#include "common.h"

extern uint32 steerDebugDuty;

extern void UART_Debuger_Init(void);
extern void LED_Debuger_Init(void);
extern void Time_Counter_Start(void);
extern uint32 Time_Counter_Get(void);
extern void Keyboard_GPIO_init(void);
extern void Keybord_Delay(void);
extern void Keyboard_Scan(void);

#endif