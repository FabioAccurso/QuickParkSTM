#ifndef USART_H
#define USART_H

#include "stm32f3xx_hal.h"  // Cambia con il tuo target, es. stm32f4xx_hal.h

extern UART_HandleTypeDef huart3;

void MX_USART3_UART_Init(void);

#endif

