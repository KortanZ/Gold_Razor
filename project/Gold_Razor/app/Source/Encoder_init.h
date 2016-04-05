#ifndef _ENCODER_INIT_H
#define _ENCODER_INIT_H

 #include "common.h"


 extern void Encoder_init(void);
 extern void UART_init(void);
 extern void pit_init(void);
 extern void NVIC_init(void);
 extern void pit0_time_start(void);
 extern uint32 pit0_time_get(void);

 extern uint16 qd_result_ftm,qd_result_lptmr;
 extern float32 Left_Pulse,Right_Pulse,Motor_Speed;

#endif