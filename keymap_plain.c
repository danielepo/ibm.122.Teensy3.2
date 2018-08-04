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
			  K09, K1D, K1E, K31, K45, K46, K59, K6D, K6E, K81, K95, K96, \
			  K0A, K0B, K1F, K32, K33, K47, K5A, K5B, K6F, K82, K83, K97, \
	K3D, K3E, K40, K2C,	K2D, K2E, K2F, K43, K44, K30, K34, K35, K36, K4A, K48, K4B,		K4C, K4D, K38,	K37, K39, K3A, K28, \
	K29, K51, K52, K54,	K55, K56, K57, K6B, K6C, K58, K5C, K5D, K5E, K72, K70,			K24, K74, K60,	K5F, K61, K62, K50, \
	K65, K66, K7A, K18,	K19, K1A, K1B, K07, K08, K1C, K20, K21, K22, K0E, K86, K87,			 K10,		K23, K25, K26, K14, \
	K15, K16, K8F, K90,	K7C, K7D, K7E, K7F, K93, K94, K80, K84, K85, K9A, K7B,			K78, K13, K27,	K79, K89, K8A, \
	K02, K01, K00,		K8C,				K8D,			    K03,	  K8E,				 K0F,			 K9D, K9E, K9F \
) { \
    { K00,   K01, K02,   K03,   KC_NO, KC_NO, KC_NO, K07, K08, K09, K0A, K0B, KC_NO, KC_NO, K0E, K0F,   K10,   KC_NO, KC_NO, K13 }, \
    { K14,   K15, K16,   KC_NO, K18,   K19,   K1A,   K1B, K1C, K1D, K1E, K1F, K20,   K21,   K22, K23,   K24,   K25,   K26,   K27 }, \
    { K28,   K29, KC_NO, KC_NO, K2C,   K2D,   K2E,   K2F, K30, K31, K32, K33, K34,   K35,   K36, K37,   K38,   K39,   K3A,   KC_NO }, \
    { KC_NO, K3D, K3E,   KC_NO, K40,   KC_NO, KC_NO, K43, K44, K45, K46, K47, K48,   KC_NO, K4A, K4B,   K4C,   K4D,   KC_NO, KC_NO }, \
    { K50,   K51, K52,   KC_NO, K54,   K55,   K56,   K57, K58, K59, K5A, K5B, K5C,   K5D,   K5E, K5F,   K60,   K61,   K62,   KC_NO }, \
    { KC_NO, K65, K66,   KC_NO, KC_NO, KC_NO, KC_NO, K6B, K6C, K6D, K6E, K6F, K70,   KC_NO, K72, KC_NO,	K74,   KC_NO, KC_NO, KC_NO }, \
    { K78,   K79, K7A,   K7B,   K7C,   K7D,   K7E,   K7F, K80, K81, K82, K83, K84,   K85,   K86, K87,   KC_NO, K89,   K8A,   KC_NO }, \
    { K8C,   K8D, K8E,   K8F,   K90,   KC_NO, KC_NO, K93, K94, K95, K96, K97, KC_NO, KC_NO, K9A, KC_NO, KC_NO, K9D,   K9E,   K9F } \
}

#define _______ KC_TRNS

static const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

KEYMAP(
     /* Keymap 0: Default Layer
     * ,-----------------------------------------------------------------------------------------------------------------------------.
     * |                 |PrnSc|ScrLk|Pause|Lock |    | << |Play|Stop| >> |Mute|Vol-|Vol+|                                           |
     * |-----------------------------------------------------------------------------------------------------------------------------|
     * |                 |  F1 |  F2 |  F3 |  F4 |  F5|  F6|  F7|  F8|  F9| F10| F11| F12|                                           |
     * |-----------------------------------------------------------------------------------------------------------------------------|
     * |-----------------------------------------------------------------------------------------------------------------------------|
     * |Copy|Pste|     ` |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|    Bspc|    INS|  HOME|  PGUP|    NLCK| PSLS| PAST| PMNS| |
     * |-----------------------------------------------------------------------------------------------------------------------------|
     * |Cut |Caps|    Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|      |    DEL|   END|  PGDN|     P7|   P8|   P9| |PPLS| |
     * |--------------------------------------------------------------------       --------------------------------------------------|
     * |BT< |BT>+|    FN1  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '| \ |Enter |	      |   UP |            P4|   P5|   P6| |  = | |
     * |---------------------------------------------------------------------------------------------------------------------------- |
     * |MC1 |App |    Shift|  \|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| *   Shift|   LEFT| DOWN | RIGHT|     P1|   P2|   P3| |PENT| |
     * |----------------------------------------------------------------------------------------------------------------------|    | |
     * |Esc |GUI |    Ctrl|    |Alt |            Space          |Alt |     |Ctrl  |       |   FN |           | *    P0| PDOT| |  * | |
     * `-----------------------------------------------------------------------------------------------------------------------------'
     */
                       KC_PSCR, KC_SLCK, KC_PAUS, KC_NO, KC_NO, KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,
                       KC_F1,   KC_F2,   KC_F3,   KC_F4, KC_F5, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,

    KC_COPY, KC_PASTE, KC_ESC,  KC_1,    KC_2,    KC_3, KC_4, KC_5,   KC_6,   KC_7,   KC_8, KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,  KC_INS, KC_HOME, KC_PGUP,  KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_CUT,  KC_CAPS,  KC_TAB,  KC_Q,    KC_W,    KC_E, KC_R, KC_T,   KC_Y,   KC_U,   KC_I, KC_O,    KC_P,    KC_LBRC, KC_RBRC,           KC_DEL, KC_END,  KC_PGDN,  KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    KC_NO,   KC_NO,    KC_NO,   KC_A,    KC_S,    KC_D, KC_F, KC_G,   KC_H,   KC_J,   KC_K, KC_L,    KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,           KC_UP,             KC_P4,   KC_P5,   KC_P6,   KC_EQL,
    KC_NO,   KC_APP,   KC_LSFT, KC_BSLS, KC_Z,    KC_X, KC_C, KC_V,   KC_B,   KC_N,   KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,           KC_LEFT,KC_DOWN, KC_RGHT,  KC_P1,   KC_P2,   KC_P3,
    KC_ESC,  KC_LGUI,  KC_LCTL,          KC_LALT,                     KC_SPC,               KC_RALT,                   KC_RCTL,                    KC_NO,                     KC_P0,   KC_PDOT, KC_PENT
    ),

        /* Keymap 1: Fn Layer
	 * ,-----------------------------------------------------------------------------------------------------------------------------.
     * |                 |email|pwd1 |pwd2 |pwd3 |___ |___ |___ |___ |___ |___ |___ |___ |                                           |
     * |-----------------------------------------------------------------------------------------------------------------------------|
     * |                 |___  |___  |___  |___  |___ |___ |___ |___ |___ |___ |___ |___ |                                           |
     * |-----------------------------------------------------------------------------------------------------------------------------|
     * |-----------------------------------------------------------------------------------------------------------------------------|
     * |___ |___ |   ___ |___|___|___|___|___|___|___|___|___|___|cmp1|___|  del  |   ___ |  ___ |  ___ |   ___ | ___ | ___ | ___ |  |
     * |-----------------------------------------------------------------------------------------------------------------------------|
     * |___ |___ |    ___  |___|___|___|___|___|___|___|up |___|pgu|___|___|      |   ___ |  ___ |  ___ |   ___ | ___ | ___ | ___ |  |
     * |--------------------------------------------------------------------       --------------------------------------------------|
     * |___ |___ |   FN1   |___|___|___|___|___|___|lft|dn |rgt|pgd|___|___| ___  |	      | ___  |          ___ | ___ | ___ | ___ |  |
     * |-----------------------------------------------------------------------------------------------------------------------------|
     * |___ |___ |    ___  |___|___|___|___|___|___|___|___|cmp2|___|___| ______  |  ___  | ___  | ___  |   ___ | ___ | ___ | |___|  |
     * |----------------------------------------------------------------------------------------------------------------------|   |  |
     * |___ |___ |    ___ |    |___ |            comp3          |___ |     |___   |       | FN1  |           |    ___ | ___ | |   |  |
     * `-----------------------------------------------------------------------------------------------------------------------------'
     */
KEYMAP(
                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______, _______, _______, _______, _______, _______, _______, _______,
                        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

    _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, KC_NO,	_______, KC_DEL,    _______, _______, _______,   _______, _______, _______, _______,
    _______, _______,  _______, KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______, _______, KC_UP,   _______,  KC_PGUP, _______, _______,			_______, _______, _______,   _______, _______, _______, _______,
    _______, _______,  _______, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, _______, _______, _______,            _______,            _______, _______, _______, _______,
    _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_NO,    _______, _______, _______,			_______, _______, _______,   _______, _______, _______,
    _______, _______,  _______,          _______,                            KC_NO,                 	_______,					_______,                     _______,                     _______, _______, _______
    ),
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
