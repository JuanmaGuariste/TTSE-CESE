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

/** @file test_API_lcd.c
 ** @brief Unit tests for the LCD API module.
 **/

/*
    Requirements to be tested:
    1- LCD must be initialized with the correct configuration sequence.
    2- It must be possible to clear the LCD screen.
    3- It must be possible to position the cursor:
        3.1- On row 1, column 0
        3.2- On row 1, column 4
        3.3- On row 2, column 0
        3.4- On row 2, column 5
        3.5- On row 2, column 16
        3.6- On row 1, column 16
    4- It must be possible to print text.
*/

/* === Headers files inclusions ===============================================================
 */
#include "unity.h"
#include "API_lcd.h"
#include "mock_API_lcd_port.h"

/* === Macros definitions ======================================================================
 */

/* === Private data type declarations ==========================================================
 */

/* === Private variable declarations ===========================================================
 */

/**
 * @brief Private global variable to store the backlight state.
 * 1 = on, 0 = off.
 */
static uint8_t backLight = 1;

/**
 *	@brief Command sequence to configure the LCD.
 */
static const uint8_t LCD_INIT_CMD[] = {_4BIT_MODE,
                                       DISPLAY_CONTROL,
                                       RETURN_HOME,
                                       ENTRY_MODE_SET | AUTOINCREMENT,
                                       DISPLAY_CONTROL | DISPLAY_ON,
                                       CLEAR_DISPLAY};

/* === Private function declarations ===========================================================
 */

/* === Public variable definitions =============================================================
 */

/* === Private variable definitions ============================================================
 */

/* === Private function implementation =========================================================
 */
/**
 * @brief Initializes the test environment.
 * Sets the default behavior for the functions that will be mocked.
 */
void setUp(void) {
    LCD_portDelay_Ignore();
}

/**
 * @brief Mock function for LCD_sendByte calls.
 *
 * @param byte Byte to be "sent" to the LCD.
 * @param ret_value Boolean return value expected from the mocked call.
 */
static void LCD_sendByte_ExpectAndReturn(uint8_t byte, bool ret_value) {
    LCD_portWriteByte_ExpectAndReturn(byte | ENABLE, ret_value);
    LCD_portWriteByte_ExpectAndReturn(byte, ret_value);
}

/**
 * @brief Mock function simulating the behavior of the private LCD_sendMsg function.
 *
 * @param data Data to be sent.
 * @param rs Indicates whether the data is a COMMAND or DATA.
 * @param ret_value Boolean return value expected from the mocked call.
 */
static void LCD_sendMsg_ExpectAndReturn(uint8_t data, uint8_t rs, bool ret_value) {
    LCD_sendByte_ExpectAndReturn((data & HIGH_NIBBLE_MASK) | (backLight << BACKLIGHT_SHIFT) | rs,
                                 ret_value);
    LCD_sendByte_ExpectAndReturn((data & LOW_NIBBLE_MASK) << TO_HIGH_NIBBLE_SHIFT |
                                     (backLight << BACKLIGHT_SHIFT) | rs,
                                 ret_value);
}

/**
 * @brief Mock function simulating the behavior of the private LCD_sendNibble function.
 *
 * @param data Data to be sent.
 * @param rs Indicates whether the data is a COMMAND or DATA.
 * @param ret_value Boolean return value expected from the mocked call.
 */
static void LCD_sendNibble_ExpectAndReturn(uint8_t data, uint8_t rs, bool ret_value) {
    LCD_sendByte_ExpectAndReturn((data & LOW_NIBBLE_MASK) << TO_HIGH_NIBBLE_SHIFT |
                                     (backLight << BACKLIGHT_SHIFT) | rs,
                                 ret_value);
}

//! @test Requirement 1: Test to verify the LCD initialization sequence.
void test_LCD_initialization_sequence(void) {
    port_init_ExpectAndReturn(true);
    LCD_sendNibble_ExpectAndReturn(CMD_INI1, COMMAND, true);
    LCD_sendNibble_ExpectAndReturn(CMD_INI1, COMMAND, true);
    LCD_sendNibble_ExpectAndReturn(CMD_INI1, COMMAND, true);
    LCD_sendNibble_ExpectAndReturn(CMD_INI2, COMMAND, true);
    for (uint8_t indice = 0; indice < sizeof(LCD_INIT_CMD); indice++) {
        LCD_sendMsg_ExpectAndReturn(LCD_INIT_CMD[indice], COMMAND, true);
    }
    TEST_ASSERT_EQUAL(LCD_OK, LCD_init());
}

