#include "tap_dance.h"

void td_layer_on_dance(tap_dance_state_t *state, void *user_data) {
    layer_clear();
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
