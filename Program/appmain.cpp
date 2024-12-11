#include "appmain.hpp"

void gpiod_init(void);

void app_main(void){
    gpiod_init();

    while (1)
    {
        asm volatile (
            "LDR R0, =0x40020C14   \n" // GPIOD_ODR address
            "LDR R1, =0xF000       \n" // Value to set pins 12-15
            "STR R1, [R0]          \n" // Write to GPIOD_ODR
        );
        HAL_Delay(1000);
        asm volatile (
            "LDR R0, =0x40020C14   \n" // GPIOD_ODR address
            "MOV R1, #0            \n" // Value to clear pins 12-15
            "STR R1, [R0]          \n" // Write to GPIOD_ODR
        );
        HAL_Delay(1000);
    }
    
    
}

void gpiod_init(void)
{
    // Enable clock for GPIOD
    asm volatile (
        "LDR R0, =0x40023830       \n" // RCC_AHB1ENR address
        "LDR R1, [R0]              \n" // Load current RCC_AHB1ENR value
        "ORR R1, R1, #(1 << 3)     \n" // Set bit 3 to enable GPIOD
        "STR R1, [R0]              \n" // Write back to RCC_AHB1ENR
    );

    // Configure GPIOD pins 12-15 as output
    asm volatile (
        "LDR R0, =0x40020C00       \n" // GPIOD_MODER address
        "LDR R1, [R0]              \n" // Load current GPIOD_MODER value
        "ORR R1, R1, #(0x55 << 24) \n" // Set pins 12-15 to output mode
        "STR R1, [R0]              \n" // Write back to GPIOD_MODER
    );

}