#include "GPIO_init.h"



GPIO_InitTypeDef gpioa_init_struct;
GPIO_InitTypeDef gpioe_init_struct;
GPIO_InitTypeDef keyC_init_struct;
GPIO_InitTypeDef keyD_init_struct;

void GPIO_init(void)
{
//--------------------K60_LED-------------------
  gpioa_init_struct.GPIO_PTx = PTA;
  gpioa_init_struct.GPIO_Pins = GPIO_Pin17;
  gpioa_init_struct.GPIO_Dir = DIR_OUTPUT;
  gpioa_init_struct.GPIO_Output = OUTPUT_H;
  gpioa_init_struct.GPIO_PinControl = IRQC_DIS;
  LPLD_GPIO_Init(gpioa_init_struct);
//---------------------Razor_LED----------------
  gpioe_init_struct.GPIO_PTx = PTE;
  gpioe_init_struct.GPIO_Pins = GPIO_Pin10;
  gpioe_init_struct.GPIO_Dir = DIR_OUTPUT;
  gpioe_init_struct.GPIO_Output = OUTPUT_L;
  gpioe_init_struct.GPIO_PinControl = IRQC_DIS;
  LPLD_GPIO_Init(gpioe_init_struct);
//---------------------Razor_Key-------------------
  keyC_init_struct.GPIO_PTx = PTC;
  keyC_init_struct.GPIO_Pins = GPIO_Pin14 | GPIO_Pin15;
  keyC_init_struct.GPIO_Dir = DIR_INPUT;
  //keyC_init_struct.GPIO_Output = INPUT_PULL_UP;
  keyC_init_struct.GPIO_PinControl = INPUT_PULL_UP;
  LPLD_GPIO_Init(keyC_init_struct);

  keyD_init_struct.GPIO_PTx = PTD;
  keyD_init_struct.GPIO_Pins = GPIO_Pin10 | GPIO_Pin11 | GPIO_Pin12 | GPIO_Pin13;
  keyD_init_struct.GPIO_Dir = DIR_INPUT;
  //keyD_init_struct.GPIO_Output = INPUT_PULL_UP;
  keyD_init_struct.GPIO_PinControl = INPUT_PULL_UP;
  LPLD_GPIO_Init(keyD_init_struct);
}