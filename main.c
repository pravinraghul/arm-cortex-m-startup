#include <stdint.h>

// Base addresses for peripherals
#define RCC_BASE        0x40023800
#define GPIOG_BASE      0x40021800

// Register offsets
#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define GPIOG_MODER     (*(volatile uint32_t *)(GPIOG_BASE + 0x00))
#define GPIOG_ODR       (*(volatile uint32_t *)(GPIOG_BASE + 0x14))

// Bit positions
#define RCC_AHB1ENR_GPIOGEN (1 << 6)
#define GPIO_MODER_PIN13 (1 << 26)
#define GPIO_MODER_PIN14 (1 << 28)
#define GPIO_ODR_PIN13 (1 << 13)  // Green LED
#define GPIO_ODR_PIN14 (1 << 14)  // Red LED

void delay(volatile uint32_t count) {
    while (count--);
}

int main(void) {
    // Enable clock for GPIOG 
    RCC_AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
    GPIOG_MODER |= GPIO_MODER_PIN13; // Set PG13 as output
    GPIOG_MODER |= GPIO_MODER_PIN14; // Set PG14 as output

    while (1) {
        GPIOG_ODR |= GPIO_ODR_PIN13;
        GPIOG_ODR &= ~GPIO_ODR_PIN14;
        delay(500000);

        GPIOG_ODR &= ~GPIO_ODR_PIN13;
        GPIOG_ODR |= GPIO_ODR_PIN14;
        delay(500000);
    }

    // Code will never reach this point
    return 0;
}
