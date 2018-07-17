#include "badgotron.h"

void    NRJ_init(void)
{
    u8	tmp;

	BUTTON_PIN_DIGITAL = 1; // Enable digital mode because this PIN is also analog
	BUTTON_PIN_MODE = PIN_MODE_INPUT;
	BUTTON_PIN_PULLUP = 0;
	// READ PORT BIT FOR CLEARING IT
	tmp = BUTTON_PIN_READ;
}