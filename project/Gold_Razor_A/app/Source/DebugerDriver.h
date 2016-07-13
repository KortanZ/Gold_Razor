/* 
*This head file for debuger driver
*include UART and GPIO initial
*include timer initial
*/
#ifndef _DEBUGERDRIVER_H_
#define _DEBUGERDRIVER_H_

#include "common.h"

//#define Twin_Car 1

extern uint32 steerDebugDuty;

void Bluetooth_Debuger_Init(void);
//void Bluetooth_Twincar_Init(void);
void LED_Debuger_Init(void);
void Time_Counter_Start(void);
uint32 Time_Counter_Get(void);
void Keyboard_GPIO_Init(void);
void Keybord_Delay(void);
void Keyboard_Scan(void);
void Keyboard_Isr(void);
void Menu_Show(void);
void DebugMode_GPIO_Init(void);

//void Bluetooth_Twincar_Isr(void);


#endif