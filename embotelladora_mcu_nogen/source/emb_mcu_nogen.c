/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    embotelladora_mcu_nogen.c
 * @brief   Application entry point.
 */
#include "inicializacion.h"

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL43Z4.h"
#include "fsl_debug_console.h"

#define SENSOR_G		!(BOARD_SW1_GPIO->PDIR >> BOARD_SW1_GPIO_PIN & 1U)
#define SENSOR_C		!(BOARD_SW3_GPIO->PDIR >> BOARD_SW3_GPIO_PIN & 1U)
#define SALIDA_M_ON()	BOARD_LED_GREEN_GPIO->PCOR |= 1U << BOARD_LED_GREEN_GPIO_PIN
#define SALIDA_M_OFF()	BOARD_LED_GREEN_GPIO->PSOR |= 1U << BOARD_LED_GREEN_GPIO_PIN
#define SALIDA_T_ON()	BOARD_LED_RED_GPIO->PCOR |= 1U << BOARD_LED_RED_GPIO_PIN
#define SALIDA_T_OFF()	BOARD_LED_RED_GPIO->PSOR |= 1U << BOARD_LED_RED_GPIO_PIN

typedef enum{
	Inicio,
	Movimiento,
	Llenando,
	Retirar_botella
} estado;

int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    inicializacion();
    estado estado_actual = Inicio;

    while(1){

    	switch(estado_actual){

    	case Inicio:
    		SALIDA_T_OFF();
    		SALIDA_M_OFF();

    		if(SENSOR_G) estado_actual = Llenando;
    		else estado_actual = Movimiento;
    		break;

    	case Movimiento:
    		SALIDA_T_OFF();
    		SALIDA_M_ON();

    		if(SENSOR_G) estado_actual = Llenando;
    		break;

    	case Llenando:
    		SALIDA_T_ON();
    		SALIDA_M_OFF();

    		if(SENSOR_C) estado_actual = Retirar_botella;
    		break;

    	case Retirar_botella:
    		SALIDA_T_OFF();
    		SALIDA_M_ON();

    		if(!SENSOR_G) estado_actual = Movimiento;
    		break;
    	}
    }
    return 0;
}
