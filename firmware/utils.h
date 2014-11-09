#ifndef UTILS_H
#define UTILS_H

#include <avr/io.h> 
#include <util/delay.h>
#include <avr/wdt.h>
#include "hardware.h"

void blink(uint16_t );
void Port_Init(void);
void s_delay(uint16_t );
void ms_delay(uint16_t );
void us_delay(uint16_t );
void delay(uint16_t , uint8_t );
void SetPort(uint8_t , uint8_t );
void DirPort(uint8_t , uint8_t );
uint8_t ReadPort(uint8_t );
void Camera(uint8_t );
void Trigger_Wait(uint8_t , uint8_t , uint8_t );
void RGB_single(uint8_t , uint8_t , uint8_t );
#endif
