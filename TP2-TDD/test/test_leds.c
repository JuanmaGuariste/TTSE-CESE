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

/** @file test_leds.c
 ** @brief Unitary tests for leds module.
 **/

/**
 * @test Prender y apagar múltiples LED’s.
 * @test Prender todos los LEDs de una vez.
 * @test Apagar todos los LEDs de una vez.
 * @test Consultar el estado de un LED que está encendido
 * @test Consultar el estado de un LED que est apagado
 * @test Revisar limites de los parametros.
 * @test Revisar parámetros fuera de los limites.
 */

/* === Headers files inclusions ===============================================================
 */
#include "unity.h"
#include "leds.h"

/* === Macros definitions ======================================================================
 */

/* === Private data type declarations ==========================================================
 */

/* === Private variable declarations ===========================================================
 */
static uint16_t virtualLeds = 0xFFFF;

/* === Private function declarations ===========================================================
 */

/* === Public variable definitions =============================================================
 */

/* === Private variable definitions ============================================================
 */

/* === Private function implementation =========================================================
 */

/* === Public function implementation ==========================================================
 */

void setUp(void) {
    Leds_init(&virtualLeds);
}

//! * @test After initialization, all LEDs should be off.
void test_all_leds_initially_off(void) {
    uint16_t virtualLeds = 0xFFFF;
    Leds_init(&virtualLeds);
    TEST_ASSERT_EQUAL_HEX16(0x0000, virtualLeds);
}

//! * @test Turn on a single LED.
void test_turn_on_single_led(void) {
    Leds_turnOnSingle(4);
    TEST_ASSERT_EQUAL_HEX16(0x0008, virtualLeds);
}

//! * @test Turn off a single LED.
void test_turn_off_single_led(void) {
    Leds_turnOnSingle(4);
    Leds_turnOffSingle(4);
    TEST_ASSERT_EQUAL_HEX16(0x0000, virtualLeds);
}

/* === End of documentation ==================================================================== */