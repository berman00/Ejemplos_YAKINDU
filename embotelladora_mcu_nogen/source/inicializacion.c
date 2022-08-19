/*
 * inicializacion.c
 *
 *  Created on: Oct 26, 2021
 *      Author: valen
 */


#include "inicializacion.h"
#include "pin_mux.h"

void inicializacion(void){

	BOARD_InitBUTTONSPins();
	BOARD_InitLEDsPins();
}
