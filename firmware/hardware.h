#ifndef HARDWARE_H
#define HARDWARE_H

#define 	GLUE(a, b)		a##b
#define		GLUE3(a, b, c)	a##b##c
#define 	PORT(x)			GLUE(PORT, x)
#define 	DDR(x)			GLUE(DDR, x)
#define		PIN(y, x)		GLUE3(P, y, x) 

#define		LED_PORT		B
#define		LED_PIN			5

#define		LED_ON()		PORT(LED_PORT) |= _BV(PIN(LED_PORT, LED_PIN))
#define		LED_OFF()		PORT(LED_PORT) &= ~_BV((PIN(LED_PORT, LED_PIN)))
#define		LED_TOGGLE()	PORT(LED_PORT) ^= _BV(PIN(LED_PORT, LED_PIN))

#endif
