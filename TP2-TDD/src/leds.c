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

/** @file leds.c
 ** @brief Definición de la función principal del programa
 **/

/* === Headers files inclusions =============================================================== */

#include "leds.h"

/* === Macros definitions ====================================================================== */

//! Mask to turn off all LEDs
#define ALL_LEDS_OFF 0x0000
//! Mask to turn on all LEDs
#define ALL_LEDS_ON 0xFFFF
//! brief LED shift offset to obtain the mask
#define LEDS_TO_BIT_OFFSET 1
//! brief Constant with the first bit set to one for generating a mask
#define FIRST_BIT 1

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

//! @brief Private variable to store the address of the LEDs output port
static uint16_t * portAddress;

/* === Private function declarations =========================================================== */
/**
 * @brief Private function to convert an LED number into a bit mask.
 * @param led LED number for which the bit mask is needed.
 * @return Bit mask with a 1 in the position corresponding to the LED.
 */
static uint16_t ledToMask(uint8_t led);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

static uint16_t ledToMask(uint8_t led) {
    return (FIRST_BIT << (led - LEDS_TO_BIT_OFFSET));
};

/* === Public function implementation ========================================================== */

void Leds_init(uint16_t * address) {
    portAddress = address;
    *portAddress = ALL_LEDS_OFF;
};

void Leds_turnOnSingle(uint8_t led) {
    *portAddress |= ledToMask(led);
};

void Leds_turnOffSingle(uint8_t led) {
    *portAddress &= ~ledToMask(led);
};

void Leds_turnOnAllLeds() {
    *portAddress = ALL_LEDS_ON;
};

/* === End of documentation ==================================================================== */