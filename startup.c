/** Basic startup code for ARM Cortex-Mx processor 
*/

#include <stdint.h>

/*** SRAM Address Definitions ***/
#define SRAM_START              0x20000000U
#define SRAM_SIZE               (256U * 1024U)            // STM32F429xx available SRAM size
#define SRAM_END                (SRAM_START + SRAM_SIZE)

/*** Stack Address Definitions ***/
#define STACK_START             SRAM_END

/*** Handler Function Definitions ***/
void reset_handler(void) {

}

/*** Vector Table Initialization ***/
// Moving the vector_table array to '.vector_table' section in the code memory.
uint32_t vector_table[] __attribute__((section(".vector_table"))) = {
    STACK_START,                    // Stack Pointer
    (uint32_t) &reset_handler       // Reset Handler
};