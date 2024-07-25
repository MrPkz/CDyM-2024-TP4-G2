/*
 * Terminal.h
 *
 * Created: 25/7/2024 16:33:41
 *  Author: perei
 */ 


#ifndef TERMINAL_H_
#define TERMINAL_H_

#include "globalheader.h"
#include "serialPort.h"
#define BR9600 (0x67)	// 0x67=103 configura BAUDRATE=9600 a 16MHz

void ConfigurarTerminal8a1(void);
void IniciarTerminal(void);
void ColorSeleccionado(char *);
void SistemaPausado(void);
void CaracterInvalido(void);

#endif /* TERMINAL_H_ */