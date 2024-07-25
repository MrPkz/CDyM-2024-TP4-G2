/*
 * TP4Microchip.c
 *
 * Created: 1/7/2024 14:16:21
 * Author : Perei
 */ 

#include "main.h"

static uint8_t pos,posprev;
volatile uint8_t col=0;		// Variable que se modificar� cuando se atienda la interrupci�n
volatile uint8_t aux;

ISR(USART_RX_vect){
	aux = UDR0; //la lectura del UDR borra flag RXC
	if (aux == 'R' || aux == 'G' || aux == 'B' || aux == 'S'){
		col = aux;
		switch(aux){
			case 'R':
			ColorSeleccionado("Rojo");
			break;
			case 'G':
			ColorSeleccionado("Verde");
			break;
			case 'B':
			ColorSeleccionado("Azul");
			break;
			case 'S':
			SistemaPausado();
			break;
		}
	} else if (aux == 'r' || aux == 'g' || aux == 'b' || aux == 's'){
		col = aux - 32;
		switch(aux){
			case 'r':
			ColorSeleccionado("Rojo");
			break;
			case 'g':
			ColorSeleccionado("Verde");
			break;
			case 'b':
			ColorSeleccionado("Azul");
			break;
			case 's':
			SistemaPausado();
			break;
		}
	} else {
		CaracterInvalido();
		col = 0;
	}
}

int main(void)
{
	ConfigurarTerminal8a1();
	sei();
	IniciarTerminal();

	ConfigurarADC();
	IniciarTimers();
	
    while (1){
		pos=ObtenerValor();
		if(posprev!=pos){
			CambiarColor(col,pos);
			posprev=pos;
		}
		UpdateRojo();
		
    }
}

