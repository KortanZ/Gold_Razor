#include "common.h"

void Keypress_GPIO_init(void);
void keybordDelay(void);

void main(void)
{
	//uint8 Model_Flag;
	DisableInterrupts;
	Keypress_GPIO_init();
	
	//GPIO_init();
	OLED_Init();
	OLED_Clear();
	
	
	Camera_init();

	EnableInterrupts;
	while (1)
	{
	  	
		if (PTD12_I == 0)						//舵机Kd增
		{
			keybordDelay();
			if (PTD12_I == 0)
			{
				
			}
		}
		if (PTD13_I == 0)						//舵机Kd减
		{
			keybordDelay();
			if (PTD13_I == 0)
			{
			  	
			}
		}

		if (PTD10_I == 0)						//舵机Kd增
		{
			keybordDelay();
			if (PTD10_I == 0)
			{
				
			}
		}
		if (PTD11_I == 0)						//舵机Kd减
		{
			keybordDelay();
			if (PTD11_I == 0)
			{
			  	
			}
		}

		if (PTC14_I == 0)						//速度增
		{
			keybordDelay();
			if (PTC14_I == 0)
			{
				PWM_Expect += 50;
			}
		}
		if (PTC15_I == 0)						//速度减
		{
			keybordDelay();
			if (PTC15_I == 0)
			{
			  	PWM_Expect -= 50;
			}
		}
	  	
	}
}

void Keypress_GPIO_init(void)
{
  	  GPIO_InitTypeDef gpio_init_struct;
      gpio_init_struct.GPIO_PTx = PTD;
      gpio_init_struct.GPIO_Pins = GPIO_Pin10 | GPIO_Pin11 | GPIO_Pin12 | GPIO_Pin13;
      gpio_init_struct.GPIO_Dir = DIR_INPUT;
      gpio_init_struct.GPIO_PinControl = IRQC_DIS | INPUT_PULL_UP;
      LPLD_GPIO_Init(gpio_init_struct);

      gpio_init_struct.GPIO_PTx = PTC;
      gpio_init_struct.GPIO_Pins = GPIO_Pin14 | GPIO_Pin15;
      gpio_init_struct.GPIO_Dir = DIR_INPUT;
      gpio_init_struct.GPIO_PinControl = IRQC_DIS | INPUT_PULL_UP;
      LPLD_GPIO_Init(gpio_init_struct);
}

void keybordDelay(void)
{
	uint16 i, n;
	for (i = 0; i<15000; i++)
	{
		for (n = 0; n<50; n++)
		{
			asm("nop");
		}
	}
}