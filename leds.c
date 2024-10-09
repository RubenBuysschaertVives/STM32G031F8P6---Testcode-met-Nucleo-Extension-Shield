#include "stm32g031xx.h"
#include "leds.h"
#include "stdbool.h"

void InitLeds(void)
{
	// Clock voor GPIOA inschakelen.
	RCC->IOPENR = RCC->IOPENR | RCC_IOPENR_GPIOAEN;
	
	// Clock voor GPIOB inschakelen.
	RCC->IOPENR = RCC->IOPENR | RCC_IOPENR_GPIOBEN;
	
	// Clock voor GPIOC inschakelen.
	RCC->IOPENR = RCC->IOPENR | RCC_IOPENR_GPIOCEN;	
	
	// On board LED op output zetten.
	GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE7) | GPIO_MODER_MODE7_0;
	
	// LED1 tot LED4 op output zetten (Nucleo Extension Shield).
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE5) | GPIO_MODER_MODE5_0;
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE6) | GPIO_MODER_MODE6_0;
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE7) | GPIO_MODER_MODE7_0;
	GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE15) | GPIO_MODER_MODE15_0;
}

void SetOnBoardLed(bool state)
{
	if(state == true)
		GPIOB->ODR = GPIOB->ODR | GPIO_ODR_OD7;		// inschakelen
	else
		GPIOB->ODR = GPIOB->ODR & ~GPIO_ODR_OD7;	// uitschakelen
}

// Functie om de data van één byte op de 4 LED's van het Nucleo Extension Shield te plaatsen.
void ByteToLeds(unsigned char data)
{
	// Enkel de 4 LSbits overhouden.
	data = data & 0x0F;
	
	if(data & 0x01)
		GPIOA->ODR = GPIOA->ODR | GPIO_ODR_OD5;			// inschakelen
	else
		GPIOA->ODR = GPIOA->ODR & ~GPIO_ODR_OD5;		// uitschakelen

	if(data & 0x02)
		GPIOA->ODR = GPIOA->ODR | GPIO_ODR_OD6;			// inschakelen
	else
		GPIOA->ODR = GPIOA->ODR & ~GPIO_ODR_OD6;		// uitschakelen

	if(data & 0x04)
		GPIOA->ODR = GPIOA->ODR | GPIO_ODR_OD7;			// inschakelen
	else
		GPIOA->ODR = GPIOA->ODR & ~GPIO_ODR_OD7;		// uitschakelen

	if(data & 0x08)
		GPIOC->ODR = GPIOC->ODR | GPIO_ODR_OD15;		// inschakelen
	else
		GPIOC->ODR = GPIOC->ODR & ~GPIO_ODR_OD15;		// uitschakelen
}
