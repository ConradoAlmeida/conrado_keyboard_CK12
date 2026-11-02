#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_3x4(
        LCTL(KC_C),  LCTL(KC_X),  LCTL(KC_V),  LCTL(KC_Z),
        LCTL(KC_S),  LCTL(KC_A),  KC_TAB,      KC_ENT,
        KC_UNDO,     KC_REDO,     KC_SPC,      KC_ESC
    ),
};
