/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

#include QMK_KEYBOARD_H

uint16_t copy_paste_timer;

// List of layers; COLEMAK_N set to default layer
enum layers {
    _COLEMAK_N = 0,
    _SYMNUM,
    _FKEYS,
    _NUMNAV,
    _KBCONFIG,
};

// Aliases for readability
#define CLMKN DF(_COLEMAK_N)
#define SYMNUM MO(_SYMNUM)
#define FKEYS OSL(_FKEYS)
#define NAV MO(_NUMNAV)
#define KBCONF MO(_KBCONFIG)

enum custom_keycodes { KC_CCCV = SAFE_RANGE };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    /*
     * Base Layer: Colemak_N
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * | Tab    |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ?  ! |ShftTab |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * | LShift |   A  |   R  |   S  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   O  | RShift |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * | LCtrl  |   Z  |   X  |   C  |   D  |   V  |  ( [ |VolMut|  |AltTab| ) ]  |   K  |   H  | ,  ; | . :  | '  " | LAlt   |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        | LGUI | Fkeys|  Nav | Space|Enter |  | Esc  | Bksp |SynNum| App  |KBConf|
     *                        |      |      |      |      |      |  |      |  Del |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */

    [_COLEMAK_N] = LAYOUT(KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_QUES, LSFT(KC_TAB), KC_LSFT, KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, KC_RSFT, KC_LCTL, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_LPRN, KC_MUTE, LALT(KC_TAB), KC_RPRN, KC_K, KC_H, KC_COMM, KC_DOT, KC_QUOTE, KC_LALT, KC_LGUI, FKEYS, NAV, KC_SPC, KC_ENT, KC_ESC, KC_BSPC, SYMNUM, KC_APP, KBCONF),

    /*
     * Toggle: SymNum
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |  Esc   |   ~  |   |  |   #  |   .  |   $  |                              |   /  |   7  |   8  |   9  |   -  |        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        |   \  |   _  |   @  |   ,  |   %  |                              |   *  |   4  |   5  |   6  |   +  |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |   `  |   ^  |   &  |   {  |   }  |   <  |      |  |      |   >  |   0  |   1  |   2  |   3  |   =  |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
    [_SYMNUM] = LAYOUT(KC_ESC, KC_TILD, KC_PIPE, KC_HASH, KC_DOT, KC_DLR, KC_SLSH, KC_7, KC_8, KC_9, KC_MINS, _______, _______, KC_BSLS, KC_UNDS, KC_AT, KC_COMM, KC_PERC, KC_ASTR, KC_4, KC_5, KC_6, KC_PLUS, _______, _______, KC_GRV, KC_CIRC, KC_AMPR, KC_LCBR, KC_RCBR, KC_LT, _______, _______, KC_GT, KC_0, KC_1, KC_2, KC_3, KC_EQL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    /*
     * Momentary layer: NumNav
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |  Esc   |   /  |   7  |   8  |   9  |   -  |                              |  PgU | Home |   U  |  End |      |        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        |   *  |   4  |   5  |   6  |   +  |                              |  PgD |   L  |   D  |   R  |      |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |   0  |   1  |   2  |   3  |   =  |Alt+F4|      |  |      |      |      |WBack |WRefr | WFwd |WSrch |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
    [_NUMNAV] = LAYOUT(KC_ESC, KC_SLSH, KC_7, KC_8, KC_9, KC_MINS, KC_PGUP, KC_HOME, KC_UP, KC_END, _______, _______, _______, KC_ASTR, KC_4, KC_5, KC_6, KC_PLUS, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_0, KC_1, KC_2, KC_3, KC_EQL, LALT(KC_F4), _______, _______, _______, _______, KC_WBAK, KC_WREF, KC_WFWD, KC_WSCH, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    /*
     * One shot layer: Fkeys
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |        |  F9  | F10  | F11  | F12  | ScLk |                              | PrtSc|      |Maxmze|      |      |        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        |  F5  |  F6  |  F7  |  F8  | CapLk|                              |SPrtSc|ScrnL |Minmze|ScrnR |      |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |  F1  |  F2  |  F3  |  F4  |Insert|      |      |  |      |      |      |      |      |      |      |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
    [_FKEYS] = LAYOUT(_______, KC_F9, KC_F10, KC_F11, KC_F12, KC_SCRL, KC_PSCR, _______, LGUI(KC_UP), _______, _______, _______, _______, KC_F5, KC_F6, KC_F7, KC_F8, KC_CAPS, LSFT(KC_PSCR), LSG(KC_LEFT), LGUI(KC_DOWN), LSG(KC_RGHT), _______, _______, _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_INS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    /*
     * Held layer: KBConfig
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |        |      |      |      |      |      |                              |Breath|Grdnt |Swirl |Snake | Plain|        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |                              | Tog  |  Sai | Hui  |  Vai | Mod  |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |      |  |      |      |Knight|  Sad | Hud  |  Vad | Rmod |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
    [_KBCONFIG] = LAYOUT(_______, _______, _______, _______, _______, _______, RGB_M_B, RGB_M_G, RGB_M_SW, RGB_M_SN, RGB_M_P, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_M_K, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    // clang-format on
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CCCV: // One key copy/paste
            if (record->event.pressed) {
                copy_paste_timer = timer_read();
            } else {
                if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) { // Hold, copy
                    tap_code16(LCTL(KC_C));
                } else { // Tap, paste
                    tap_code16(LCTL(KC_V));
                }
            }
            break;
    }
    return true;
}


#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // Niscient logo and version information
        // clang-format off
        static const char PROGMEM niscient_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
            // clang-format on

            oled_write_P(niscient_logo, false);
        oled_write_P(PSTR("Kyria rev3.0.007\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case _COLEMAK_N:
                oled_write_P(PSTR("Colemak-N\n"), false);
                break;
            case _SYMNUM:
                oled_write_P(PSTR("SymNum\n"), false);
                break;
            case _FKEYS:
                oled_write_P(PSTR("FKeys\n"), false);
                break;
            case _NUMNAV:
                oled_write_P(PSTR("NumNav\n"), false);
                break;
            case _KBCONFIG:
                oled_write_P(PSTR("KBConfig\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // clang-format off
        static const char PROGMEM fox_logo[] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xf0, 0xf0,
            0xf8, 0xf8, 0xe8, 0xe8, 0xcc, 0xc4, 0xa4, 0x94, 0x9c, 0xcc, 0xe0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xfc, 0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xf8, 0xf0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf8, 0xfe, 0xff, 0xff, 0xf3, 0xf9, 0xf9, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x8f, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x03, 0x1f, 0x3f, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x1f, 0x1f, 0x3f, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x0f, 0x09, 0x13, 0x13, 0x33, 0x3f, 0x7e, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x07, 0x0f, 0x0f, 0x1f, 0x1f, 0x1f, 0x3f, 0x3f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xe7, 0x0f, 0x1f, 0x3f, 0x3f, 0x1f, 0x1f, 0x0f, 0x8f, 0xcf, 0xc7, 0x63, 0x20, 0x30, 0x00, 0x01, 0x01, 0x81, 0xc1, 0xe1, 0xf1, 0x79, 0x38, 0x1c, 0x0e,
            0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x01, 0x00, 0x00, 0x18, 0x0c, 0x06, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x3f, 0x3f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x1c, 0x18, 0x30, 0x71, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };
        // clang-format on
        oled_write_raw_P(fox_logo, sizeof(fox_logo));
    }
    return false;
}
#endif

/*
* Enable and program the 2 rotary encoders
* In default case
*  Encoder 0 = volume
*  Encoder 1 = window switching (alt-tab)
* In SYSNUM case
*  Encoder 0 = PgUp/PgDn
*  Encoder 1 = no change
*/

