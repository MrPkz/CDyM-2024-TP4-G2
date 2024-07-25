/*
 * adc.c
 *
 * Created: 25/7/2024 16:50:43
 *  Author: perei
 */ 

#include "adc.h"

static uint8_t valoractual;

void ConfigurarADC(void){
	// Configuración del ADC:
	ADMUX |= (1 << MUX0) | (1 << MUX1);					  // Selecciono el canal 3 del ADC
	ADMUX |= (1 << REFS0);								  // Configuro el ADC para que trabaje con el voltaje de referencia AVCC
	ADMUX |= (1 << ADLAR);								  // Configuro el ADC para que la salida sea izquierda justificada (8 bits) el resultado estará en ADCH
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Configuro el preescalador del ADC para que trabaje a 125kHz
	ADCSRA |= (1 << ADATE);								  // Habilito el modo de disparo automático
	ADCSRA |= (1 << ADEN);								  // Habilito el ADC
	
	DIDR0= 0x01;			//Deshabilita algo REVISAR
	ADCSRA |= (1<<ADSC);								//Manda Conversion Inicial
}

uint8_t ObtenerValor(void){
	while(!(ADCSRA&(1<<ADIF))){}		//wait for conversion to finish
	valoractual=ADCH;
	ADCSRA |= (1<<ADIF); //borrar flag
	ADCSRA |= (1<<ADSC);//start conversion
	return valoractual;
}