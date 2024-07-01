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

static uint8_t rojo;

volatile uint8_t RX_Buffer=0;		// Variable que se modificará cuando se atienda la interrupción
volatile uint8_t flagFin=0;			// Variable que se modificará cuando se atienda la interrupción

ISR(USART_RX_vect){
	RX_Buffer = UDR0; //la lectura del UDR borra flag RXC
	switch (RX_Buffer) {
		case 'R':
			//Modificar rojo
			rojo=255; 
			azul=0;
			verde=0;
		break;
		case 'G':
		//Modificar verde
		rojo=0;
		azul=0;
		verde=255;
		break;
		case 'B':
		//Modificar azul
		rojo=0;
		azul=255;
		verde=0;
		break;
	}
	RX_Buffer=0;
}

int main(void)
{
	
	SerialPort_Init(BR9600); 																										// Inicializo formato 8N1 y BAUDRATE = 9600bps
	SerialPort_TX_Enable();																											// Activo el Transmisor del Puerto Serie (1<<TXEN0) en UCSR0B
	SerialPort_RX_Enable();																											// Activo el Receptor del Puerto Serie	(1<<RXEN0) en UCSR0B
	SerialPort_RX_Interrupt_Enable();
	SerialPort_Send_String("¡Bienvenido! Seleccione 'R' 'G' o 'B' para modificar los colores del LED. \r\n");
	
	
	
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
		/*
		if(++c>1000){
			c=0;
			rojo= (rojo+1) % 256;
		}
		if(rojo < TCNT1 ){
			PORTB |= (1<<PORTB5);
		}else{
			PORTB &= ~(1<<PORTB5);
		}
		_delay_us(1);
		*/
    }
}

