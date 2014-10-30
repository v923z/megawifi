#include <avr/io.h>

extern volatile uint8_t control_byte;

void ADC_Init(void) {
	// Internal voltage reference, 2.56 V. This also means that the highest 
	// measureable voltage is 2.56 V, so care should be taken when hooking 
	// anything up to the analog input channels 
	ADMUX |= ( _BV(REFS0) | _BV(REFS1) );
	// Prescaler 128
	ADCSRA |= _BV(ADEN) | _BV(ADFR) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2);
}
// ------------------------------------------------------
uint16_t ADC_Convert(int8_t channel) {
	unsigned short HIGH, LOW;

	ADMUX = (ADMUX & ~0x0F) | channel;

	ADCSRA |= _BV(ADSC);
	while((ADCSRA & _BV(ADIF))==0);
	ADCSRA |= _BV(ADIF);
	LOW = ADCL;
	HIGH = ADCH;

	return((HIGH << 8) + LOW);
}
// ------------------------------------------------------
int16_t ADC_ConversionN(int8_t channel, int8_t N) {
	// This function takes N readings, and returns their sum
	// Since the return value is a 16-bit integer, N should be smaller than 64, otherwise, an overflow will occur
	uint16_t HIGH, LOW;
	uint16_t ret_val = 0;

	ADMUX = (ADMUX & ~0x0F) | channel;

	while(N) {
		ADCSRA |= _BV(ADSC);
		while((ADCSRA & _BV(ADIF))==0);
		ADCSRA |= _BV(ADIF);
		LOW = ADCL;
		HIGH = ADCH; 
		ret_val += ( (HIGH << 8) + LOW );
		N--;
	}
	return(ret_val);
}

void ADC_Wait(int8_t channel, uint16_t threshold, uint8_t dir) {
	if((channel > 3) || (threshold > 1023)) {
		control_byte = 'A';
		return;
	}
	if(dir == '+') {
		while((ADC_Convert(channel) < threshold) && control_byte == 0) {};
	}
	if(dir == '-') {
		while((ADC_Convert(channel) > threshold) && control_byte == 0) {};
	}							
}
