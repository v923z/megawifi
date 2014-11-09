#ifndef PARSING_H
#define	PARSING_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define MAX_VARIABLE	128

uint16_t asm_convert(char *);
void RemoveWhiteSpace(uint8_t ** );
uint16_t GetNumber(uint8_t ** );
uint16_t GetIndex(uint8_t ** );
uint16_t GetToken(uint8_t **);
uint8_t TokenEnd(uint16_t );
void SetVariable(uint16_t , uint16_t , uint8_t );
uint16_t GetVariable(uint16_t );
#endif
