// Basiscode voor het testen het STM32G031-bord (ontwerp Hans Naert) in combinatie met een Nucleo Extension Shield V2 (ontwerp Ruben Buysschaert).
//
// OPM:
//	- via 'Options for Target ...' zet je de compiler op C99 (en eventueel op AC5-like warnings).
// 
// Versie: 20221116

// Includes.
#include "stm32g031xx.h"
#include "stdio.h"
#include "stdbool.h"
#include "leds.h"
#include "buttons.h"

// Functie prototypes.
void SystemClock_Config(void);
void InitIo(void);
void WaitForMs(uint32_t timespan);

// Variabelen aanmaken. 
// OPM: het keyword 'static', zorgt ervoor dat de variabele enkel binnen dit bestand gebruikt kan worden.
static uint8_t count = 0;
static volatile uint32_t ticks = 0;

// Entry point.
int main(void)
{
	// Initialisaties.
	SystemClock_Config();
	InitIo();
	InitButtons();
	InitLeds();

	// Oneindige lus starten.
	while (1)
	{		
		// On board LED en SW testen.
		if(UserButtonActive())
			SetOnBoardLed(true);
		else
		{
			SetOnBoardLed(false);
			WaitForMs(50);
			SetOnBoardLed(true);
		}
		
		// Knoppen en LED's testen van het Nucleo Extension Shield.
		if(SW1Active() || SW2Active() || SW3Active() || SW4Active())
			ByteToLeds(0x0F);
		else
		{
			count++;
			ByteToLeds(count);
		}
		
		WaitForMs(50);
	}
}

// Functie om extra IO's te initialiseren.
void InitIo(void)
{

}

// Handler die iedere 1ms afloopt. Ingesteld met SystemCoreClockUpdate() en SysTick_Config().
void SysTick_Handler(void)
{
	ticks++;
}

// Wachtfunctie via de SysTick.
void WaitForMs(uint32_t timespan)
{
	uint32_t startTime = ticks;
	
	while(ticks < startTime + timespan);
}

// Klokken instellen. Deze functie niet wijzigen, tenzij je goed weet wat je doet.
void SystemClock_Config(void)
{
	RCC->CR  |= RCC_CR_HSION;																// Internal high speed oscillator enable (16MHz).
	while((RCC->CR & RCC_CR_HSIRDY) == 0);									// Wacht tot HSI zeker ingeschakeld is.
	
	RCC->CFGR &= ~RCC_CFGR_SW;															// System clock op HSI zetten (SWS is status geupdatet door hardware).
	while((RCC->CFGR & RCC_CFGR_SWS) != 0);									// Wachten tot effectief HSI in actie is getreden.
	
	SystemCoreClockUpdate();																// Nieuwe waarde van de core frequentie opslaan in SystemCoreClock variabele.
	SysTick_Config(16000);																	// Interrupt genereren. Zie core_cm0.h, om na ieder 1ms een interrupt
																													// te hebben op SysTick_Handler().
}
