/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ch.h"
#include "hal.h"

/*
 * scan matrix
 */
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "util.h"
#include "wait.h"

#ifndef DEBOUNCE
#define DEBOUNCE 5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

inline uint8_t matrix_rows(void) {
  return MATRIX_ROWS;
}

inline uint8_t matrix_cols(void) {
  return MATRIX_COLS;
}

#define LED_ON()                                  \
  do {                                            \
    palSetPad(TEENSY_PIN13_IOPORT, TEENSY_PIN13); \
  } while (0)
#define LED_OFF()                                   \
  do {                                              \
    palClearPad(TEENSY_PIN13_IOPORT, TEENSY_PIN13); \
  } while (0)
#define LED_TGL()                                    \
  do {                                               \
    palTogglePad(TEENSY_PIN13_IOPORT, TEENSY_PIN13); \
  } while (0)

void matrix_init(void) {
  // initialize row and col
  unselect_rows();
  init_cols();

  // initialize matrix state: all keys off
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    matrix[i] = 0;
    matrix_debouncing[i] = 0;
  }

  // debug
  debug_matrix = true;
  LED_ON();
  wait_ms(500);
  LED_OFF();
}

uint8_t matrix_scan(void) {
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    select_row(i);
    wait_us(30);  // without this wait read unstable value.
    matrix_row_t cols = read_cols();
    if (matrix_debouncing[i] != cols) {
      matrix_debouncing[i] = cols;
      if (debouncing) {
        debug("bounce!: ");
        debug_hex(debouncing);
        debug("\n");
      }
      debouncing = DEBOUNCE;
    }
    unselect_rows();
  }

  if (debouncing) {
    if (--debouncing) {
      wait_ms(1);
    } else {
      for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = matrix_debouncing[i];
      }
    }
  }

  return 1;
}

inline bool matrix_is_on(uint8_t row, uint8_t col) {
  return (matrix[row] & ((matrix_row_t)1 << col));
}

inline matrix_row_t matrix_get_row(uint8_t row) {
  return matrix[row];
}

void matrix_print(void) {
  print("\nr/c 0123456789ABCDEF\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    phex(row);
    print(": ");
    pbin_reverse16(matrix_get_row(row));
    print("\n");
  }
}
#define KB_COL_01 TEENSY_PIN0_IOPORT, TEENSY_PIN0
#define KB_COL_02 TEENSY_PIN1_IOPORT, TEENSY_PIN1
#define KB_COL_03 TEENSY_PIN2_IOPORT, TEENSY_PIN2
#define KB_COL_04 TEENSY_PIN3_IOPORT, TEENSY_PIN3
#define KB_COL_05 TEENSY_PIN4_IOPORT, TEENSY_PIN4
#define KB_COL_06 TEENSY_PIN5_IOPORT, TEENSY_PIN5
#define KB_COL_07 TEENSY_PIN6_IOPORT, TEENSY_PIN6
#define KB_COL_08 TEENSY_PIN7_IOPORT, TEENSY_PIN7
#define KB_COL_09 TEENSY_PIN8_IOPORT, TEENSY_PIN8
#define KB_COL_10 TEENSY_PIN9_IOPORT, TEENSY_PIN9
#define KB_COL_11 TEENSY_PIN10_IOPORT, TEENSY_PIN10
#define KB_COL_12 TEENSY_PIN11_IOPORT, TEENSY_PIN11
#define KB_COL_13 TEENSY_PIN12_IOPORT, TEENSY_PIN12
#define KB_COL_14 TEENSY_PIN33_IOPORT, TEENSY_PIN33
#define KB_COL_15 TEENSY_PIN16_IOPORT, TEENSY_PIN16
#define KB_COL_16 TEENSY_PIN32_IOPORT, TEENSY_PIN32
#define KB_COL_17 TEENSY_PIN31_IOPORT, TEENSY_PIN31
#define KB_COL_18 TEENSY_PIN30_IOPORT, TEENSY_PIN30
#define KB_COL_19 TEENSY_PIN29_IOPORT, TEENSY_PIN29
#define KB_COL_20 TEENSY_PIN23_IOPORT, TEENSY_PIN23

#define setKeyboardPinMode(PARAMS1, PARAM2) palSetPadMode(PARAMS1, PARAM2)
/* Column pin configuration
 */
