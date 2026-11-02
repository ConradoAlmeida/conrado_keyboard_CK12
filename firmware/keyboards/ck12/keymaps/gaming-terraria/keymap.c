#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_3x4(
        KC_W,        KC_E,        KC_Q,        KC_ESC,
        KC_A,        KC_S,        KC_D,        KC_LSFT,
        KC_1,        KC_2,        KC_3,        KC_4
    ),
};
