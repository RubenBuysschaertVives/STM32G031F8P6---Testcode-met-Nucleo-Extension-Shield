#include "stm32g031xx.h"
#include "stdbool.h"
#include "buttons.h"

// Knoppen als input initialiseren.
void InitButtons(void)
{
	// Clock voor GPIOA inschakelen.
	RCC->IOPENR = RCC->IOPENR | RCC_IOPENR_GPIOAEN;
	
	// Clock voor GPIOB inschakelen.
	RCC->IOPENR = RCC->IOPENR | RCC_IOPENR_GPIOBEN;
	
	// On board knop.
	GPIOB->MODER = GPIOB->MODER & ~GPIO_MODER_MODE9;
	
	// Knoppen van het Nucleo Extension Shield.
	GPIOA->MODER = GPIOA->MODER & ~GPIO_MODER_MODE1;
	GPIOA->MODER = GPIOA->MODER & ~GPIO_MODER_MODE2;
	GPIOA->MODER = GPIOA->MODER & ~GPIO_MODER_MODE3;
	GPIOA->MODER = GPIOA->MODER & ~GPIO_MODER_MODE4;
}

bool SW1Active(void)
{
	// SW1 actief?
	if((GPIOA->IDR & GPIO_IDR_ID1) != GPIO_IDR_ID1)
			return true;
	else
			return false;
}		
	
bool SW2Active(void)
{
	// SW2 actief?
	if((GPIOA->IDR & GPIO_IDR_ID2) != GPIO_IDR_ID2)
			return true;
	else
			return false;
}

bool SW3Active(void)
{
	// SW3 actief?
	if((GPIOA->IDR & GPIO_IDR_ID3) != GPIO_IDR_ID3)
			return true;
	else
			return false;
}

bool SW4Active(void)
{
	// SW4 actief?
	if((GPIOA->IDR & GPIO_IDR_ID4) != GPIO_IDR_ID4)
			return true;
	else
			return false;
}

bool UserButtonActive(void)
{
	// User button actief?
	if((GPIOB->IDR & GPIO_IDR_ID9) != GPIO_IDR_ID9)
			return true;
	else
			return false;
}
