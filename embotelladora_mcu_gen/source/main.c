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
 * @file    MKL43Z4_Project.c
 * @brief   Application entry point.
 */
#include "embotelladora.h"
#include "inicializacion.h"

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL43Z4.h"
#include "fsl_debug_console.h"

// Macros
#define SENSOR_G		!(BOARD_SW1_GPIO->PDIR >> BOARD_SW1_GPIO_PIN & 1U)
#define SENSOR_C		!(BOARD_SW3_GPIO->PDIR >> BOARD_SW3_GPIO_PIN & 1U)
#define SALIDA_M_ON()	BOARD_LED_GREEN_GPIO->PCOR |= 1U << BOARD_LED_GREEN_GPIO_PIN
#define SALIDA_M_OFF()	BOARD_LED_GREEN_GPIO->PSOR |= 1U << BOARD_LED_GREEN_GPIO_PIN
#define SALIDA_T_ON()	BOARD_LED_RED_GPIO->PCOR |= 1U << BOARD_LED_RED_GPIO_PIN
#define SALIDA_T_OFF()	BOARD_LED_RED_GPIO->PSOR |= 1U << BOARD_LED_RED_GPIO_PIN


int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif


    /* Referencia
     * SW1 			=> G
     * SW3 			=> C
     * LED VERDE(1)	=> M
     * LED ROJO(2)	=> T
     */

    // Inicialización de los pines
    inicializacion();

    // Inicialización de la maquina de estados
    Embotelladora embotelladora;
    embotelladora_init(&embotelladora);
    embotelladora_enter(&embotelladora);


    // Loop del programa
    while(1) {

    	/* Generación de eventos
    	 * Se disparan los eventos según el estado de
    	 * las entradas
    	 */
    	if (SENSOR_G)
    		embotelladora_raise_sensorG_ON(&embotelladora);
    	else
    		embotelladora_raise_sensorG_OFF(&embotelladora);

    	if (SENSOR_C)
    		embotelladora_raise_sensorC_ON(&embotelladora);


    	/* Salidas
    	 * Se activan las salidas según algún parámetro
    	 * del diagrma de estados. En este caso, se usaron
    	 * variables dentro del diagrama de estados, pero
    	 * también se pueden utlizar los estados, por ejemplo
    	 * mediante la función:
    	 *
    	 * embotelladora_is_state_active(&embotelladora, Embotelladora_main_region_Llenando)
    	 */

    	// Salida M - Cinta tranportadora
    	if(embotelladora_get_m_cinta(&embotelladora))
    		SALIDA_M_ON();
    	else
    		SALIDA_M_OFF();

    	// Salida T - Valvula
    	if(embotelladora_get_t_valvula(&embotelladora))
    		SALIDA_T_ON();
    	else
    		SALIDA_T_OFF();
    }
    return 0;
}
