#include "wifi.h"

extern volatile uint8_t control_byte;
uint8_t counter;

uint16_t token_value, indx, dtime,  channel, threshold, value, counter_for;
extern volatile uint8_t data[MAX_DATA], control_byte;
uint8_t *pos, *pos_for, num, led_counter, read;
extern uint8_t command[MAX_DATA];
uint8_t if_register, while_register, *while_pointer;
uint8_t led_state = 1;

int main (void) {
	USART_Init();
	Port_Init();	
	sei();
	wdt_enable(WDTO_2S);

	for(;;) {
		wdt_reset();
		if((counter == 250) && (led_state == 1)) LED_TOGGLE();
		counter++;
		_delay_ms(2);
		
		switch(control_byte) {
		case COMMAND:
				USART_ReadCommand(';');
				pos = &command[0];
				USART_Restore();	// Restore the USART, so that we can use control_byte for breaking out of the main loop.
				// Begin parsing
				while(*pos != ';' && control_byte == 0) {
					token_value = GetToken(&pos);
					if(token_value == asm_convert("rbt")) {
						// Reboot
						for(;;) {}
					}
					else if(token_value == asm_convert("blk")) {
						// Blink LED
						value = GetNumber(&pos);						
						blink(value);
					}
					else if(token_value == asm_convert("ech")) {
						value = GetNumber(&pos);						
						USART_SendInteger(value, ';');
					}					
					else if(token_value == asm_convert("led")) {
						value = GetNumber(&pos);
						led_state = 1;
						if(value == 0) {
							LED_OFF();
							led_state = 0;
						} else if(value == 1) {
							LED_ON();
							led_state = 0;
						} else if(value == 2) {
							LED_TOGGLE();
							led_state = 0;
						}	
					} 
					else if(token_value == asm_convert("wau")) {
						// Wait us
						dtime = GetNumber(&pos);
						us_delay(dtime);
					}
					else if(token_value == asm_convert("wam")) {
						// Wait ms
						dtime = GetNumber(&pos);
						delay(dtime, 'm');
					}
					else if(token_value == asm_convert("was")) {
						// Wait s
						dtime = GetNumber(&pos);
						s_delay(dtime);
					}
					//else if(token_value == asm_convert("dac")) {
						//indx = GetNumber(&pos);
						//value = GetNumber(&pos);
						////DAC_Out(channel, value);
					//}
					//else if(token_value == asm_convert("adc")) {
						//indx = GetIndex(&pos);
						//channel = GetNumber(&pos);
						//value = ADC_Convert((uint8_t)channel);
						//SetVariable(indx, value, 's');
					//}
					//else if(token_value == asm_convert("set")) {
						//indx = GetIndex(&pos);
						//value = GetNumber(&pos);
						//SetVariable(indx, value, 's');
					//}
					//else if(token_value == asm_convert("add")) {
						//indx = GetIndex(&pos);
						//value = GetNumber(&pos);
						//SetVariable(indx, value, '+');
					//}
					//else if(token_value == asm_convert("sub")) {
						//indx = GetIndex(&pos);
						//value = GetNumber(&pos);
						//SetVariable(indx, value, '-');
					//}
					//else if(token_value == asm_convert("mul")) {
						//indx = GetIndex(&pos);
						//value = GetNumber(&pos);
						//SetVariable(indx, value, '*');
					//}					
					//else if(token_value == asm_convert("div")) {
						//indx = GetIndex(&pos);
						//value = GetNumber(&pos);
						//SetVariable(indx, value, '/');
					//}
					//else if(token_value == asm_convert("or")) {
						//indx = GetIndex(&pos);
						//value = GetNumber(&pos);
						//SetVariable(indx, value, '|');
					//}
					//else if(token_value == asm_convert("and")) {
						//indx = GetIndex(&pos);
						//value = GetNumber(&pos);
						//SetVariable(indx, value, '&');
					//}
					//else if(token_value == asm_convert("xor")) {
						//indx = GetIndex(&pos);
						//value = GetNumber(&pos);
						//SetVariable(indx, value, '^');
					//}
					//else if(token_value == asm_convert("neg")) {
						//indx = GetIndex(&pos);
						//SetVariable(indx, 0, '~');
					//}
					//else if(token_value == asm_convert("gt")) {
						//num = GetNumber(&pos);
						//value = GetNumber(&pos);
						//if(num > value) if_register = while_register = 1;
						//else if_register = while_register = 0;
					//}
					//else if(token_value == asm_convert("st")) {
						//num = GetNumber(&pos);
						//value = GetNumber(&pos);
						//if(num > value) if_register = while_register = 1;
						//else if_register = while_register = 0;
					//}
					//else if(token_value == asm_convert("eq")) {
						//num = GetNumber(&pos);
						//value = GetNumber(&pos);
						//if(num == value) if_register = while_register = 1;
						//else if_register = while_register = 0;
					//}
					//else if(token_value == asm_convert("neq")) {
						//num = GetNumber(&pos);
						//value = GetNumber(&pos);
						//if(num == value) if_register = while_register = 0;
						//else if_register = while_register = 1;
					//}
					//else if(token_value >= asm_convert("spa") && token_value <= asm_convert("spf")) {
						//num = GetNumber(&pos);
						//SetPort(TokenEnd(token_value), (uint8_t)num);
					//}
					//else if(token_value >=  asm_convert("dpa") && token_value <= asm_convert("dpf")) {
						//num = GetNumber(&pos);
						//DirPort(TokenEnd(token_value), (uint8_t)num);
					//}
					//else if(token_value >=  asm_convert("rpa") && token_value <= asm_convert("rpf")) {
						//value = GetNumber(&pos);
						//read = ReadPort(TokenEnd(token_value));
						//SetVariable(value, read, 's');
					//}					
					//else if(token_value == asm_convert("cam")) {
						//Camera(TokenEnd(token_value));
					//}	
					//else if(token_value == asm_convert("for")) {
						//counter_for = GetNumber(&pos);
						//if(counter_for > 0) counter_for--;
						//RemoveWhiteSpace(&pos);
						//if(*pos != '[') {
							//// break out of the loop, for there is a syntax error
							//*pos = ';';
							//break;
						//}
						//else pos++;
						//if(counter_for == 0) {
							//// We don't need to do anything
							//do { pos++; } while(*pos != ']' && *pos != '\0');
						//}
						//pos_for = pos;
					//}		
					//else if(token_value == asm_convert("gt")) {
						//num = GetNumber(&pos);
						//value = GetNumber(&pos);
						//if(num > value) if_register = while_register = 1;
						//else if_register = while_register = 0;
					//}
					//else if(token_value == asm_convert("if")) {
						//if_register = 0;
					//}
					//else if(token_value == asm_convert("whi")) {
						//while_register = 0;
						//while_pointer = pos-4;
					//}
					//if(*pos == ']') {
						//if(counter_for) { 
							//counter_for--;
							//pos = pos_for;
						//}
						//else pos++;
					//}
					//if(*pos == '{') {
						//if(if_register == 0) {
							//while((*pos != ':') && (*pos != '\0')) pos++;
						//}
						//else pos++;
					//}
					//if(*pos == '}') {
						//pos++;
						//if_register = 0;
					//}
					//if((*pos == ':') && (if_register == 1)) while((*pos != '}') && (*pos != '\0')) pos++;
					//if(*pos == '<') {
						//if(while_register == 0) {
							//while((*pos != '>') && (*pos != '\0')) pos++;
							//pos++;
						//}
						//else pos++;
					//}
					//if(*pos == '>') pos = while_pointer;

				}
				break;

			case BLINK:
				num = USART_ReadInteger('N');
				blink(num);
				USART_Restore();
				break;

			default:
				if(control_byte != 0) {
					USART_Flush();
					USART_Restore();
				}
				_delay_ms(2);
				counter++;
				break;				
		}
	}
	return(0);
}
