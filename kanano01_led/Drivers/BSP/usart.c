#include "usart.h"

UART_HandleTypeDef Uart1_handle = {0};//句柄
uint8_t g_rx_buffer[1];
uint8_t g_rx_flag	=	0; //接受标志
void uart_init( uint32_t baudrate)
{
	
	UART_InitTypeDef Uart1_Init = {0};
	Uart1_Init.BaudRate	=	baudrate;//波特率
	Uart1_Init.WordLength	=	UART_WORDLENGTH_8B;//8个数据字长
	Uart1_Init.StopBits	=	UART_STOPBITS_1;//1位停止位
	Uart1_Init.Parity	=	UART_PARITY_NONE; //奇校验位
	Uart1_Init.Mode =	UART_MODE_TX_RX;//收发模式
	Uart1_Init.HwFlowCtl =	UART_PARITY_NONE;//硬件流控
	
	

	Uart1_handle.Instance = USART1; //#define USART1              ((USART_TypeDef *)USART1_BASE)
	Uart1_handle.Init	=	Uart1_Init;
	
	
	
	
HAL_UART_Init(&Uart1_handle);//配置串口参数
	HAL_UART_Receive_IT(&Uart1_handle,(uint8_t*)g_rx_buffer,1);//开启接受中断函数
	//串口底层初始化
	//开启接受中断
	//中断优先级
	//中断服务函数
	//串口发送函数

}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)//msp回调函数
{
	GPIO_InitTypeDef gpio_init_struct	=	{0};
	if(huart->Instance	==	USART1)//如果基地址为串口1
{
__HAL_RCC_USART1_CLK_ENABLE();//开启串口时钟
__HAL_RCC_GPIOA_CLK_ENABLE();//开启GPIO的时钟 PA9 PA10
	gpio_init_struct.Mode	=	 GPIO_MODE_AF_PP;//推挽复用
			gpio_init_struct.Pin	=	GPIO_PIN_9;//tx
			gpio_init_struct.Pull	=	GPIO_PULLUP;//低电平是起始信号
			gpio_init_struct.Speed	=	GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA,&gpio_init_struct);
	gpio_init_struct.Pin	=	GPIO_PIN_10;//rx;
	gpio_init_struct.Mode	=	 GPIO_MODE_AF_INPUT;//复用输入
		HAL_GPIO_Init(GPIOA,&gpio_init_struct);
	
	
	/***********设置优先级*以及使能中断****************/
	HAL_NVIC_SetPriority(USART1_IRQn,2,1);
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
	HAL_NVIC_EnableIRQ(USART1_IRQn);//开启使能中断
	
	
}
	
	
}


void USART1_IRQHandler (void)
{
	HAL_UART_IRQHandler(&Uart1_handle);//清除中断标志
	HAL_UART_Receive_IT(&Uart1_handle,(uint8_t*)g_rx_buffer,1);
}	


/*******************串口数据接受完成回调函数*****************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
		g_rx_flag = 1;//查询此变量的值可知道接受是否完成
}





/******************************************************************************************/
/* ¼ÓÈëÒÔÏÂ´úÂë, Ö§³Öprintfº¯Êý, ¶ø²»ÐèÒªÑ¡Ôñuse MicroLIB */

#if 1

#if (__ARMCC_VERSION >= 6010050)            /* Ê¹ÓÃAC6±àÒëÆ÷Ê± */
__asm(".global __use_no_semihosting\n\t");  /* ÉùÃ÷²»Ê¹ÓÃ°ëÖ÷»úÄ£Ê½ */
__asm(".global __ARM_use_no_argv \n\t");    /* AC6ÏÂÐèÒªÉùÃ÷mainº¯ÊýÎªÎÞ²ÎÊý¸ñÊ½£¬·ñÔò²¿·ÖÀý³Ì¿ÉÄÜ³öÏÖ°ëÖ÷»úÄ£Ê½ */

#else
/* Ê¹ÓÃAC5±àÒëÆ÷Ê±, ÒªÔÚÕâÀï¶¨Òå__FILE ºÍ ²»Ê¹ÓÃ°ëÖ÷»úÄ£Ê½ */
#pragma import(__use_no_semihosting)

struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};

#endif

/* ²»Ê¹ÓÃ°ëÖ÷»úÄ£Ê½£¬ÖÁÉÙÐèÒªÖØ¶¨Òå_ttywrch\_sys_exit\_sys_command_stringº¯Êý,ÒÔÍ¬Ê±¼æÈÝAC6ºÍAC5Ä£Ê½ */
int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}

/* ¶¨Òå_sys_exit()ÒÔ±ÜÃâÊ¹ÓÃ°ëÖ÷»úÄ£Ê½ */
void _sys_exit(int x)
{
    x = x;
}

char *_sys_command_string(char *cmd, int len)
{
    return NULL;
}


/* FILE ÔÚ stdio.hÀïÃæ¶¨Òå. */
FILE __stdout;

/* MDKÏÂÐèÒªÖØ¶¨Òåfputcº¯Êý, printfº¯Êý×îÖÕ»áÍ¨¹ýµ÷ÓÃfputcÊä³ö×Ö·û´®µ½´®¿Ú */
int fputc(int ch, FILE *f)
{
    while ((USART1->SR & 0X40) == 0);     /* µÈ´ýÉÏÒ»¸ö×Ö·û·¢ËÍÍê³É */

    USART1->DR = (uint8_t)ch;             /* ½«Òª·¢ËÍµÄ×Ö·û ch Ð´Èëµ½DR¼Ä´æÆ÷ */
    return ch;
}
#endif
/******************************************************************************************/


