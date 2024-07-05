#include "key.h"
void key_init(void)
{
	__HAL_RCC_GPIOE_CLK_ENABLE();//enable gpioe
	 
		GPIO_InitTypeDef GPIOPP;
	
			GPIOPP.Mode	=	 GPIO_MODE_INPUT;
			GPIOPP.Pin	=	GPIO_PIN_4;
			GPIOPP.Pull	=	GPIO_PULLUP;
			GPIOPP.Speed	=	GPIO_SPEED_FREQ_HIGH;
		
		

	//void HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
	HAL_GPIO_Init(GPIOE,&GPIOPP);

}
char key_scan(void)
{
	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4)==0)
		{
				HAL_Delay(10);
			if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4)==0)
			{
					
				while(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4)==0);
				return 1 ;
			}
		}
		return 0;
}
