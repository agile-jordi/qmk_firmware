/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define SSD1306OLED

#define USE_SERIAL_PD2

// The MT is also MOD if both keys are held longer than the TAPPING_TERM, even if the MT key is relased first
// And MT down + k down + MT up + k up acts as tap unless both keys are held longer than the TAPPING_TERM
// See https://beta.docs.qmk.fm/using-qmk/software-features/tap_hold#ignore-mod-tap-interrupt
// See https://precondition.github.io/home-row-mods#ignore-mod-tap-interrupt
#define IGNORE_MOD_TAP_INTERRUPT
// https://beta.docs.qmk.fm/using-qmk/software-features/tap_hold#tapping-term
#define TAPPING_TERM 220

// When a user holds an MT key after tapping it, make it MOD instead of tapping for key repeat
// See https://beta.docs.qmk.fm/using-qmk/software-features/tap_hold#tapping-force-hold
// See https://precondition.github.io/home-row-mods#tapping-force-hold
#define TAPPING_FORCE_HOLD

// The MT is MOD if a second key is tapped and releases before MT, even if within TAPPING_TERM
// See https://beta.docs.qmk.fm/using-qmk/software-features/tap_hold#permissive-hold
// See https://precondition.github.io/home-row-mods#permissive-hold
#define PERMISSIVE_HOLD


#define TAP_HOLD_CAPS_DELAY 0

#define ONESHOT_TAP_TOGGLE 3
#define ONESHOT_TIMEOUT 2000



#ifdef RGBLIGHT_ENABLE
    #undef RGBLED_NUM
    #define RGBLIGHT_ANIMATIONS
    #define RGBLED_NUM 27
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif
