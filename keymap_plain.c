/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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

#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"

#define KEYMAP( \
                        F13,  F14,  F15,  F16,	F17,	F18,	F19,	F20,	F21,	F22,	F23,	F24,\
                        F1,   F2,   F3,   F4,	  F5,	  F6,	  F7,	  F8,	  F9,	  F10,	F11,	F12,\
  FS1,  FS6,    BCTIC,  K1,	  K2,   K3,	  K4,	  K5,	  K6,	  K7,	  K8,	  K9,	  K0,	   TIC,	IACC,	BKSP,	    INS,	HOME,	PAGSU,      UPAD7,UPAD8,UPAD9,UPADMINUS,\
  FS2,  FS7,    TAB,    Q,	  W,	  E,	  R,	  T,	  Y,	  U,	  I,	  O,	  P,	   EACC,	PLUS,	ENT,    CANC,	END,	PAGGIU,	    PAD7,	PAD8,	PAD9,	PADMINUS,\
  FS3,  FS8,    CAPS,   A,	  S,	  D,	  F,	  G,	  H,	  J,	  K,	  L,	  OACC,	 AACC,	UACC,	              UP,               PAD4,	PAD5,	PAD6,	DXPAD6,\
  FS4,  FS9,    SHFSX,  LT,	  Z,	  X,	  C,	  V,	  B,	  N,	  M,	  COMA,	DOT,	 MINUS,	SHFDX,	      LEFT,	CENTER,	RIGHT,  	PAD1,	PAD2,	PAD3,	PADPLUS,\
  FS5,  FS10,   CTRLSX,       ALT,    SPACE,	                                ALTGR,	      CTRLDX,	            DOWN,             PAD0,	            PADDOT\
) { \
    {LEFT, PAD1, CAPS, SHFDX, Z, X, C, V, M, F22, F10, F11, COMA, DOT, UACC, ENT, KC_NO, PAD2, PAD3, KC_NO} ,\
    {ALT, SPACE, CTRLDX, SHFSX, LT, KC_NO, KC_NO, B, N, F23, F24, F12, KC_NO, KC_NO, MINUS, KC_NO, KC_NO, PAD0, PADDOT, PADPLUS} ,\
    {KC_NO, FS3, FS8, KC_NO, KC_NO, KC_NO, KC_NO, T, Y, F20, F21, F9, PLUS, KC_NO, EACC, KC_NO, END, KC_NO, KC_NO, KC_NO} ,\
    {PADMINUS, FS7, TAB, KC_NO, Q, W, E, R, U, F19, F7, F8, I, O, P, PAD7, PAGGIU, PAD8, PAD9, KC_NO} ,\
    {KC_NO, FS1, FS6, KC_NO, BCTIC, KC_NO, KC_NO, K5, K6, F17, F18, F6, IACC, KC_NO, TIC, BKSP, INS, HOME, KC_NO, KC_NO} ,\
    {UPADMINUS, FS2, KC_NO, KC_NO, K1, K2, K3, K4, K7, F16, F4, F5, K8, K9, K0, UPAD7, PAGSU, UPAD8, UPAD9, KC_NO} ,\
    {DXPAD6, FS4, FS9, KC_NO, A, S, D, F, J, F14, F15, F3, K, L, OACC, PAD4, KC_NO, PAD5, PAD6, RIGHT} ,\
    {CTRLSX, FS10, FS5, ALTGR, KC_NO, KC_NO, KC_NO, G, H, F13, F1, F2, KC_NO, KC_NO, AACC, DOWN, UP, KC_NO, KC_NO, CENTER}\
}

#define _______ KC_TRNS

