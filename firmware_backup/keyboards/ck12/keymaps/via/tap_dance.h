#pragma once

#include QMK_KEYBOARD_H

enum {
    TD_LAYER_SWITCH,
};

#define TD_LS TD(TD_LAYER_SWITCH)

extern tap_dance_action_t tap_dance_actions[];
