#include "stm32f1xx_hal.h"
void uart_init(uint32_t baudrate);
extern uint8_t g_rx_buffer[1];
extern uint8_t g_rx_flag	; //接受标志
extern UART_HandleTypeDef Uart1_handle;
#include "stdio.h"
