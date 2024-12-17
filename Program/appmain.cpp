#include "appmain.hpp"
#include "usart.hpp"


void app_main(void){
    
    UART2_Init(115200);
    HAL_Delay(200);
    printf("UART printf example on STM32F407\r\n");
    while (1)
    {
        printf("Hello, world! Counter: %ld\r\n", HAL_GetTick());
        HAL_Delay(1000);
    }
}

