/* Copyright 2022 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef RGB_MATRIX_ENABLE

// The number of LEDs connected
#    define RGB_MATRIX_LED_COUNT 62
#    define DRIVER_LED_TOTAL 62

// show this is a splitkb
#    define RGB_MATRIX_SPLIT \
        { 31, 31 }
#    define SPLIT_TRANSPORT_MIRROR

// set up matrix params
#    define RGB_MATRIX_KEYPRESSES                                   // reacts to keypresses
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true                     // turn off effects when suspended
#    define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#    define RGB_MATRIX_LED_FLUSH_LIMIT 16                           // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#    undef RGB_MATRIX_MAXIMUM_BRIGHTNESS                            // is preset in info_config.h:49
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150                       // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
#    define RGB_MATRIX_HUE_STEP 8
#    define RGB_MATRIX_SAT_STEP 8
#    define RGB_MATRIX_VAL_STEP 8
#    define RGB_MATRIX_SPD_STEP 10

#endif

#define LED_CAPS_LOCK_PIN 24
#define LED_PIN_ON_STATE 0