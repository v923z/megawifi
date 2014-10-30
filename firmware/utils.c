#include "utils.h"

extern volatile uint8_t control_byte;

void Port_Init() {	
	uint16_t k = 250, j;
	DDR(LED_PORT) |= _BV(LED_PIN);
	while(k > 50) {
		LED_TOGGLE();
		for(j=0; j < k; j++) _delay_ms(1);
		k -= 20;
	}
}

void blink(uint16_t value) {
	while(value) {
		value--;
		delay(100, 'm');
		LED_TOGGLE();
	}
}

void s_delay(uint16_t delay) {
	while(delay > 0) { // && control_byte == 0) {
		ms_delay(1000);
		delay--;
	}
}

void ms_delay(uint16_t delay) {
	while(delay > 0) {
		_delay_ms(1.0);
		delay--;
		wdt_reset();
	}
}

void us_delay(uint16_t delay) {
      while(delay) {
            _delay_us(1.0);
            delay--;
      }
}

void delay(uint16_t delay, uint8_t dtype) {	
	if(dtype == 'u') us_delay(delay);
	else if(dtype == 'm') ms_delay(delay);
	else if(dtype == 's') s_delay(delay);
}

void SetPort(uint8_t port, uint8_t value) {
	// Note that we have to use lowercase letters here, in order to conform to the command string specifications.
	switch(port) {
		case 'b':
			PORTB = value;
			break;

		case 'c':
			PORTC = value;
			break;
			
		case 'd':
			PORTD = value;
			break;			
	}
}

void DirPort(uint8_t port, uint8_t value) {
	switch(port) {
		case 'b':
			DDRB = value;
			break;

		case 'c':
			DDRC = value;
			break;
			
		case 'd':
			DDRD = value;
			break;			
	}	
}

uint8_t ReadPort(uint8_t port) {
	switch(port) {
		case 'b':
			return(PINB);
			break;

		case 'c':
			return(PINC);
			break;
			
		default:
			return(PIND);
			break;
		}	
}

void Camera(uint8_t do_what) {
	if(do_what == 'f') FOCUS();
	if(do_what == 's') SHOT();
}

void Trigger_Wait(uint8_t port, uint8_t high_low, uint8_t mask) {
	volatile uint8_t *port_in;
	
	switch(port) {
		case 'b':
			port_in = &PINB;
			break;

		case 'c':
			port_in = &PINC;
			break;
			
		case 'd':
			port_in = &PIND;
			break;
		
		default:
			return;
			break;
	}	
	if(high_low == 0) {
		// We wait for a low value on pin 'mask'
		while(*port_in != mask && control_byte == 0) { };
	}
	if(high_low == 1) {
		// We wait for a high value on pin 'mask'
		while(*port_in != ~mask && control_byte == 0) { };
	}	
}
