#include QMK_KEYBOARD_H

enum {
    TD_LAYER_SWITCH,
};

#define TD_LS TD(TD_LAYER_SWITCH)

void td_layer_on_dance(tap_dance_state_t *state, void *user_data) {
    layer_off(2);
    layer_off(1);
    layer_off(0);
    if (state->count == 1) {
        layer_on(0);
    } else if (state->count == 2) {
        layer_on(1);
    } else if (state->count >= 3) {
        layer_on(2);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_LAYER_SWITCH] = ACTION_TAP_DANCE_FN(td_layer_on_dance),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        TD_LS,      LCTL(KC_X), LCTL(KC_C), LCTL(KC_V),
        KC_BSPC,    KC_ENT,     KC_TAB,     KC_ESC,
        KC_MUTE,    KC_VOLD,    KC_VOLU,    KC_MPLY
    ),
    [1] = LAYOUT(
        KC_TRNS,    KC_F14,     KC_F15,     KC_F16,
        KC_F17,     KC_F18,     KC_F19,     KC_F20,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [2] = LAYOUT(
        KC_TRNS,    KC_F22,     KC_F23,     KC_F24,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
};
