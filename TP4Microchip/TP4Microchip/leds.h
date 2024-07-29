
/*Author: Ramiro Madera y Ulises Pereira*/

#ifndef LEDS_H_
#define LEDS_H_

//Definiciones de registros como colores para claridad conceptual del código
#define azul OCR1A
#define verde OCR1B

#include "globalheader.h"

void IniciarTimers(void);
void CambiarColor(uint8_t, uint8_t);
void UpdateRojo(void);

#endif /* LEDS_H_ */