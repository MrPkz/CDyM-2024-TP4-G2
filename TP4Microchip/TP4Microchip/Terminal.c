/*
 * Terminal.c
 *
 * Created: 25/7/2024 16:33:29
 *  Author: perei
 */ 

#include "terminal.h"

static void MostrarMenu(void){
	SerialPort_Send_String("Seleccione 'R', 'r', 'G', 'g', 'B' o 'b' para modificar los colores del LED, y 'S' o 's' para dejar de modificar colores. \r\n");
	SerialPort_Wait_For_TX_Buffer_Free();
}

static void EscribirColor(char * color){
	SerialPort_Send_String(color);
	SerialPort_Wait_For_TX_Buffer_Free();
	SerialPort_Send_String(".\r\n");
	SerialPort_Wait_For_TX_Buffer_Free();
}

void ConfigurarTerminal8a1(void){
	SerialPort_Init(BR9600); 																										// Inicializo formato 8N1 y BAUDRATE = 9600bps
	SerialPort_TX_Enable();																											// Activo el Transmisor del Puerto Serie (1<<TXEN0) en UCSR0B
	SerialPort_RX_Enable();																											// Activo el Receptor del Puerto Serie	(1<<RXEN0) en UCSR0B
	SerialPort_RX_Interrupt_Enable();
}

void IniciarTerminal(void){
	SerialPort_Send_String("Bienvenido al sistema. \r\n");
	SerialPort_Wait_For_TX_Buffer_Free();
	MostrarMenu();
}

void ColorSeleccionado(char * s){
	SerialPort_Send_String("Estas modificando el color ");
	SerialPort_Wait_For_TX_Buffer_Free();
	EscribirColor(s);
}

void SistemaPausado(void){
	SerialPort_Send_String("Modificación desactivada. \r\n");
	SerialPort_Wait_For_TX_Buffer_Free();
}

void CaracterInvalido(void){
	SerialPort_Send_String("Caracter no valido. \r\n");
	SerialPort_Wait_For_TX_Buffer_Free();
	MostrarMenu();
}

