#include <stm32f4xx.h>

void delay(volatile uint32_t count) {
    while (count--);
}

int main(void) {
    // Enable clock for GPIOG
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN_Msk;
    GPIOG->MODER |= (0x01 << GPIO_MODER_MODER13_Pos); // Set PG13 as output
    GPIOG->MODER |= (0x01 << GPIO_MODER_MODER14_Pos); // Set PG14 as output

    while (1) {
        GPIOG->ODR |= GPIO_ODR_OD13_Msk;
        GPIOG->ODR &= ~GPIO_ODR_OD14_Msk;
        delay(500000);

        GPIOG->ODR &= ~GPIO_ODR_OD13_Msk;
        GPIOG->ODR |= GPIO_ODR_OD14_Msk;
        delay(500000);
    }

    return 0;
}