#ifdef ENCODER_ENABLE

    bool     is_alt_tab_active = false;
    uint16_t alt_tab_timer     = 0;

    void matrix_scan_user(void) {
        if (is_alt_tab_active) {
            if (timer_elapsed(alt_tab_timer) > 2000) {
                unregister_code(KC_LALT);
                is_alt_tab_active = false;
            }
        }
    }

    bool encoder_update_user(uint8_t index, bool clockwise) {
        if (index == 0) {
            // For the LH encoder
            switch (biton32(layer_state)) {
                case _SYMNUM:
                    // Scrolling with PageUp and PgDn.
                    if (clockwise) {
                        tap_code(KC_PGDN);
                    } else {
                        tap_code(KC_PGUP);
                    }
                    break;
                default:
                    // Volume control.
                    if (clockwise) {
                        tap_code(KC_VOLU);
                    } else {
                        tap_code(KC_VOLD);
                    }
                    break;
            }
        } else if (index == 1) {
            // For the RH encoder
            switch (biton32(layer_state)) {
                default:
                    // Switch between windows on Windows with alt tab.
                    if (clockwise) {
                        if (!is_alt_tab_active) {
                            is_alt_tab_active = true;
                            register_code(KC_LALT);
                        }
                        alt_tab_timer = timer_read();
                        tap_code16(KC_TAB);
                    } else {
                        tap_code16(S(KC_TAB));
                    }
                    break;
            }
        }

        return false;
    }
#endif

    // Set up the key overrides
    const key_override_t delete_key_override      = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
    const key_override_t exclamation_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUES, KC_EXLM);
    const key_override_t semicolon_key_override   = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);
    const key_override_t colon_key_override       = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLN);
    const key_override_t lsquare_key_override     = ko_make_basic(MOD_MASK_SHIFT, KC_LPRN, KC_LBRC);
    const key_override_t rsquare_key_override     = ko_make_basic(MOD_MASK_SHIFT, KC_RPRN, KC_RBRC);
    const key_override_t lcurly_key_override      = ko_make_basic(MOD_MASK_CTRL, KC_LPRN, KC_LCBR);
    const key_override_t rcurly_key_override      = ko_make_basic(MOD_MASK_CTRL, KC_RPRN, KC_RCBR);

    // Globally define key override array
    const key_override_t *key_overrides[] = {
        &delete_key_override,
        &exclamation_key_override,
        &semicolon_key_override,
        &colon_key_override,
        &lsquare_key_override,
        &rsquare_key_override,
        &lcurly_key_override,
        &rcurly_key_override
    };