//! @test Requirement 2: The LCD screen must be cleared correctly.
void test_LCD_clear_screen(void) {
    LCD_sendMsg_ExpectAndReturn(CLEAR_DISPLAY, COMMAND, true);
    TEST_ASSERT_EQUAL(LCD_OK, LCD_clear());
}

//! @test Requirement 3.1: Cursor must be positioned on row 1, column 0.
void test_LCD_setCursor_row1_col0(void) {
    uint8_t col = 0;
    LCD_sendMsg_ExpectAndReturn((LCD_ROW_1_ADDRESS + col) | SET_DDRAM_ADDRESS, COMMAND, true);
    TEST_ASSERT_EQUAL(LCD_OK, LCD_setCursor(LCD_ROW_1, col));
}

//! @test Requirement 3.2: Cursor must be positioned on row 1, column 4.
void test_LCD_setCursor_positions_row1_col4_correctly(void) {
    uint8_t col = 4;
    LCD_sendMsg_ExpectAndReturn((LCD_ROW_1_ADDRESS + col) | SET_DDRAM_ADDRESS, COMMAND, true);
    TEST_ASSERT_EQUAL(LCD_OK, LCD_setCursor(LCD_ROW_1, col));
}

//! @test Requirement 3.3: Cursor must be positioned on row 2, column 0.
void test_LCD_setCursor_positions_row2_col0_correctly(void) {
    uint8_t col = 0;
    LCD_sendMsg_ExpectAndReturn((LCD_ROW_2_ADDRESS + col) | SET_DDRAM_ADDRESS, COMMAND, true);
    TEST_ASSERT_EQUAL(LCD_OK, LCD_setCursor(LCD_ROW_2, col));
}

//! @test Requirement 3.4: Cursor must be positioned on row 2, column 5.
void test_LCD_setCursor_positions_row2_col5_correctly(void) {
    uint8_t col = 5;
    LCD_sendMsg_ExpectAndReturn((LCD_ROW_2_ADDRESS + col) | SET_DDRAM_ADDRESS, COMMAND, true);
    TEST_ASSERT_EQUAL(LCD_OK, LCD_setCursor(LCD_ROW_2, col));
}

//! @test Requirement 3.5: Cursor must be positioned on row 2, column 16.
void test_LCD_setCursor_positions_row2_col16_correctly(void) {
    uint8_t col = 16;
    LCD_sendMsg_ExpectAndReturn((LCD_ROW_2_ADDRESS + col) | SET_DDRAM_ADDRESS, COMMAND, true);
    TEST_ASSERT_EQUAL(LCD_OK, LCD_setCursor(LCD_ROW_2, col));
}

//! @test Requirement 3.6: Cursor must be positioned on row 1, column 16.
void test_LCD_setCursor_positions_row1_col16_correctly(void) {
    uint8_t col = 16;
    LCD_sendMsg_ExpectAndReturn((LCD_ROW_1_ADDRESS + col) | SET_DDRAM_ADDRESS, COMMAND, true);
    TEST_ASSERT_EQUAL(LCD_OK, LCD_setCursor(LCD_ROW_1, col));
}

//! @test Requirement 4: It must be possible to print text.
void test_LCD_print_text_correctly(void) {
    char text[] = "Test text";
    LCD_sendMsg_ExpectAndReturn(CLEAR_DISPLAY, COMMAND, true); // LCD_clear()
    LCD_sendMsg_ExpectAndReturn((LCD_ROW_1_ADDRESS + LCD_COL_0) | SET_DDRAM_ADDRESS, COMMAND,
                                true); // LCD_setCursor(row 1, col 0)
    // Expect a call to LCD_printChar() for each character
    for (int i = 0; text[i] != '\0'; i++) {
        LCD_sendMsg_ExpectAndReturn(text[i], DATA, true);
    }
    TEST_ASSERT_EQUAL(LCD_OK, LCD_printText(text));
}

/* === End of documentation ====================================================================
 */
