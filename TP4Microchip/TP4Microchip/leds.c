
/*Author: Ramiro Madera y Ulises Pereira*/

#include "leds.h"

static uint8_t rojo;

void IniciarTimers(void){
	TCCR1B |= (1<<CS12);																//Setea Prescaler en 256
	TCCR1A |= (1<<WGM10) | (1<<COM1B1) | (1<<COM1A1) | (1<<COM1B0) | (1<<COM1A0);		//Setea el Modo invertido (COM1A/B) en modo Fase Correcta de 8 bits (WGM)
	//Inicialmente, la luz será blanca
	azul = 255;																			//Indica Valor Azul
	verde = 255;																		//Indica Valor Verde
	rojo = 255;																			//Indica Valor Rojo
	DDRC &= ~(1 << PORTC3);																//Configuro el pin PC3 (ADC3) como entrada
	DDRB |= (1<<PORTB1) | (1<<PORTB2) | (1<<PORTB5);									//Configuro pins de LEDs como salida
}

void CambiarColor(uint8_t col, uint8_t pos){
	//Asigna el valor actual para el color almacenado en 'pos' según corresponda en 'col'
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
	//Actualiza el estado del color rojo por Software
	if(rojo < TCNT1 ){
		PORTB |= (1<<PORTB5);
		}else{
		PORTB &= ~(1<<PORTB5);
	}
}