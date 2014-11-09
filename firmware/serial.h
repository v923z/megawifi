#ifndef SERIAL_H
#define SERIAL_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BAUD_PRESCALE (((F_CPU / (BAUDRATE * 16UL))) - 1)
#define MAX_DATA	128

void USART_Flush(void);
void USART_Init(void);
unsigned char USART_ReadByte(void);
void USART_SendByte(unsigned char );
void USART_SendString(char *);
void USART_OK(void);
void USART_Restore(void);
uint16_t USART_ReadInteger(uint8_t );
void USART_SendInteger(unsigned int, unsigned char );
void USART_ReadCommand(uint8_t );
void USART_SendIntByte(uint16_t );
#endif
