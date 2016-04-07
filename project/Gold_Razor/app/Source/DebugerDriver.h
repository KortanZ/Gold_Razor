/* 
*This head file for debuger driver
*include UART and GPIO initial
*include timer initial
*/
#ifndef _DEBUGERDRIVER_
#define _DEBUGERDRIVER_ 

#include "common.h"

extern void UART_Debuger_Init(void);
extern void LED_Debuger_Init(void);
extern void Time_Counter_Start(void);
extern uint32 Time_Counter_Get(void);

#endif