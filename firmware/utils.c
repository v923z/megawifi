#include "utils.h"

void Port_Init() {	
	uint16_t k = 250, j;
	DDR(LED_PORT) |= _BV(LED_PIN);
	while(k > 50) {
		LED_TOGGLE();
		for(j=0; j < k; j++) _delay_ms(1);
		k -= 20;
	}
}
