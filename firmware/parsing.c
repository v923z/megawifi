#include "parsing.h"

uint16_t variable[MAX_VARIABLE];
uint16_t variable_ind;

uint16_t asm_convert(char *str) {
	uint16_t r = 0;
	while(*str != '\0') {
		r = (r << 5) + (*str-96);	
		str++;
	}
	return(r);
}

void RemoveWhiteSpace(uint8_t **pos) {
	// At this point, all whitespaces should have been converted to 
	// space (see USART_ReadCommand in serial.c!)
	while(**pos == ' ') (*pos)++;
}

uint16_t GetNumber(uint8_t **pos) {
	uint16_t ret = 0;
	uint8_t ss, isvariable = 0;
	variable_ind = 65535;
	RemoveWhiteSpace(pos);
	while(1) {
	    ss = *((*pos)++);
	    if((ss == ' ') || 
			(ss == ';') || 
			(ss == ']') || 
			(ss == '[') || 
			(ss == ')') ||
			(ss == '}') ||
			(ss == '{')) break;
	    else if((ss >= '0') && (ss <= '9')) ret = ret * 10 + (ss - '0');
	    else if(ss == 'v') {
			while(ss != '(') ss = *((*pos)++);
			variable_ind = GetNumber(pos);
			while((*(*pos) == ')')) (*pos)++;
			isvariable = 1;
			break;
		}
	}
	// This is needed, so that we can catch loops
	if(ss == ';' || ss == ']') (*pos)--;
	if(isvariable) {
		if(variable_ind < MAX_VARIABLE) ret = variable[variable_ind];
		else ret = 65535;
	}
	//printf("ret: %d\n", ret);
	return(ret);
}

uint16_t GetIndex(uint8_t **pos) {
	uint8_t ss;
	RemoveWhiteSpace(pos);
	ss = *((*pos)++);
	if(ss != 'v') return(65535);
	return(GetNumber(pos));
}

uint16_t GetToken(uint8_t **pos) {
	uint16_t value = 0;
	uint8_t c;
	RemoveWhiteSpace(pos);
	while(1) {
		c = *((*pos)++);
		//if(c == '\0' || c == ' ' || c == ';' || c == '[' || c == ']') break;
		if(c >= 'a' && c <= 'z') value = (value << 5) + (c-96);
		else break;
	}
	if(c == ';' || c == '[' || c == ']') (*pos)--;
	return(value);
}

uint8_t TokenEnd(uint16_t token) {
	return((uint8_t)((token & 0x1F) + 96));
}

void SetVariable(uint16_t ind, uint16_t value, uint8_t op) {
	if(ind >= MAX_VARIABLE) return;
	if(op == 's') variable[ind] = value;
	else if(op == '+') variable[ind] += value;
	else if(op == '-') variable[ind] -= value;
	else if(op == '*') variable[ind] *= value;
	else if(op == '/') variable[ind] /= value;
	else if(op == '|') variable[ind] |= value;
	else if(op == '&') variable[ind] &= value;
	else if(op == '^') variable[ind] ^= value;
	else if(op == '~') variable[ind] = ~variable[ind];
}
