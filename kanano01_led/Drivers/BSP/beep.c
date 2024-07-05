#include "beep.h"

void beep_init(void)
{
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GPIO_InitTypeDef GPIOBEEP; 
		GPIOBEEP.Mode =	GPIO_MODE_OUTPUT_PP;
		GPIOBEEP.Pin	=	GPIO_PIN_8;
		GPIOBEEP.Pull =	GPIO_PULLDOWN;
		GPIOBEEP.Speed	=	GPIO_SPEED_FREQ_MEDIUM;
	
		HAL_GPIO_Init(GPIOB,&GPIOBEEP);
		
}

void beep_call(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET);
} 

void beep_shutdown(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET);
} 
