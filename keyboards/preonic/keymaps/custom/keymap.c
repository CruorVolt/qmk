#include "preonic.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum preonic_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _GAMES,
  _GAMES_MOD,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = {
  {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12},
  {KC_ESC,        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_TAB,        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {OSM(MOD_LSFT), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
  {KC_LCTL,       KC_LGUI, KC_LEAD, M(0),    KC_SPC,  RAISE,   LOWER,   KC_SPC,  M(2),    M(1),    KC_LALT, M(3)}
},

[_LOWER] = {
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_LPRN, KC_RPRN, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

[_RAISE] = {
  {_______, _______, _______, _______, _______, _______, _______, _______, _______,     _______,     _______,  _______},
  {KC_TILD, KC_1,    KC_2,       KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,        KC_9,        KC_0,     KC_DELETE},
  {_______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,       KC_RIGHT,    _______,  KC_BSLASH},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_LBRACKET, KC_RBRACKET, KC_MINUS, KC_EQUAL},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______,     _______,     _______,  _______}
},

[_GAMES] = {
  {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12},
  {KC_ESC,        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
  {KC_LCTL, KC_F1,   KC_LEAD, KC_LALT, KC_SPC,  MO(_GAMES_MOD),   KC_F3,   KC_SPC,  KC_HOME, KC_END,  KC_F4,    M(4)}
},

[_GAMES_MOD] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    KC_BSPC},
  {KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    KC_7},
  {KC_F8,   _______, _______, _______, KC_F9,   _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______},
  {KC_F6,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______,  _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, XXXXXXX}
},

[_ADJUST] = {
  {RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}


};

#ifdef AUDIO_ENABLE
float tone_coin[][2]    = SONG(MARIO_THEME);
float tone_ring[][2]    = SONG(MARIO_GAMEOVER);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_QWERTY);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
      }
    return true;
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    case 0: // alt-tab hold thing
      if (record->event.pressed) {
        layer_on(_RAISE);
        return MACRO( I(10), D(LALT), T(TAB), END);
      } else {
        layer_off(_RAISE);
        return MACRO( I(10), U(LALT), END);
      }
      break;
    case 1: //browser tab right
      if (record->event.pressed) {
        return MACRO( I(10), D(LCTRL), T(TAB), U(LCTRL), END);
      }
      break;
    case 2: //browser tab left
      if (record->event.pressed) {
        return MACRO( I(10), D(LCTRL), D(LSHIFT), T(TAB), U(LCTRL), U(LSHIFT), END);
      }
      break;
    case 3: //_GAMES
      if (record->event.pressed) {
        layer_on(_GAMES);
        PLAY_NOTE_ARRAY(tone_coin, false, 0);
      }
      break;
    case 4: //_QWERTY
      if (record->event.pressed) {
        layer_off(_GAMES);
        PLAY_NOTE_ARRAY(tone_ring, false, 0);
      }
      break;
  }
  return MACRO_NONE;
};

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    //Spell out keycodes to send them

    SEQ_ONE_KEY(KC_I) {
      register_code(KC_INSERT);
      unregister_code(KC_INSERT);
    }

    SEQ_ONE_KEY(KC_H) {
        register_code(KC_HOME);
        unregister_code(KC_HOME);
    }

    SEQ_ONE_KEY(KC_D) {
        register_code(KC_DELETE);
        unregister_code(KC_DELETE);
    }

    SEQ_ONE_KEY(KC_E) {
        register_code(KC_END);
        unregister_code(KC_END);
    }

    SEQ_ONE_KEY(KC_P) {
        register_code(KC_PSCREEN);
        unregister_code(KC_PSCREEN);
    }

    SEQ_ONE_KEY(KC_S) {
        register_code(KC_SCROLLLOCK);
        unregister_code(KC_SCROLLLOCK);
    }

    SEQ_ONE_KEY(KC_B) {
        register_code(KC_PAUSE);
        unregister_code(KC_PAUSE);
    }

    SEQ_TWO_KEYS(KC_P, KC_D) {
        register_code(KC_PGDOWN);
        unregister_code(KC_PGDOWN);
    }

    SEQ_TWO_KEYS(KC_P, KC_U) {
        register_code(KC_PGUP);
        unregister_code(KC_PGUP);
    }
  }

}

