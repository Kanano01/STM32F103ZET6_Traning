#include "nvic.h"


/**
  * @brief 
  * @note 
  * @note 
  * @param
  * @retval 
  */
void nvic_init()
{
 
	__HAL_RCC_GPIOE_CLK_ENABLE();
	//void HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)

//	HAL_NVIC_SetPriorityGrouping  //中断分组 几组pre中断优先几组响应sub优先
	HAL_NVIC_SetPriority(EXTI3_IRQn,2,0);//中断优先级
	HAL_NVIC_EnableIRQ(EXTI3_IRQn);//使能中断 key1 pe3
}

void exti_init()
{
		GPIO_InitTypeDef GPIOPP;
	
			GPIOPP.Mode	=	 GPIO_MODE_IT_FALLING;
			GPIOPP.Pin	=	GPIO_PIN_3;
			GPIOPP.Pull	=	GPIO_PULLUP;
			GPIOPP.Speed	=	GPIO_SPEED_FREQ_HIGH;
		
		

	//void HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
	HAL_GPIO_Init(GPIOE,&GPIOPP);
}

/**
  * @brief 
  * @note   //DCD     EXTI0_IRQHandler           ; EXTI Line 0
  * @note  要清除中断标志
  * @param
  * @retval 
  */
  
void  EXTI3_IRQHandler(void)
{
	
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
	
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)//公共回调函数
{
		
	//HAL_Delay(20);//消抖
	if(GPIO_Pin == GPIO_PIN_3) //是exti3造成的回调函数
	{
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_3)==0)// 按键按下了
		{
			HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_5);
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_8);
		}
	}

}
