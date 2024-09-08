/** Basic startup code for ARM Cortex-Mx processor 
*/

#include <stdint.h>

/*** SRAM Address Definitions ***/
#define SRAM_START              0x20000000U
#define SRAM_SIZE               (192U * 1024U)            // STM32F429xx available SRAM size
#define SRAM_END                ((SRAM_START) + (SRAM_SIZE))

/*** Stack Address Definitions ***/
#define STACK_START             SRAM_END

/*** Linker Symbols ***/
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

int main(void);

/*** Handler Function Prototype ***/
void Reset_Handler(void);

/*** Vector Table Initialization ***/
// Moving the vector_table array to '.vector_table' section in the code memory.
uint32_t vector_table[] __attribute__((section(".isr_vector"))) = {
    (uint32_t) STACK_START,          // Stack Pointer
    (uint32_t) Reset_Handler,       // Reset Handler
};

/*** Handler Function Definitions ***/
void Reset_Handler(void) {
    uint8_t *dest = (uint8_t*)&_sdata;
    uint8_t *src = (uint8_t*)&_etext;
    uint32_t size;
    
    // copy .data section to SRAM
    size = (uint32_t)&_edata - (uint32_t)&_sdata;
    for (uint32_t i = 0; i < size; i++) {
        *dest++ = *src++;
    }

    // Init the .bss section to zero in SRAM
    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    dest = (uint8_t*) &_sbss;
    for (uint32_t i = 0; i < size; i++) {
        *dest++=0;
    }
    
    // call the main
    main();
}