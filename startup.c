/** Basic startup code for ARM Cortex-Mx processor 
*/

#include <stdint.h>

/*** SRAM Address Definitions ***/
#define SRAM_START              0x20000000U
#define SRAM_SIZE               (192U * 1024U) // STM32F429xx available SRAM size
#define SRAM_END                ((SRAM_START) + (SRAM_SIZE))

/*** Stack Address Definitions ***/
// Cortex-M is a full descending stack, meaning stack memory starts 
// from the last address of the memory.
// Ref: https://developer.arm.com/documentation/dui0552/a/the-cortex-m3-processor/programmers-model/stacks
#define STACK_START             SRAM_END

/*** Linker Symbols ***/
extern uint32_t end_of_text;
extern uint32_t start_of_data;
extern uint32_t end_of_data;
extern uint32_t start_of_bss;
extern uint32_t end_of_bss;

int main(void);

/*** Handler Function Prototype ***/
void reset_handler(void);
void hardfault_handler(void) __attribute__ ((weak, alias("default_handler")));

/*** External Interrupts Prototype ***/
void exti0_irq_handler(void) __attribute__ ((weak, alias("default_handler")));
void spi4_irq_handler(void) __attribute__ ((weak, alias("default_handler")));
void uart5_irq_handler(void) __attribute__ ((weak, alias("default_handler")));

