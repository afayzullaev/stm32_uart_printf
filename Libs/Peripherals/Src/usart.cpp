#include "usart.hpp"


UART_HandleTypeDef huart2;


void UART2_Init(uint32_t baudrate)
{
    // Enable USART2 clock
    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct;

    // Configure GPIO Pins PA2 (TX) and PA3 (RX)
    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;        // Alternate function push-pull
    GPIO_InitStruct.Pull = GPIO_NOPULL;            // No pull-up or pull-down
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;  // High speed
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;   // Alternate function USART2
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // UART Configuration
    huart2.Instance = USART2;
    huart2.Init.BaudRate = baudrate;           // Set baud rate
    huart2.Init.WordLength = UART_WORDLENGTH_8B;  // 8 data bits
    huart2.Init.StopBits = UART_STOPBITS_1;       // 1 stop bit
    huart2.Init.Parity = UART_PARITY_NONE;        // No parity
    huart2.Init.Mode = UART_MODE_TX_RX;           // Enable TX and RX
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;  // No hardware flow control
    huart2.Init.OverSampling = UART_OVERSAMPLING_16; // Oversampling by 16

    // Initialize UART
    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        // Initialization Error
        Error_Handler();
    }
}


int __io_putchar(int ch) {
 uint8_t c[1];
 c[0] = ch & 0x00FF;
 HAL_UART_Transmit(&huart2, &c[0], 1, 100);
 return ch;
}


int _write(int file,char *ptr, int len) {
 int DataIdx;
 for(DataIdx= 0; DataIdx< len; DataIdx++) {
    __io_putchar(*ptr++);
 }
 return len;
}

