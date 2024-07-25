/*
 * leds.h
 *
 * Created: 25/7/2024 17:03:44
 *  Author: perei
 */ 


#ifndef LEDS_H_
#define LEDS_H_

#define azul OCR1A
#define verde OCR1B

#include "globalheader.h"

void IniciarTimers(void);
void CambiarColor(uint8_t, uint8_t);
void UpdateRojo(void);


#endif /* LEDS_H_ */