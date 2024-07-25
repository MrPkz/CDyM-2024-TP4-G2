/*
 * leds.c
 *
 * Created: 25/7/2024 17:03:35
 *  Author: perei
 */ 

#include "leds.h"

static uint8_t rojo;

void IniciarTimers(void){
	TCCR1B |= (1<<CS12);																//Prescaler 256
	TCCR1A |= (1<<WGM10) | (1<<COM1B1) | (1<<COM1A1) | (1<<COM1B0) | (1<<COM1A0);		//Modo invertido, Fast PWM 8-bit
	azul = 255;												//Valor Azul
	verde = 255;											//Valor Verde
	rojo = 255;												//Valor Rojo
	DDRC &= ~(1 << PORTC3);									//Configuro el pin PC3 (ADC3) como entrada
	DDRB |= (1<<PORTB1) | (1<<PORTB2) | (1<<PORTB5);		//Configuro LEDs como salida
}

void CambiarColor(uint8_t col, uint8_t pos){
	switch(col){
		case 'R':
		rojo = pos;
		break;
		case 'G':
		verde = pos;
		break;
		case 'B':
		azul = pos;
		break;
	}
}

void UpdateRojo(void){
	if(rojo < TCNT1 ){
		PORTB |= (1<<PORTB5);
		}else{
		PORTB &= ~(1<<PORTB5);
	}
}