/*
 * TP4Microchip.c
 *
 * Created: 1/7/2024 14:16:21
 * Author : Perei
 */ 

#define F_CPU 16000000UL
#define azul OCR1A
#define verde OCR1B
 

#include "serialPort.h"
#include <avr/interrupt.h>
#define BR9600 (0x67)	// 0x67=103 configura BAUDRATE=9600 a 16MHz

#include <avr/io.h>
#include <util/delay.h>

volatile uint8_t rojo;
volatile uint8_t col=0;		// Variable que se modificar� cuando se atienda la interrupci�n

ISR(USART_RX_vect){
	uint8_t aux;
	aux = UDR0; //la lectura del UDR borra flag RXC
	if (aux == 'R' || aux == 'G' || aux == 'B'){
		col = aux;
	} else if (aux == 'r' || aux == 'g' || aux == 'b'){
		col = aux - 32;
	} else {
		SerialPort_Send_String("Caracter no valido. Seleccione 'R' 'G' o 'B' para modificar los colores del LED. \r\n");
		col = 0;
	}
}

int main(void)
{
	
	SerialPort_Init(BR9600); 																										// Inicializo formato 8N1 y BAUDRATE = 9600bps
	SerialPort_TX_Enable();																											// Activo el Transmisor del Puerto Serie (1<<TXEN0) en UCSR0B
	SerialPort_RX_Enable();																											// Activo el Receptor del Puerto Serie	(1<<RXEN0) en UCSR0B
	SerialPort_RX_Interrupt_Enable();
	SerialPort_Send_String("�Bienvenido! Seleccione 'R' 'G' o 'B' para modificar los colores del LED. \r\n");


	// Configuración del ADC:
	DDRC &= ~(1 << PC3);								  // Configuro el pin PC3 (ADC3) como entrada
	ADMUX |= (1 << MUX0) | (1 << MUX1);					  // Selecciono el canal 3 del ADC
	ADMUX |= (1 << REFS0);								  // Configuro el ADC para que trabaje con el voltaje de referencia AVCC
	ADMUX |= (1 << ADLAR);								  // Configuro el ADC para que la salida sea izquierda justificada (8 bits) el resultado estará en ADCH
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Configuro el preescalador del ADC para que trabaje a 125kHz
	ADCSRA |= (1 << ADATE);								  // Habilito el modo de disparo automático
	ADCSRA |= (1 << ADEN);								  // Habilito el ADC

	TCCR1A |= (1<<WGM10);		//Modo Fast PWM 8-Bit
	TCCR1B |= (1<<CS12);		//Prescaler 256
	TCCR1A |= (1<<COM1B1) | (1<<COM1A1) | (1<<COM1B0) | (1<<COM1A0);		//Modo invertido
	azul = 250;				//Valor Azul
	verde = 20;					//Valor Verde
	
	DDRB |= (1<<PORTB1) | (1<<PORTB2) | (1<<PORTB5);
	DDRB &= ~(1<<PORTC3);
	
	rojo=2;
	uint16_t c=0;
	
	sei();
	
    while (1) 
    {
		switch(col){
			case 'R':
				rojo = ADCH;
				break;
			case 'G':
				verde = ADCH;
			break;
			case 'B':
				azul = ADCH;
			break;
		}
		if(rojo < TCNT1 ){
			PORTB |= (1<<PORTB5);
		}else{
			PORTB &= ~(1<<PORTB5);
		}
    }
}

