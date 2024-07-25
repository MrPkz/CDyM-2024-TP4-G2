
/*Author: Ramiro Madera y Ulises Pereira*/

#include "main.h"

static uint8_t pos;
volatile uint8_t col=0, aux;		// Variables que se modificarán cuando se atienda las interrupciones
//En aux guarda el caracter leído, en pos el caracter en mayúscula de ser válido

ISR(USART_RX_vect){
	aux = UDR0; //la lectura del UDR borra flag RXC
	//Se procesa el caracter de forma case-sensitive
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
	} else {		//De ser el caracter válido, se notifica de ello y queda la selección en el estado previo
		CaracterInvalido();
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
		CambiarColor(col,pos);
		UpdateRojo();
    }
}

