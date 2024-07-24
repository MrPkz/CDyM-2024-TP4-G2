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

static uint8_t rojo,valorprevio=0,valoractual=0;
volatile uint8_t col=0;		// Variable que se modificar� cuando se atienda la interrupci�n
volatile uint8_t aux;

ISR(USART_RX_vect){
	aux = UDR0; //la lectura del UDR borra flag RXC
	if (aux == 'R' || aux == 'G' || aux == 'B'){
		col = aux;
		switch(aux){
			case 'R':
				SerialPort_Send_String("Estas modificando el color Rojo. \r\n");
			break;
			case 'G':
				SerialPort_Send_String("Estas modificando el color Verde. \r\n");
			break;
			case 'B':
				SerialPort_Send_String("Estas modificando el color Azul. \r\n");
			break;
		}
	} else if (aux == 'r' || aux == 'g' || aux == 'b'){
		col = aux - 32;
		switch(aux){
			case 'r':
			SerialPort_Send_String("Estas modificando el color Rojo. \r\n");
			break;
			case 'g':
			SerialPort_Send_String("Estas modificando el color Verde. \r\n");
			break;
			case 'b':
			SerialPort_Send_String("Estas modificando el color Azul. \r\n");
			break;
		}
	} else {
		SerialPort_Send_String("Caracter no valido. Seleccione 'R', 'r', 'G', 'g', 'B' o 'b' para modificar los colores del LED. \r\n");
		col = 0;
	}
}

int main(void)
{
	
	SerialPort_Init(BR9600); 																										// Inicializo formato 8N1 y BAUDRATE = 9600bps
	SerialPort_TX_Enable();																											// Activo el Transmisor del Puerto Serie (1<<TXEN0) en UCSR0B
	SerialPort_RX_Enable();																											// Activo el Receptor del Puerto Serie	(1<<RXEN0) en UCSR0B
	SerialPort_RX_Interrupt_Enable();
	sei();
	SerialPort_Send_String("Bienvenido al sistema. Seleccione 'R', 'r', 'G', 'g', 'B' o 'b' para modificar los colores del LED. \r\n");


	// Configuración del ADC:
	DDRC &= ~(1 << PORTC3);								  // Configuro el pin PC3 (ADC3) como entrada
	ADMUX |= (1 << MUX0) | (1 << MUX1);					  // Selecciono el canal 3 del ADC
	ADMUX |= (1 << REFS0);								  // Configuro el ADC para que trabaje con el voltaje de referencia AVCC
	ADMUX |= (1 << ADLAR);								  // Configuro el ADC para que la salida sea izquierda justificada (8 bits) el resultado estará en ADCH
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Configuro el preescalador del ADC para que trabaje a 125kHz
	ADCSRA |= (1 << ADATE);								  // Habilito el modo de disparo automático
	ADCSRA |= (1 << ADEN);								  // Habilito el ADC
	
	DIDR0= 0x01;			//Deshabilita algo REVISAR
	
	TCCR1A |= (1<<WGM10);		//Modo Fast PWM 8-Bit
	TCCR1B |= (1<<CS12);		//Prescaler 256
	TCCR1A |= (1<<COM1B1) | (1<<COM1A1) | (1<<COM1B0) | (1<<COM1A0);		//Modo invertido
	azul = 255;				//Valor Azul
	verde = 0;					//Valor Verde
	
	DDRB |= (1<<PORTB1) | (1<<PORTB2) | (1<<PORTB5);
	//DDRB &= ~(1<<PORTC3);
	
	rojo=255;
	//uint16_t c=0;
	ADCSRA |= (1<<ADSC);
    while (1) 
    {
		if((ADCSRA&(1<<ADIF))){
			valoractual=ADCH;
			ADCSRA |= (1<<ADIF); //borrar flag
			ADCSRA |= (1<<ADSC);//start conversion
		}//wait for conversion to finish
		if(valorprevio!=valoractual){	
			switch(col){
				case 'R':
				rojo = valoractual;
				break;
				case 'G':
				verde = valoractual;
				break;
				case 'B':
				azul = valoractual;
				break;
				case 'r':
				rojo = valoractual;
				break;
				case 'g':
				verde = valoractual;
				break;
				case 'b':
				azul = valoractual;
				break;
			}
			valorprevio=valoractual;
		}
		if(rojo < TCNT1 ){
			PORTB |= (1<<PORTB5);
		}else{
			PORTB &= ~(1<<PORTB5);
		}
		
    }
}