static const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      KEYMAP( \
//      /* Keymap 0: Default Layer
//      * ,-----------------------------------------------------------------------------------------------------------------------------.
//      * |                 |PrnSc|ScrLk|Pause|Lock |    | << |Play|Stop| >> |Mute|Vol-|Vol+|                                           |
//      * |-----------------------------------------------------------------------------------------------------------------------------|
//      * |                 |  F1 |  F2 |  F3 |  F4 |  F5|  F6|  F7|  F8|  F9| F10| F11| F12|                                           |
//      * |-----------------------------------------------------------------------------------------------------------------------------|
//      * |-----------------------------------------------------------------------------------------------------------------------------|
//      * |Copy|Pste|     ` |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|    Bspc|    INS|  HOME|  PGUP|    NLCK| PSLS| PAST| PMNS| |
//      * |-----------------------------------------------------------------------------------------------------------------------------|
//      * |Cut |Caps|    Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|      |    DEL|   END|  PGDN|     P7|   P8|   P9| |PPLS| |
//      * |--------------------------------------------------------------------       --------------------------------------------------|
//      * |BT< |BT>+|    FN1  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '| \ |Enter |	      |   UP |            P4|   P5|   P6| |  = | |
//      * |---------------------------------------------------------------------------------------------------------------------------- |
//      * |MC1 |App |    Shift|  \|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| *   Shift|   LEFT| DOWN | RIGHT|     P1|   P2|   P3| |PENT| |
//      * |----------------------------------------------------------------------------------------------------------------------|    | |
//      * |Esc |GUI |    Ctrl|    |Alt |            Space          |Alt |     |Ctrl  |       |   FN |           | *    P0| PDOT| |  * | |
//      * `-----------------------------------------------------------------------------------------------------------------------------'
//      */
                              KC_PSCR, KC_SLCK, KC_PAUS,KC_NO,  KC_NO,  KC_MPRV,KC_MPLY,KC_MSTP,KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,
                              KC_F1,   KC_F2,   KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,  KC_F11,  KC_F12,

  KC_COPY, KC_PASTE,  KC_ESC, KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,	KC_INS, KC_HOME, KC_PGUP,   KC_NLCK,KC_PSLS,KC_PAST, KC_PMNS,
  KC_CUT,  KC_CAPS,   KC_TAB, KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC, KC_RBRC,	KC_ENT,   KC_DEL, KC_END,  KC_PGDN,   KC_P7,  KC_P8,  KC_P9,   KC_PPLS,
  KC_NO,   KC_NO,     KC_NO,  KC_A,    KC_S,    KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,	                  KC_UP,              KC_P4,  KC_P5,  KC_P6,   KC_EQL,
  KC_NO,   KC_APP,    KC_LSFT,KC_BSLS, KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,	          KC_LEFT,KC_DOWN, KC_RGHT,   KC_P1,  KC_P2,  KC_P3,   KC_PENT,
  KC_ESC,  KC_LGUI,   KC_LCTL,         KC_LALT,                 KC_SPC,                 KC_RALT,                  KC_RCTL,	                          KC_NO,              KC_P0,          KC_PDOT
),


//         /* Keymap 1: Fn Layer
// 	 * ,-----------------------------------------------------------------------------------------------------------------------------.
//      * |                 |email|pwd1 |pwd2 |pwd3 |___ |___ |___ |___ |___ |___ |___ |___ |                                           |
//      * |-----------------------------------------------------------------------------------------------------------------------------|
//      * |                 |___  |___  |___  |___  |___ |___ |___ |___ |___ |___ |___ |___ |                                           |
//      * |-----------------------------------------------------------------------------------------------------------------------------|
//      * |-----------------------------------------------------------------------------------------------------------------------------|
//      * |___ |___ |   ___ |___|___|___|___|___|___|___|___|___|___|cmp1|___|  del  |   ___ |  ___ |  ___ |   ___ | ___ | ___ | ___ |  |
//      * |-----------------------------------------------------------------------------------------------------------------------------|
//      * |___ |___ |    ___  |___|___|___|___|___|___|___|up |___|pgu|___|___|      |   ___ |  ___ |  ___ |   ___ | ___ | ___ | ___ |  |
//      * |--------------------------------------------------------------------       --------------------------------------------------|
//      * |___ |___ |   FN1   |___|___|___|___|___|___|lft|dn |rgt|pgd|___|___| ___  |	      | ___  |          ___ | ___ | ___ | ___ |  |
//      * |-----------------------------------------------------------------------------------------------------------------------------|
//      * |___ |___ |    ___  |___|___|___|___|___|___|___|___|cmp2|___|___| ______  |  ___  | ___  | ___  |   ___ | ___ | ___ | |___|  |
//      * |----------------------------------------------------------------------------------------------------------------------|   |  |
//      * |___ |___ |    ___ |    |___ |            comp3          |___ |     |___   |       | FN1  |           |    ___ | ___ | |   |  |
//      * `-----------------------------------------------------------------------------------------------------------------------------'
//      */
// KEYMAP(
//                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______, _______, _______, _______, _______, _______, _______, _______,
//                         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

//     _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, KC_NO,	_______, KC_DEL,    _______, _______, _______,   _______, _______, _______, _______,
//     _______, _______,  _______, KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______, _______, KC_UP,   _______,  KC_PGUP, _______, _______,			_______, _______, _______,   _______, _______, _______, _______,
//     _______, _______,  _______, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, _______, _______, _______,            _______,            _______, _______, _______, _______,
//     _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_NO,    _______, _______, _______,			_______, _______, _______,   _______, _______, _______,
//     _______, _______,  _______,          _______,                            KC_NO,                 	_______,					_______,                     _______,                     _______, _______, _______
//     ),
 };

const action_t  fn_actions[] = {
    [0]  = ACTION_LAYER_MOMENTARY(1),
};


/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
  return keymaps[(layer)][(key.row)][(key.col)];
}

/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
  return fn_actions[FN_INDEX(keycode)];
}
