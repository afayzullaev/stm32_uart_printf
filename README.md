# GPIO Initialization Tutorial

This repository contains a simple example demonstrating how to initialize GPIO pins and toggle them using low-level assembly instructions in an embedded system. The code is specifically designed for microcontrollers based on the ARM Cortex-M architecture (e.g., STM32).

## Project Structure

The repository is organized as follows:

```
STM32_ASSEMBLY/
├── .vscode/               # Configuration files for Visual Studio Code
├── build/                 # Build output directory
├── cmake/                 # CMake configuration files
│   ├── stm32cubemx/       # CubeMX-generated CMake scripts
│   └── gcc-arm-none-eabi.cmake  # CMake toolchain file for ARM GCC
├── Core/                  # Core application files
│   ├── Inc/               # Header files
│   │   ├── main.h         # Main application header
│   │   ├── stm32f4xx_hal_conf.h # HAL configuration header
│   │   └── stm32f4xx_it.h # Interrupt handlers header
│   └── Src/               # Source files
│       ├── main.c         # Main application source
│       ├── stm32f4xx_hal_msp.c # HAL MSP initialization
│       ├── stm32f4xx_it.c # Interrupt handlers source
│       ├── syscalls.c     # System call implementations
│       ├── sysmem.c       # Memory management source
│       └── system_stm32f4xx.c # System initialization source
├── Drivers/               # HAL and peripheral drivers
│   ├── Inc/               # Driver headers
│   └── Src/               # Driver sources
├── Program/               # Application-specific code
│   ├── appmain.cpp        # Application entry point (C++)
│   └── appmain.hpp        # Application-specific header (C++)
├── README.md              # Project documentation
├── startup_stm32f407xx.s  # Startup assembly code for STM32F4
├── CMakeLists.txt         # CMake build configuration
└── compile_commands.json  # Compilation database for code analysis
```

## Features

- Enables GPIO clock.
- Configures GPIO pins 12 to 15 as outputs.
- Toggles GPIO pins 12 to 15 on and off with a delay.

## Code Overview

### `gpiod_init(void)`
This function initializes the GPIO port by enabling its clock and configuring pins 12 to 15 as output pins.

```c
void gpiod_init(void) {
    // Enable clock for GPIOD
    asm volatile (
        "LDR R0, =0x40023830 \n" // RCC_AHB1ENR address
        "LDR R1, [R0] \n"      // Load current RCC_AHB1ENR value
        "ORR R1, R1, #8 \n"    // Set bit 3 to enable GPIOD
        "STR R1, [R0] \n"      // Write back to RCC_AHB1ENR
    );

    // Configure GPIOD pins 12-15 as output
    asm volatile (
        "LDR R0, =0x40020C00 \n" // GPIOD_MODER address
        "LDR R1, [R0] \n"      // Load current GPIOD_MODER value
        "ORR R1, R1, #(0x55 << 24) \n" // Set pins 12-15 to output mode
        "STR R1, [R0] \n"      // Write back to GPIOD_MODER
    );
}
```

### `app_main(void)`
The main function initializes the GPIO port and enters an infinite loop to toggle pins 12 to 15 with a delay.

```c
void app_main(void) {
    gpiod_init();

    while (1) {
        // Turn on pins 12-15
        asm volatile (
            "LDR R0, =0x40020C14 \n" // GPIOD_ODR address
            "LDR R1, =0xF000 \n"     // Value to set pins 12-15
            "STR R1, [R0] \n"        // Write to GPIOD_ODR
        );
        HAL_Delay(1000);

        // Turn off pins 12-15
        asm volatile (
            "LDR R0, =0x40020C14 \n" // GPIOD_ODR address
            "MOV R1, #0 \n"         // Value to clear pins 12-15
            "STR R1, [R0] \n"        // Write to GPIOD_ODR
        );
        HAL_Delay(1000);
    }
}
```

## How It Works

1. **Enable GPIO Clock:**
   The clock for the GPIOD peripheral is enabled by setting the corresponding bit in the `RCC_AHB1ENR` register.

2. **Configure GPIO Pins:**
   Pins 12 to 15 of GPIOD are configured as outputs by modifying the `GPIOD_MODER` register.

3. **Toggle GPIO Pins:**
   The `GPIOD_ODR` register is used to toggle the output state of pins 12 to 15. The `HAL_Delay` function introduces a 1-second delay between state changes.

## Prerequisites

- ARM Cortex-M microcontroller (e.g., STM32).
- Toolchain for compiling C code (e.g., GCC for ARM).
- Debugger/Programmer for flashing the code to the microcontroller.

## Usage

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/gpio-tutorial.git
   cd gpio-tutorial
   ```

2. Build the code using your preferred build system.

3. Flash the binary to your microcontroller using your programmer.

4. Observe the LEDs connected to GPIO pins 12 to 15 toggling on and off with a delay.

## Notes

- The base addresses used in the code (e.g., `0x40023830`, `0x40020C00`, etc.) are specific to STM32 microcontrollers. Modify them as needed for your target device.
- Ensure that the pins 12 to 15 of the GPIOD port are connected to LEDs or other output devices.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your changes.
