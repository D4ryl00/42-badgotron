#include "badgotron.h"

void    NRJ_init(void)
{
    u8	tmp;

	NRJ_PIN_ANALOG = 0; // Enable digital mode because this PIN is also analog
	NRJ_PIN_MODE = PIN_MODE_INPUT;
	NRJ_PIN_PULLUP = 1;
	// READ PORT BIT FOR CLEARING IT
	tmp = NRJ_PIN_READ;
}