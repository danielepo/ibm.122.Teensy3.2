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
                   K709,K609,K60A,K509,K409,K40A,K309,K209,K20A,K009,K109,K10A,\
                   K70A,K70B,K60B,K50A,K50B,K40B,K30A,K30B,K20B,K00A,K00B,K10B,\
  K401,K402 , K404,K504,K505,K506,K507,K407,K408,K508,K50C,K50D,K50E,K40E,K40C,K40F , K410,K411,K510 , K50F,K511,K512,K500,\
  K501,K301 , K302,K304,K305,K306,K307,K207,K208,K308,K30C,K30D,K30E,K20F,K20C,K00F , CANC,K210,K310 , K30F,K311,K312,K300,\
  K201,K202 , K002,K604,K605,K606,K607,K707,K708,K608,K60C,K60D,K60E,K70E,K00E,            K710,       K60F,K611,K612,K600,\
  K601,K602 , K103,K104,K004,K005,K006,K007,K107,K108,K008,K00C,K00D,K10E,K003,       K000,K713,K613 , K001,K011,K012,K113,\
  K702,K701 , K700,     K100,               K101,               K703,     K102,            K70F,       K111,          K112\
) { \
  {KC_##K000,KC_##K001,KC_##K002,KC_##K003,KC_##K004,KC_##K005,KC_##K006,KC_##K007,KC_##K008,KC_##K009,KC_##K00A,KC_##K00B,KC_##K00C,KC_##K00D,KC_##K00E,KC_##K00F,KC_NO    ,KC_##K011,KC_##K012,KC_NO} ,\
  {KC_##K100,KC_##K101,KC_##K102,KC_##K103,KC_##K104,KC_NO    ,KC_NO    ,KC_##K107,KC_##K108,KC_##K109,KC_##K10A,KC_##K10B,KC_NO    ,KC_NO    ,KC_##K10E,KC_NO    ,KC_NO    ,KC_##K111,KC_##K112,KC_##K113} ,\
  {KC_NO    ,KC_##K201,KC_##K202,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_##K207,KC_##K208,KC_##K209,KC_##K20A,KC_##K20B,KC_##K20C,KC_NO    ,KC_##K20F,KC_NO    ,KC_##K210,KC_NO    ,KC_NO    ,KC_NO} ,\
  {KC_##K300,KC_##K301,KC_##K302,KC_NO    ,KC_##K304,KC_##K305,KC_##K306,KC_##K307,KC_##K308,KC_##K309,KC_##K30A,KC_##K30B,KC_##K30C,KC_##K30D,KC_##K30E,KC_##K30F,KC_##K310,KC_##K311,KC_##K312,KC_NO} ,\
  {KC_NO    ,KC_##K401,KC_##K402,KC_NO    ,KC_##K404,KC_NO    ,KC_NO    ,KC_##K407,KC_##K408,KC_##K409,KC_##K40A,KC_##K40B,KC_##K40C,KC_NO    ,KC_##K40E,KC_##K40F,KC_##K410,KC_##K411,KC_NO    ,KC_NO} ,\
  {KC_##K500,KC_##K501,KC_NO    ,KC_NO    ,KC_##K504,KC_##K505,KC_##K506,KC_##K507,KC_##K508,KC_##K509,KC_##K50A,KC_##K50B,KC_##K50C,KC_##K50D,KC_##K50E,KC_##K50F,KC_##K510,KC_##K511,KC_##K512,KC_NO} ,\
  {KC_##K600,KC_##K601,KC_##K602,KC_NO    ,KC_##K604,KC_##K605,KC_##K606,KC_##K607,KC_##K608,KC_##K609,KC_##K60A,KC_##K60B,KC_##K60C,KC_##K60D,KC_##K60E,KC_##K60F,KC_NO    ,KC_##K611,KC_##K612,KC_##K613} ,\
  {KC_##K700,KC_##K701,KC_##K702,KC_##K703,KC_NO    ,KC_NO    ,KC_NO    ,KC_##K707,KC_##K708,KC_##K709,KC_##K70A,KC_##K70B,KC_NO    ,KC_NO    ,KC_##K70E,KC_##K70F,KC_##K710,KC_NO    ,KC_NO    ,KC_##K713}\
}

#define _______ KC_TRNS

static const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      KEYMAP( \
//      /* Keymap 0: Default Layer
//      * ,---------------------------------------------------------------------------------------------------------------------------------.
//      * |                 |PrnSc|ScrLk|Pause|Lock |    | << |Play|Stop| >> |Mute|Vol-|Vol+|                                               |
//      * |                 |  F1 |  F2 |  F3 |  F4 |  F5|  F6|  F7|  F8|  F9| F10| F11| F12|                                               |
//      * |---------------------------------------------------------------------------------------------------------------------------------|
//      * |Copy|Pste|    | `  |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = | Bspc|   | INS|HOME|PGUP|   |NLCK| PSLS|PAST|PMNS|
//      * |Cut |Caps|    |Tab |  Q |  W |  E |  R |  T |  Y |  U |  I |  O |  P |  [ | ]  |Enter|   | DEL| END|PGDN|   | P7 |  P8 |  P9|PPLS|
//      * |BT< |BT>+|    |FN1 |  A |  S |  D |  F |  G |  H |  J |  K |  L |  ; |  ' | \    |            | UP |        | P4 |  P5 |  P6|  = |
//      * |MC1 |App |    |Shft|  \ |  Z |  X |  C |  V |  B |  N |  M |  , |  . |  / | *  |Shift|   |LEFT|DOWN|RGHT|   | P1 |  P2 |  P3|PENT|
//      * |Esc |GUI |    |Ctrl|    |Alt |            Space                 | Alt|    |Ctrl|              | FN |        | P0       |PDOT|  * |
//      * `---------------------------------------------------------------------------------------------------------------------------------'
//      */
                              PSCR, SLCK, PAUS,NO,  NO,  MPRV,MPLY,MSTP,MNXT, MUTE, VOLD, VOLU,
                              F1,   F2,   F3,  F4,  F5,  F6,  F7,  F8,  F9,   F10,  F11,  F12,

  FN0  , ESC    , ESC  ,  1  ,  2  ,  3  ,  4  ,  5  ,  6  ,  7  ,  8  ,  9  ,  0  , MINS, EQL , BSPC  ,  INS , HOME, PGUP  ,    NLCK, PSLS, PAST, PMNS,
  FN1  , CAPS   , TAB  ,  Q  ,  W  ,  E  ,  R  ,  T  ,  Y  ,  U  ,  I  ,  O  ,  P  , LBRC, RBRC, ENT   ,  DEL , END , PGDN  ,    P7  , P8  , P9  , PPLS,
  FN2  , NO     , NO   ,  A  ,  S  ,  D  ,  F  ,  G  ,  H  ,  J  ,  K  ,  L  , SCLN, QUOT, BSLS,                UP  ,            P4  , P5  , P6  , EQL ,
  FN3  , NO     , LSFT , BSLS,  Z  ,  X  ,  C  ,  V  ,  B  ,  N  ,  M  , COMM, DOT , SLSH,       RSFT  ,  LEFT, DOWN, RGHT  ,    P1  , P2  , P3  , PENT,
  FN4  , NO     , LCTL ,       LALT,             SPC ,                         RALT,             RCTL  ,         NO ,            P0        ,PDOT
),


 };

const action_t  fn_actions[] = {
    [0]  = ACTION_LAYER_MOMENTARY(1),
    [1]  = ACTION_LAYER_MOMENTARY(1),
    [2]  = ACTION_LAYER_MOMENTARY(1),
    [3]  = ACTION_LAYER_MOMENTARY(1),
    [4]  = ACTION_LAYER_MOMENTARY(1),
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