static void init_cols(void) {
  // internal pull-up
  setKeyboardPinMode(KB_COL_01, PAL_MODE_INPUT_PULLUP);
  setKeyboardPinMode(KB_COL_02, PAL_MODE_INPUT_PULLUP);
  setKeyboardPinMode(KB_COL_03, PAL_MODE_INPUT_PULLUP);
  setKeyboardPinMode(KB_COL_04, PAL_MODE_INPUT_PULLUP);
  setKeyboardPinMode(KB_COL_05, PAL_MODE_INPUT_PULLUP);
  setKeyboardPinMode(KB_COL_06, PAL_MODE_INPUT_PULLUP);
  setKeyboardPinMode(KB_COL_07, PAL_MODE_INPUT_PULLUP);
  setKeyboardPinMode(KB_COL_08, PAL_MODE_INPUT_PULLUP);
  setKeyboardPinMode(KB_COL_09, PAL_MODE_INPUT_PULLUP);
  setKeyboardPinMode(KB_COL_10, PAL_MODE_INPUT_PULLUP);
  setKeyboardPinMode(KB_COL_11, PAL_MODE_INPUT_PULLUP);
  setKeyboardPinMode(KB_COL_12, PAL_MODE_INPUT_PULLUP);
  setKeyboardPinMode(KB_COL_13, PAL_MODE_INPUT_PULLUP);
  setKeyboardPinMode(KB_COL_15, PAL_MODE_INPUT_PULLUP);
  setKeyboardPinMode(KB_COL_20, PAL_MODE_INPUT_PULLUP);
  setKeyboardPinMode(KB_COL_19, PAL_MODE_INPUT_PULLUP);
  setKeyboardPinMode(KB_COL_18, PAL_MODE_INPUT_PULLUP);
  setKeyboardPinMode(KB_COL_17, PAL_MODE_INPUT_PULLUP);
  setKeyboardPinMode(KB_COL_16, PAL_MODE_INPUT_PULLUP);
  setKeyboardPinMode(KB_COL_14, PAL_MODE_INPUT_PULLUP);
}

#define readRowAsPowerOfTwo(port, pin, power) \
  ((palReadPad(port, pin) == PAL_HIGH) ? 0 : (1 << power))

#define readRow(PARAMS1, PARAM2) readRowAsPowerOfTwo(PARAMS1, PARAM2)
/* Returns status of switches(1:on, 0:off) */
static matrix_row_t read_cols(void) {
  return readRow(KB_COL_01, 0) | readRow(KB_COL_02, 1) | readRow(KB_COL_03, 2) |
         readRow(KB_COL_04, 3) | readRow(KB_COL_05, 4) | readRow(KB_COL_06, 5) |
         readRow(KB_COL_07, 6) | readRow(KB_COL_08, 7) | readRow(KB_COL_09, 8) |
         readRow(KB_COL_10, 9) | readRow(KB_COL_11, 10) |
         readRow(KB_COL_12, 11) | readRow(KB_COL_13, 12) |
         readRow(KB_COL_14, 13) | readRow(KB_COL_15, 14) |
         readRow(KB_COL_16, 15) | readRow(KB_COL_17, 16) |
         readRow(KB_COL_18, 17) | readRow(KB_COL_19, 18) |
         readRow(KB_COL_20, 19);
}
#define KB_ROW_01 TEENSY_PIN14_IOPORT, TEENSY_PIN14
#define KB_ROW_02 TEENSY_PIN15_IOPORT, TEENSY_PIN15
#define KB_ROW_03 TEENSY_PIN17_IOPORT, TEENSY_PIN17
#define KB_ROW_04 TEENSY_PIN18_IOPORT, TEENSY_PIN18
#define KB_ROW_05 TEENSY_PIN19_IOPORT, TEENSY_PIN19
#define KB_ROW_06 TEENSY_PIN20_IOPORT, TEENSY_PIN20
#define KB_ROW_07 TEENSY_PIN21_IOPORT, TEENSY_PIN21
#define KB_ROW_08 TEENSY_PIN22_IOPORT, TEENSY_PIN22
/* Row pin configuration
 */
static void unselect_rows(void) {
  setKeyboardPinMode(KB_ROW_01, PAL_MODE_INPUT);
  setKeyboardPinMode(KB_ROW_02, PAL_MODE_INPUT);
  setKeyboardPinMode(KB_ROW_03, PAL_MODE_INPUT);
  setKeyboardPinMode(KB_ROW_04, PAL_MODE_INPUT);
  setKeyboardPinMode(KB_ROW_05, PAL_MODE_INPUT);
  setKeyboardPinMode(KB_ROW_06, PAL_MODE_INPUT);
  setKeyboardPinMode(KB_ROW_07, PAL_MODE_INPUT);
  setKeyboardPinMode(KB_ROW_08, PAL_MODE_INPUT);
}

#define selectRow(PARAMS)                          \
  palSetPadMode(PARAMS, PAL_MODE_OUTPUT_PUSHPULL); \
  palClearPad(PARAMS);

static void select_row(uint8_t row) {
  (void)row;
  // Output low to select
  switch (row) {
    case 0:
      selectRow(KB_ROW_02);
      break;

    case 1:
      selectRow(KB_ROW_01);
      break;

    case 2:
      selectRow(KB_ROW_03);
      break;

    case 3:
      selectRow(KB_ROW_04);
      break;

    case 4:
      selectRow(KB_ROW_05);
      break;

    case 5:
      selectRow(KB_ROW_06);
      break;

    case 6:
      selectRow(KB_ROW_07);
      break;

    case 7:
      selectRow(KB_ROW_08);
      break;
  }
}
