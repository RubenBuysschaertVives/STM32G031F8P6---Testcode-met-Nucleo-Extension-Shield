#include "stm32g031xx.h"
#include "stdbool.h"

#if !defined(LEDS_DEFINED)
	#define LEDS_DEFINED
	
	void InitLeds(void);
	void SetOnBoardLed(bool state);
	void ByteToLeds(uint8_t data);
#endif
