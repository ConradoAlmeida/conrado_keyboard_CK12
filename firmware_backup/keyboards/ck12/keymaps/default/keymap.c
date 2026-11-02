#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V),
        KC_BSPC,    KC_ENT,     KC_TAB,     KC_ESC,
        KC_MUTE,    KC_VOLD,    KC_VOLU,    KC_MPLY
    ),
    [1] = LAYOUT(
        KC_F13,     KC_F14,     KC_F15,     KC_F16,
        KC_F17,     KC_F18,     KC_F19,     KC_F20,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
};
