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

/*** Vector Table Initialization ***/
// Moving the vector_table array to '.vector_table' section in the code memory.
uint32_t vector_table[] __attribute__((section(".vector_table"))) = {
    // Basic exceptions required to boot Cortex-M processor
    (uint32_t) STACK_START,         // Stack Pointer
    (uint32_t) reset_handler,       // Reset Handler
};

/*** Handler Function Definitions ***/
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