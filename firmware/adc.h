#ifndef ADC_H
#define ADC_H

void ADC_Init(void);
uint16_t ADC_Convert(int8_t );
uint16_t ADC_ConversionN(int8_t , int8_t );
void ADC_Wait(int8_t , uint16_t , uint8_t );
#endif
