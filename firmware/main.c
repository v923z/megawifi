#include "wifi.h"

extern volatile uint8_t control_byte;

uint16_t blink, pos, id, angles[5];
uint8_t counter;

int main (void) {
	USART_Init();
	Port_Init();
	sei();
	wdt_enable(WDTO_2S);

	for(;;) {
		wdt_reset();
		if(counter == 250) LED_TOGGLE();
		switch(control_byte) {
				
			case BLINK:
				blink = USART_ReadInteger('N');
				while(blink) {
					wdt_reset(); 	
					blink--;
					LED_TOGGLE();
					_delay_ms(100);
				}
				USART_Restore();
				break;

			case ECHO:
				USART_SendInteger(USART_ReadInteger('N'), 'N');
				USART_Restore();
				break;

			case VERSION:
				USART_SendString(VERSION_STRING);
				USART_Restore();
				break;
				
			case IDENTIFY:
				USART_SendString(ID_STRING);
				USART_Restore();
				break;
			
			case REBOOT:
				_delay_ms(1000);
				// This will trigger the watchdog timer after 2 seconds.
				for(;;) {}
				break;

			default:
				if(control_byte != 0) {
					USART_Flush();
					//USART_SendString(FAIL_STRING);
					USART_Restore();
				}
				_delay_ms(2);
				counter++;
				break;				
		}
	}
	return(0);
}
