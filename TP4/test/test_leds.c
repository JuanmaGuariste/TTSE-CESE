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

//! @test After initialization, all LEDs should be off.
void test_all_leds_initially_off(void) {
    uint16_t virtualLeds = 0xFFFF;
    Leds_init(&virtualLeds);
    TEST_ASSERT_EQUAL_HEX16(0x0000, virtualLeds);
}

//! @test Turn on a single LED.
void test_turn_on_single_led(void) {
    Leds_turnOnSingle(4);
    TEST_ASSERT_EQUAL_HEX16(0x0008, virtualLeds);
}

//! @test Turn off a single LED.
void test_turn_off_single_led(void) {
    Leds_turnOnSingle(4);
    Leds_turnOffSingle(4);
    TEST_ASSERT_EQUAL_HEX16(0x0000, virtualLeds);
}

//! @test Turn on and turn off multiple LEDs.
void test_turn_on_and_off_multiple_leds(void) {
    Leds_turnOnSingle(4);
    Leds_turnOnSingle(6);
    Leds_turnOffSingle(4);
    Leds_turnOffSingle(8);
    TEST_ASSERT_EQUAL_HEX16(0x0020, virtualLeds);
}

//! * @test Turn on all LEDs at once.
void test_turn_on_all_leds_together(void) {
    Leds_turnOnAllLeds();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, virtualLeds);
}

//! @test Turn off all LEDs at once.
void test_turn_off_all_leds_together(void) {
    Leds_turnOnAllLeds();
    Leds_turnOffAllLeds();
    TEST_ASSERT_EQUAL_HEX16(0x0000, virtualLeds);
}

//!  @test Query the state of a LED that is on.
void test_query_the_state_of_a_led_that_is_on(void) {
    Leds_turnOnSingle(4);
    TEST_ASSERT_EQUAL(true, Leds_isLedTurnedOn(4));
}

//! @test Query the state of a LED that is off.
void test_query_the_state_of_a_led_that_is_off(void) {
    Leds_turnOffSingle(4);
    TEST_ASSERT_EQUAL(true, Leds_isLedTurnedOff(4));
}

//! @test Check if the lower limit LED (LED 1) is turned on correctly.
void test_turn_on_lower_limit_led(void) {
    Leds_turnOnSingle(1);
    TEST_ASSERT_EQUAL(true, Leds_isLedTurnedOn(1));
    TEST_ASSERT_EQUAL_HEX16(0x0001, virtualLeds);
}

//! @test Check if the lower limit LED (LED 1) is turned off correctly.
void test_turn_off_lower_limit_led(void) {
    Leds_turnOffSingle(1);
    TEST_ASSERT_EQUAL(true, Leds_isLedTurnedOff(1));
    TEST_ASSERT_EQUAL_HEX16(0x0000, virtualLeds);
}

//! @test Check if the upper limit LED (LED 16) is turned on correctly.
void test_turn_on_upper_limit_led(void) {
    Leds_turnOnSingle(16);
    TEST_ASSERT_EQUAL(true, Leds_isLedTurnedOn(16));
    TEST_ASSERT_EQUAL_HEX16(0x8000, virtualLeds);
}

//! @test Check if the upper limit LED (LED 16) is turned off correctly.
void test_turn_off_upper_limit_led(void) {
    Leds_turnOffSingle(16);
    TEST_ASSERT_EQUAL(true, Leds_isLedTurnedOff(16));
    TEST_ASSERT_EQUAL_HEX16(0x0000, virtualLeds);
}

// ! @test Check parameters below the lower limit.
void test_below_lower_limit_led_parameters(void) {
    Leds_turnOnSingle(0);
    TEST_ASSERT_EQUAL(false, Leds_isLedTurnedOn(0));
    TEST_ASSERT_EQUAL_HEX16(0x0000, virtualLeds);
    Leds_turnOffSingle(0);
    TEST_ASSERT_EQUAL(false, Leds_isLedTurnedOff(0));
    TEST_ASSERT_EQUAL_HEX16(0x0000, virtualLeds);
}

//! @test Check parameters above the upper limit.
void test_above_upper_limit_led_parameters(void) {
    Leds_turnOnSingle(17);
    TEST_ASSERT_EQUAL(false, Leds_isLedTurnedOn(17));
    TEST_ASSERT_EQUAL_HEX16(0x0000, virtualLeds);
    Leds_turnOffSingle(17);
    TEST_ASSERT_EQUAL(false, Leds_isLedTurnedOff(17));
    TEST_ASSERT_EQUAL_HEX16(0x0000, virtualLeds);
}

/* === End of documentation ==================================================================== */
