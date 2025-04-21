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
 ** @brief Definition of the library for LED control
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
//! brief Minimum LED number
#define MIN_LED 1
//! brief Maximum LED number
#define MAX_LED 16

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

//! @brief Private variable to store the address of the LEDs output port
static uint16_t * portAddress;

/* === Private function declarations =========================================================== */
/**
 * @brief Private function to convert an LED number into a bit mask.
 *
 * @param led LED number for which the bit mask is needed.
 *
 * @return Bit mask with a 1 in the position corresponding to the LED.
 */
static uint16_t ledToMask(uint8_t led);

/**
 * @brief Private function to update the value of the LED port.
 *  *
 * @param value The value to be written to the port. Each bit corresponds to a specific LED's state.
 *
 * @return void
 */
static void updatePortValue(uint16_t value);

/**
 * @brief Private function to set the state of an individual LED. *
 *
 * @param led The LED number to set the state for (1 to 16).
 *
 * @param state The desired state of the LED (ON or OFF).
 *
 * @note The `state` is expected to be an enumerated value of type `LedState_t`.
 *
 * @return void
 */
static void setLedState(uint8_t led, LedState_t state);

/**
 * @brief Private function to set the address of the LED port.
 *
 * @param address Pointer to the address of the LED port.
 *
 * @return void
 */
static void setPortAddress(uint16_t * address);

/**
 * @brief Private function to get the address of the LED port.
 *
 * @return uint16_t* Pointer to the address of the LED port.
 */
static uint16_t * getPortAddress(void);

/* === Public variable definitions =============================================================
 */

/* === Private variable definitions ============================================================
 */

/* === Private function implementation =========================================================
 */
uint16_t ledToMask(uint8_t led) {
    return (FIRST_BIT << (led - LEDS_TO_BIT_OFFSET));
};

void updatePortValue(uint16_t value) {
    *portAddress = value;
}

void setLedState(uint8_t led, LedState_t state) {
    uint16_t currentValue = *portAddress;
    if (state == LED_ON) {
        currentValue |= ledToMask(led);
    } else {
        currentValue &= ~ledToMask(led);
    }
    updatePortValue(currentValue);
}

void setPortAddress(uint16_t * address) {
    portAddress = address;
}

uint16_t * getPortAddress(void) {
    return portAddress;
}

/* === Public function implementation ==========================================================
 */

void Leds_init(uint16_t * address) {
    setPortAddress(address);
    Leds_turnOffAllLeds();
};

void Leds_turnOnSingle(uint8_t led) {
    setLedState(led, LED_ON);
};

void Leds_turnOffSingle(uint8_t led) {
    setLedState(led, LED_OFF);
};

void Leds_turnOnAllLeds() {
    updatePortValue(ALL_LEDS_ON);
};

void Leds_turnOffAllLeds(void) {
    updatePortValue(ALL_LEDS_OFF);
}

bool Leds_isLedTurnedOn(uint8_t led) {
    if (led < MIN_LED || led > MAX_LED) {
        return false;
    }
    uint16_t * port = getPortAddress();
    return (*port & ledToMask(led));
};

bool Leds_isLedTurnedOff(uint8_t led) {
    if (led < MIN_LED || led > MAX_LED) {
        return false;
    }
    uint16_t * port = getPortAddress();
    return !(*port & ledToMask(led));
}
/* === End of documentation ====================================================================
 */