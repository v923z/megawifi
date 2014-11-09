#ifndef HARDWARE_H
#define HARDWARE_H

#define 	GLUE(a, b)		a##b
#define		GLUE3(a, b, c)	a##b##c
#define 	PORT(x)			GLUE(PORT, x)
#define 	DDR(x)			GLUE(DDR, x)
#define		PIN(y, x)		GLUE3(P, y, x) 

#define		LED_PORT		B
#define		LED_PIN			5

#define		ALL_ON()		PORTB |= _BV(PB0) | _BV(PB1) | _BV(PB2)
#define		RED_OFF()		PORTB &= ~_BV(PB0)
#define		GREEN_OFF()		PORTB &= ~_BV(PB1)
#define		BLUE_OFF()		PORTB &= ~_BV(PB2)

#define		LED_ON()		PORT(LED_PORT) |= _BV(PIN(LED_PORT, LED_PIN))
#define		LED_OFF()		PORT(LED_PORT) &= ~_BV((PIN(LED_PORT, LED_PIN)))
#define		LED_TOGGLE()	PORT(LED_PORT) ^= _BV(PIN(LED_PORT, LED_PIN))

#define		CAMERA_PORT		PORTB
#define		CAMERA_DDR		DDRB
#define		CAMERA_FOCUS	_BV(PB1)
#define		CAMERA_SHOT		_BV(PB3)
#define		FOCUS()	{CAMERA_PORT &= ~CAMERA_FOCUS; _delay_ms(200); CAMERA_PORT |= CAMERA_FOCUS;}
#define		SHOT()	{CAMERA_PORT &= ~CAMERA_SHOT; _delay_ms(200); CAMERA_PORT |= CAMERA_SHOT;}

#endif