/*** Vector Table Initialization ***/
// Moving the vector_table array to '.vector_table' section in the code memory.
uint32_t vector_table[] __attribute__((section(".vector_table"))) = {
    // Basic exceptions required to boot Cortex-M processor
    (uint32_t) STACK_START,         // Stack Pointer
    (uint32_t) reset_handler,       // Reset Handler

    /* System Exceptions */
    (uint32_t) 0,                   // NMI Handler
    (uint32_t) hardfault_handler,   // Hard Fault Handler
    (uint32_t) 0,                   // Memory Management Handler
    (uint32_t) 0,                   // Bus Fault Handler
    (uint32_t) 0,                   // Usage Fault Handler
    (uint32_t) 0,                   // Reserved
    (uint32_t) 0,                   // Reserved
    (uint32_t) 0,                   // Reserved
    (uint32_t) 0,                   // Reserved
    (uint32_t) 0,                   // SVC Handler
    (uint32_t) 0,                   // Debug Monitor Handler
    (uint32_t) 0,                   // Reserved
    (uint32_t) 0,                   // PendSV Handler
    (uint32_t) 0,                   // SysTick Handler
   
    /* External Interrupts specific to STM32F429xx */
    (uint32_t) 0,                   // Window WatchDog
    (uint32_t) 0,                   // PVD through EXTI Line detection
    (uint32_t) 0,                   // Tamper and TimeStamps through the EXTI line
    (uint32_t) 0,                   // RTC Wakeup through the EXTI line
    (uint32_t) 0,                   // FLASH
    (uint32_t) 0,                   // RCC
    (uint32_t) exti0_irq_handler,   // EXTI Line0
    (uint32_t) 0,                   // EXTI Line1
    (uint32_t) 0,                   // EXTI Line2
    (uint32_t) 0,                   // EXTI Line3
    (uint32_t) 0,                   // EXTI Line4
    (uint32_t) 0,                   // DMA1 Stream 0
    (uint32_t) 0,                   // DMA1 Stream 1
    (uint32_t) 0,                   // DMA1 Stream 2
    (uint32_t) 0,                   // DMA1 Stream 3
    (uint32_t) 0,                   // DMA1 Stream 4
    (uint32_t) 0,                   // DMA1 Stream 5
    (uint32_t) 0,                   // DMA1 Stream 6
    (uint32_t) 0,                   // ADC1, ADC2 and ADC3s
    (uint32_t) 0,                   // CAN1 TX
    (uint32_t) 0,                   // CAN1 RX0
    (uint32_t) 0,                   // CAN1 RX1
    (uint32_t) 0,                   // CAN1 SCE
    (uint32_t) 0,                   // External Line[9:5]s
    (uint32_t) 0,                   // TIM1 Break and TIM9
    (uint32_t) 0,                   // TIM1 Update and TIM10
    (uint32_t) 0,                   // TIM1 Trigger and Commutation and TIM11
    (uint32_t) 0,                   // TIM1 Capture Compare
    (uint32_t) 0,                   // TIM2
    (uint32_t) 0,                   // TIM3
    (uint32_t) 0,                   // TIM4
    (uint32_t) 0,                   // I2C1 Event
    (uint32_t) 0,                   // I2C1 Error
    (uint32_t) 0,                   // I2C2 Event
    (uint32_t) 0,                   // I2C2 Error
    (uint32_t) 0,                   // SPI1
    (uint32_t) 0,                   // SPI2
    (uint32_t) 0,                   // USART1
    (uint32_t) 0,                   // USART2
    (uint32_t) 0,                   // USART3
    (uint32_t) 0,                   // External Line[15:10]s
    (uint32_t) 0,                   // RTC Alarm (A and B) through EXTI Line
    (uint32_t) 0,                   // USB OTG FS Wakeup through EXTI line
    (uint32_t) 0,                   // TIM8 Break and TIM12
    (uint32_t) 0,                   // TIM8 Update and TIM13
    (uint32_t) 0,                   // TIM8 Trigger and Commutation and TIM14
    (uint32_t) 0,                   // TIM8 Capture Compare
    (uint32_t) 0,                   // DMA1 Stream7
    (uint32_t) 0,                   // FMC
    (uint32_t) 0,                   // SDIO
    (uint32_t) 0,                   // TIM5
    (uint32_t) 0,                   // SPI3
    (uint32_t) 0,                   // UART4
    (uint32_t) uart5_irq_handler,   // UART5
    (uint32_t) 0,                   // TIM6 and DAC1&2 underrun errors
    (uint32_t) 0,                   // TIM7
    (uint32_t) 0,                   // DMA2 Stream 0
    (uint32_t) 0,                   // DMA2 Stream 1
    (uint32_t) 0,                   // DMA2 Stream 2
    (uint32_t) 0,                   // DMA2 Stream 3
    (uint32_t) 0,                   // DMA2 Stream 4
    (uint32_t) 0,                   // Ethernet
    (uint32_t) 0,                   // Ethernet Wakeup through EXTI line
    (uint32_t) 0,                   // CAN2 TX
    (uint32_t) 0,                   // CAN2 RX0
    (uint32_t) 0,                   // CAN2 RX1
    (uint32_t) 0,                   // CAN2 SCE
    (uint32_t) 0,                   // USB OTG FS
    (uint32_t) 0,                   // DMA2 Stream 5
    (uint32_t) 0,                   // DMA2 Stream 6
    (uint32_t) 0,                   // DMA2 Stream 7
    (uint32_t) 0,                   // USART6
    (uint32_t) 0,                   // I2C3 event
    (uint32_t) 0,                   // I2C3 error
    (uint32_t) 0,                   // USB OTG HS End Point 1 Out
    (uint32_t) 0,                   // USB OTG HS End Point 1 In
    (uint32_t) 0,                   // USB OTG HS Wakeup through EXTI
    (uint32_t) 0,                   // USB OTG HS
    (uint32_t) 0,                   // DCMI
    (uint32_t) 0,                   // Reserved
    (uint32_t) 0,                   // Hash and Rng
    (uint32_t) 0,                   // FPU
    (uint32_t) 0,                   // UART7
    (uint32_t) 0,                   // UART8
    (uint32_t) spi4_irq_handler,    // SPI4
    (uint32_t) 0,                   // SPI5
    (uint32_t) 0,                   // SPI6
    (uint32_t) 0,                   // SAI1
    (uint32_t) 0,                   // LTDC_IRQHandler
    (uint32_t) 0,                   // LTDC_ER_IRQHandler
    (uint32_t) 0,                   // DMA2D
};

/*** Handler Function Definitions ***/

void default_handler(void) {
    while(1);
}

void reset_handler(void) {
    uint8_t *dest = (uint8_t*)&start_of_data;
    uint8_t *src = (uint8_t*)&end_of_text;
    uint32_t size;

    // copy .data section to SRAM
    size = (uint32_t)&end_of_data - (uint32_t)&start_of_data;
    for (uint32_t i = 0; i < size; i++) {
        *dest++ = *src++;
    }

    // initialize the .bss section to zero in SRAM
    size = (uint32_t)&end_of_bss - (uint32_t)&start_of_bss;
    dest = (uint8_t*) &start_of_bss;
    for (uint32_t i = 0; i < size; i++) {
        *dest++=0;
    }

    // call the main
    main();
}