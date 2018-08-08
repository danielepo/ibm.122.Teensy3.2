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

#define ___ NO
#define KC____ KC_NO


#define KEYMAP( \
                K7J,K6J,K6K,K5J,K4J,K4K,K3J,K2J,K2K,K1J,K0J,K0K,\
                K7K,K7L,K6L,K5K,K5L,K4L,K3K,K3L,K2L,K1K,K1L,K0L,\
K4B,K4C , K4E,K5E,K5F,K5G,K5H,K4H,K4I,K5I,K5M,K5N,K5O,K4O,K4M,K4P  ,  K4Q,K4R,K5Q,   K5P  ,K5R,K5S,K5A,\
K5B,K3B , K3C,K3E,K3F,K3G,K3H,K2H,K2I,K3I,K3M,K3N,K3O,K2O,K2M,K1P,              K6Q,K2P,K3Q,  K3P,K3R,K3S,K3A  ,\
K2B,K2C , K1C,K6D,K6E,K6F,K6H,K7H,K7I,K6I,K6M,K6N,K6O,K7O,K1O,                   K7Q,          K6P,K6R,K6S,K6A,\
K6B,K6C , K0D,K0E,Z,K1F,K1G,K1H,K0H,K0I,K1I,K1M,K1N,K0O,K1D,     K1A,K7T,K6T,K1B,K1R,K1S,K0T,\
K7C,K7B, K7A,   K0A,  K0B,K7D,  K0C,                         K7P,        K0R,     K0S\
) { \
{KC_##K0A ,KC_##K0B,KC_##K0C  ,KC_##K0D ,KC_##K0E ,KC_NO    ,KC_NO    ,KC_##K0H,KC_##K0I,KC_##K0J,KC_##K0K,KC_##K0L,KC_NO,KC_NO,KC_##K0O,KC_NO,KC_NO,KC_##K0R  ,KC_##K0S  ,KC_##K0T   },\
{KC_##K1A ,KC_##K1B,KC_##K1C  ,KC_##K1D ,KC_NO    ,KC_##K1F ,KC_##K1G ,KC_##K1H,KC_##K1I,KC_##K1J,KC_##K1K,KC_##K1L,KC_##K1M  ,KC_##K1N  ,KC_##K1O,KC_##K1P  ,KC_NO,KC_##K1R  ,KC_##K1S  ,KC_NO },\
{KC_NO    ,KC_##K2B,KC_##K2C  ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_##K2H,KC_##K2I,KC_##K2J,KC_##K2K,KC_##K2L,KC_##K2M  ,KC_NO,KC_##K2O,KC_NO,KC_##K2P  ,KC_NO,KC_NO,KC_NO },\
{KC_##K3A ,KC_##K3B,KC_##K3C  ,KC_NO    ,KC_##K3E ,KC_##K3F ,KC_##K3G ,KC_##K3H,KC_##K3I,KC_##K3J,KC_##K3K,KC_##K3L,KC_##K3M  ,KC_##K3N  ,KC_##K3O,KC_##K3P  ,KC_##K3Q  ,KC_##K3R  ,KC_##K3S  ,KC_NO },\
{KC_NO    ,KC_##K4B,KC_##K4C  ,KC_NO    ,KC_##K4E ,KC_NO    ,KC_NO    ,KC_##K4H,KC_##K4I,KC_##K4J,KC_##K4K,KC_##K4L,KC_##K4M  ,KC_NO,KC_##K4O,KC_##K4P  ,KC_##K4Q  ,KC_##K4R  ,KC_NO,KC_NO },\
{KC_##K5A ,KC_##K5B,KC_NO     ,KC_NO    ,KC_##K5E ,KC_##K5F ,KC_##K5G ,KC_##K5H,KC_##K5I,KC_##K5J,KC_##K5K,KC_##K5L,KC_##K5M  ,KC_##K5N  ,KC_##K5O,KC_##K5P  ,KC_##K5Q  ,KC_##K5R  ,KC_##K5S  ,KC_NO },\
{KC_##K6A ,KC_##K6B,KC_##K6C  ,KC_NO    ,KC_##K6D ,KC_##K6E ,KC_##K6F ,KC_##K6H,KC_##K6I,KC_##K6J,KC_##K6K,KC_##K6L,KC_##K6M  ,KC_##K6N  ,KC_##K6O,KC_##K6P  ,KC_##K6Q  ,KC_##K6R  ,KC_##K6S  ,KC_##K6T   },\
{KC_##K7A ,KC_##K7B,KC_##K7C  ,KC_##K7D ,KC_NO    ,KC_NO    ,KC_NO    ,KC_##K7H,KC_##K7I,KC_##K7J,KC_##K7K,KC_##K7L,KC_NO,KC_NO,KC_##K7O,KC_##K7P  ,KC_##K7Q  ,KC_NO,KC_NO,KC_##K7T   }\
},

static const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      KEYMAP(
     /* Keymap 0: Default Layer
     * ,---------------------------------------------------------------------------------------------------------------------------------.
     * |                 |PrnSc|ScrLk|Pause|Lock |    | << |Play|Stop| >> |Mute|Vol-|Vol+|                                               |
     * |                 |  F1 |  F2 |  F3 |  F4 |  F5|  F6|  F7|  F8|  F9| F10| F11| F12|                                               |
     * |---------------------------------------------------------------------------------------------------------------------------------|
     * |Copy|Pste|    | `  |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = | Bspc|   | INS|HOME|PGUP|   |NLCK| PSLS|PAST|PMNS|
     * |Cut |Caps|    |Tab |  Q |  W |  E |  R |  T |  Y |  U |  I |  O |  P |  [ | ]  |Enter|   | DEL| END|PGDN|   | P7 |  P8 |  P9|PPLS|
     * |BT< |BT>+|    |FN1 |  A |  S |  D |  F |  G |  H |  J |  K |  L |  ; |  ' | \    |            | UP |        | P4 |  P5 |  P6|  = |
     * |MC1 |App |    |Shft|  \ |  Z |  X |  C |  V |  B |  N |  M |  , |  . |  / | *  |Shift|   |LEFT|DOWN|RGHT|   | P1 |  P2 |  P3|PENT|
     * |Esc |GUI |    |Ctrl|    |Alt |            Space                 | Alt|    |Ctrl|              | FN |        | P0       |PDOT|  * |
     * `---------------------------------------------------------------------------------------------------------------------------------'
     */
                              PSCR, SLCK, PAUS,NO,  NO,  MPRV,MPLY,MSTP,MNXT, MUTE, VOLD, VOLU,
                              F1,   F2,   F3,  F4,  F5,  F6,  F7,  F8,  F9,   F10,  F11,  F12,

  FN0 , ESC    , 0    ,  1  ,  2  ,  3  ,  4  ,  5  ,  6  ,  7  ,  8  ,  9  ,  0  , MINS, EQL , BSPC  ,  INS , HOME, PGUP  ,    NLCK, PSLS, PAST, PMNS,
  FN1 , CAPS   , TAB  ,  Q  ,  W  ,  E  ,  R  ,  T  ,  Y  ,  U  ,  I  ,  O  ,  P  , LBRC, RBRC, ENT   ,  DEL , END , PGDN  ,    P7  , P8  , P9  , PPLS,
  FN2 , ___    , FN1  ,  A  ,  S  ,  D  ,  F  ,  G  ,  H  ,  J  ,  K  ,  L  , SCLN, QUOT, BSLS,                UP  ,            P4  , P5  , P6  , EQL ,
  FN3 , MENU   , LSFT , BSLS,  Z  ,  X  ,  C  ,  V  ,  B  ,  N  ,  M  , COMM, DOT , SLSH,       RSFT  ,  LEFT, DOWN, RGHT  ,    P1  , P2  , P3  , PENT,
  FN4 , RGUI   , LCTL ,       LALT,             SPC ,                         RALT,             RCTL  ,         NO ,            P0        ,PDOT
)

 KEYMAP(
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
                 ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                 ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ ,

 FN0 , ___   ,   1   , F1  , F2  , F3  , F4  , F5  , F6  , F7  , F8  , F9  , F10 , F11 , F12 , ___   ,   ___ , ___ , ___  ,  ___ , ___ , ___ , ___ ,
 FN1 , ___   ,   ___ , ___ , ___ , ___ , ___ , ___ , ___ , PGUP, HOME, UP  , END , DEL , ___ , ___   ,   ___ , ___ , ___  ,  ___ , ___ , ___ , ___ ,
 FN2 , ___   ,   FN1 , LALT, ___ , LSFT, LCTL, ___ , ___ , PGDN, LEFT, DOWN, RGHT, BSPC, ___ ,                 ___        ,  ___ , ___ , ___ , ___ ,
 FN3 , ___   ,   ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ ,           ___ , ___ , ___  ,  ___ , ___ , ___ , ___ ,
 FN4 , ___   ,   ___ ,       ___ ,             ENT ,                         ___ ,       ___ ,                 ___ ,         ___ ,       ___
)

 KEYMAP(
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
                 ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                 ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ ,

 FN0 , ___   ,   2   , ___ , ___ , ___ , ___ , ___ , ___ , P7  , P8  , P9  , PMNS, ___ , ___ , ___   ,   ___ , ___ , ___  ,  ___ , ___ , ___ , ___ ,
 FN1 , ___   ,   ___ , ___ , ___ , ___ , ___ , ___ , ___ , P4  , P5  , P6  , PPLS, ___ , ___ , ___   ,   ___ , ___ , ___  ,  ___ , ___ , ___ , ___ ,
 FN2 , ___   ,   FN0 , ___ , ___ , ___ , ___ , ___ , ___ , P1  , P2  , P3  , PAST, ___ , ___ ,                 ___        ,  ___ , ___ , ___ , ___ ,
 FN3 , ___   ,   ___ , ___ , ___ , ___ , ___ , ___ , ___ , P0  , PDOT, PSLS, ___ , ___ , ___ ,           ___ , ___ , ___  ,  ___ , ___ , ___ , ___ ,
 FN4 , ___   ,   ___ ,       ___ ,             ENT ,                         ___ ,       ___ ,                 ___ ,         ___ ,       ___
)

 KEYMAP(
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
                 ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                 ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ ,

 FN0 , ___   ,   3   , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___   ,   ___ , ___ , ___  ,  ___ , ___ , ___ , ___ ,
 FN1 , ___   ,   ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___   ,   ___ , ___ , ___  ,  ___ , ___ , ___ , ___ ,
 FN2 , ___   ,   FN0 , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ ,                 ___        ,  ___ , ___ , ___ , ___ ,
 FN3 , ___   ,   ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ ,           ___ , ___ , ___  ,  ___ , ___ , ___ , ___ ,
 FN4 , ___   ,   ___ ,       ___ ,             ___ ,                         ___ ,       ___ ,                 ___ ,         ___ ,       ___
)

 KEYMAP(
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
                 ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                 ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ ,

 FN0 , ___   ,   4   , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___   ,   ___ , ___ , ___  ,  ___ , ___ , ___ , ___ ,
 FN1 , ___   ,   ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___   ,   ___ , ___ , ___  ,  ___ , ___ , ___ , ___ ,
 FN2 , ___   ,   FN0 , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ ,                 ___        ,  ___ , ___ , ___ , ___ ,
 FN3 , ___   ,   ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ ,           ___ , ___ , ___  ,  ___ , ___ , ___ , ___ ,
 FN4 , ___   ,   ___ ,       ___ ,             ___ ,                         ___ ,       ___ ,                 ___ ,         ___ ,       ___
)
 };
// #define AC_L3       ACTION_LAYER_MOMENTARY(3)
// #define AC_L4       ACTION_LAYER_MOMENTARY(4)
// #define AC_LS_2     ACTION_LAYER_MODS(2, MOD_LSFT)
// #define AC_RS_2     ACTION_LAYER_MODS(2, MOD_RSFT)
// #define AC_TGL1     ACTION_LAYER_TOGGLE(1)
const action_t  fn_actions[] = {
    [0]  = ACTION_LAYER_TOGGLE(0),
    [1]  = ACTION_LAYER_TOGGLE(1),
    [2]  = ACTION_LAYER_TOGGLE(2),
    [3]  = ACTION_LAYER_TOGGLE(3),
    [4]  = ACTION_LAYER_TOGGLE(4),
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
