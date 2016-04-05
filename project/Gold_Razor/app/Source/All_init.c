#include "All_init.h"




void All_init(void)
{
  //GPIO_init();
  NVIC_init();
  Motor_init();
  Steer_init();
  OLED_Init();
  Encoder_init();
  UART_init();
  pit_init();
  Camera_init();
}

