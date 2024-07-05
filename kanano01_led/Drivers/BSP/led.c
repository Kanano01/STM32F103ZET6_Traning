#include "./led.h"
//########################################
//1.enable clock
//2. config setting
//3.enable GPIO
//##########################################

char led_init(void)
{
	 __HAL_RCC_GPIOE_CLK_ENABLE();//enable gpioe
	 __HAL_RCC_GPIOB_CLK_ENABLE();
		GPIO_InitTypeDef GPIOPP;
	
			GPIOPP.Mode	=	 GPIO_MODE_OUTPUT_PP;
			GPIOPP.Pin	=	GPIO_PIN_5;
			GPIOPP.Pull	=	GPIO_PULLDOWN;
			GPIOPP.Speed	=	GPIO_SPEED_FREQ_HIGH;
		
		

	//void HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
	HAL_GPIO_Init(GPIOE,&GPIOPP);
	HAL_GPIO_Init(GPIOB,&GPIOPP);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
		return 1;
	
}
