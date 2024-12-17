#ifndef _USART_HPP_
#define _USART_HPP_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "stm32f4xx_hal_uart.h"
#include <stdio.h>
#include "string.h"


void UART2_Init(uint32_t baudrate);
int __io_putchar(int ch);
int _write(int file,char *ptr, int len);
void print_something();
#ifdef __cplusplus
}
#endif

#endif /* PROGRAM_INC_CPPMAIN_H_ */