
# STM32F407 UART `printf` Example

This repository demonstrates how to implement **`printf` functionality** over UART on an **STM32F407** microcontroller using bare-metal programming. The project uses **HAL (Hardware Abstraction Layer)** and is built with **CMake** for organization and flexibility.

---

## 📁 **Project Structure**

```
.
├── CMakeLists.txt                # CMake build system configuration
├── Drivers/                      # HAL driver files and startup scripts
├── Libs/
│   └── Peripherals/
│       ├── Inc/                 # Header files for peripherals
│       │   └── usart.hpp
│       └── Src/                 # Source files for peripherals
│           └── usart.cpp        # UART initialization and printf redirection
├── Program/
│   ├── appmain.cpp              # Main application code
│   └── appmain.hpp              # Header file for main application
├── startup_stm32f407xx.s        # Startup file for STM32F407
├── stm32_dma.ioc                # STM32CubeMX project file
├── STM32F407VGTx_FLASH.ld       # Linker script
└── README.md                    # Project documentation (this file)
```

---

## 🚀 **Features**
- Redirects **`printf`** to UART for serial communication.
- Configures UART2 (TX on PA2) with a baud rate of **115200**.
- Integrates a clean project structure using **CMake**.
- Supports **float values in `printf`** using `-u _printf_float`.
- Demonstrates the use of HAL library for STM32 bare-metal programming.

---

## 🛠️ **Tools and Dependencies**
- **STM32CubeMX**: Peripheral configuration.
- **CMake**: Build system.
- **GNU ARM Toolchain**: Cross-compilation for ARM Cortex-M.
- **VSCode**: IDE for code editing and debugging.
- **Serial Monitor**: For viewing UART output (e.g., PuTTY, Tera Term).

---

## 🔧 **How It Works**

### 1. **UART Initialization**
The UART peripheral is initialized with the following configuration:
- **Baud Rate**: 115200  
- **Word Length**: 8 bits  
- **Stop Bits**: 1  
- **Parity**: None  

**Code Snippet** (usart.cpp):
```c
void UART2_Init(uint32_t baud_rate) {
    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    huart2.Instance = USART2;
    huart2.Init.BaudRate = baud_rate;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&huart2);
}
```

---

### 2. **`printf` Redirection**
The `printf` function is redirected to UART using `_write` and `__io_putchar`:

**Code Snippet** (usart.cpp):
```c
int __io_putchar(int ch) {
    uint8_t c[1];
    c[0] = ch & 0x00FF;
    HAL_UART_Transmit(&huart2, &c[0], 1, 100);
    return ch;
}

int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        __io_putchar(*ptr++);
    }
    return len;
}
```

---

### 3. **Main Program**
The main program demonstrates UART transmission using `printf`:

**Code Snippet** (appmain.cpp):
```c
void app_main(void) {
    UART2_Init(115200);
    HAL_Delay(200);  // Ensure UART is ready

    printf("UART printf example on STM32F407\r\n");

    while (1) {
        printf("Hello, world! Counter: %ld\r\n", HAL_GetTick());
        HAL_Delay(1000);
    }
}
```

---

## 🛠️ **Building the Project**
To build the project using CMake:
```bash
# Create a build directory
mkdir build
cd build

# Configure the project
cmake ..

# Build the project
cmake --build .
```

---

## 🖥️ **Running and Testing**
1. Flash the `.elf` file to the STM32F407 board using a tool like **ST-Link**.
2. Connect a USB-to-UART adapter to the **PA2 (TX)** pin of the microcontroller.
3. Open a serial monitor (e.g., Tera Term) and set the baud rate to **115200**.
4. Verify the UART output.

---

## ⚙️ **Linker Configuration**
To enable `printf` for floating-point values, the following linker options are set in **CMakeLists.txt**:
```cmake
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    --specs=nosys.specs  # Minimal I/O system
    -u _printf_float     # Enable float support for printf
)
```

---

## 📜 **License**
This project is open-source and licensed under the [MIT License](LICENSE).

---

## 📧 **Contact**
For questions or suggestions, feel free to reach out:
- **GitHub**: [Your GitHub Profile Link]
- **Email**: fayzullaev776@gmail.com
