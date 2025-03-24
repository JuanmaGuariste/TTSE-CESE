/************************************************************************************************
Copyright (c) 2025, Juan Manuel Guariste <juanmaguariste@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

#ifndef LEDS_H
#define LEDS_H

/** @file leds.h
 ** @brief Declaraciones de la interfaz del módulo de control de LEDs
 **/

/* === Headers files inclusions ================================================================ */
#include <stdint.h>
#include <stdbool.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/* === Public data type declarations =========================================================== */
/**
 * @brief Enumeration for LED states.
 *
 * This enumeration defines the two possible states of an LED:
 *
 * - LED_OFF: The LED is turned off (value 0).
 *
 * - LED_ON: The LED is turned on (value 1).
 *
 * @note This type is used to represent the state of an individual LED in the system.
 */
typedef enum { LED_OFF = 0, LED_ON = 1 } LedState_t;

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Initializes the LED library.
 *
 * @note This function must be called before using any other function in the library.
 *
 * @param address Pointer to the memory address where the LEDs are stored.
 *
 * @return void
 */
void Leds_init(uint16_t * address);

/**
 * @brief Turns on a single LED.
 *
 * @param led LED number to turn on (1 to 16).
 *
 * @return void
 */
void Leds_turnOnSingle(uint8_t led);

/**
 * @brief Turns off a single LED.
 *
 * @param led LED number to turn off (1 to 16).
 *
 * @return void
 */
void Leds_turnOffSingle(uint8_t led);

/**
 * @brief Turns on all LEDs.
 *
 * @param void
 *
 * @return void
 */
void Leds_turnOnAllLeds();

/**
 * @brief Turns off all LEDs.
 *
 * @param void
 *
 * @return void
 */
void Leds_turnOffAllLeds(void);

/**
 * @brief Checks if a LED is turned on.
 *
 * @param led LED number to check (1 to 16).
 *
 * @return true if the LED is turned on, false otherwise.
 */
bool Leds_isLedTurnedOn(uint8_t led);

/**
 * @brief Checks if a LED is turned off.
 *
 * @param led LED number to check (1 to 16).
 *
 * @return true if the LED is turned off, false otherwise.
 */
bool Leds_isLedTurnedOff(uint8_t led);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* LEDS_H */