#include QMK_KEYBOARD_H

enum custom_keycodes {
    AUTO_CLICK_250MS = SAFE_RANGE, // User0 no Vial: duplo-click a cada 250ms
    AUTO_CLICK_500MS,              // User1 no Vial: duplo-click a cada 500ms
    AUTO_CLICK_1000MS,             // User2 no Vial: duplo-click a cada 1s
};

#define DOUBLE_CLICK_GAP_MS 40 // intervalo entre os 2 clicks do duplo (fixo)

static bool auto_click_on = false;
static uint16_t auto_click_delay_ms = 500; // pausa ENTRE duplos-clicks
static uint8_t dbl_step = 0; // 0 = esperando pausa (1o click), 1 = esperando gap (2o click)
static uint32_t auto_click_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint16_t new_delay = 0;
    // User0..2 no Vial novo (0x7E40+) e no Vial antigo (QK_KB_0.., 0x7E00+)
    if (keycode == AUTO_CLICK_250MS || keycode == QK_KB_0) {
        new_delay = 250;
    } else if (keycode == AUTO_CLICK_500MS || keycode == QK_KB_1) {
        new_delay = 500;
    } else if (keycode == AUTO_CLICK_1000MS || keycode == QK_KB_2) {
        new_delay = 1000;
    } else {
        return true;
    }
    if (!record->event.pressed) {
        return false;
    }
    if (auto_click_on && auto_click_delay_ms == new_delay) {
        auto_click_on = false; // mesma tecla de novo = desliga
    } else {
        auto_click_on = true; // liga ou troca a pausa mantendo ligado
        auto_click_delay_ms = new_delay;
        dbl_step = 0;
        tap_code(KC_MS_BTN1); // feedback imediato: 1o click do duplo
        dbl_step = 1;
    }
    auto_click_timer = timer_read32();
    return false;
}

void matrix_scan_user(void) {
    if (!auto_click_on) {
        return;
    }
    if (dbl_step == 0 && timer_elapsed32(auto_click_timer) > auto_click_delay_ms) {
        tap_code(KC_MS_BTN1); // 1o click do duplo
        dbl_step = 1;
        auto_click_timer = timer_read32();
    } else if (dbl_step == 1 && timer_elapsed32(auto_click_timer) > DOUBLE_CLICK_GAP_MS) {
        tap_code(KC_MS_BTN1); // 2o click do duplo
        dbl_step = 0;
        auto_click_timer = timer_read32();
    }
}

static void install_default_tap_dance(void) {
    vial_tap_dance_entry_t default_td = { TO(0), TO(2), TO(1), TO(2), TAPPING_TERM };
    dynamic_keymap_set_tap_dance(0, &default_td);
}

void eeconfig_init_user(void) {
    install_default_tap_dance();
}

static bool td_entry_is_empty(vial_tap_dance_entry_t *td) {
    return (td->on_tap == KC_NO || td->on_tap == 0xFFFF) &&
           (td->on_hold == KC_NO || td->on_hold == 0xFFFF) &&
           (td->on_double_tap == KC_NO || td->on_double_tap == 0xFFFF) &&
           (td->on_tap_hold == KC_NO || td->on_tap_hold == 0xFFFF);
}

void keyboard_post_init_user(void) {
    vial_tap_dance_entry_t td;
    if (dynamic_keymap_get_tap_dance(0, &td) == 0 && td_entry_is_empty(&td)) {
        install_default_tap_dance();
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        TD(0),      LCTL(KC_X), LCTL(KC_C), LCTL(KC_V),
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
