// https://docs.qmk.fm/#/keymap

// # What's the problem with shift?
//
// Each non function key in the ANSI layout has a main symbol and a symbol emitted when pressed alongside shift. The same goes for Alt
// and other modifiers. If we want a different symbol to be emitted when shift and a symbol is pressed, we need to replace that keypress.
// Furthermore, if the symbol we want emitted when shift is pressed is in non-shift position (e.g. the semicolon), we need to unregister
// any shift mods that may be registered.
// 
// ## What about CAPS_LOCK?
//
// We can still use CAPS_LOCK as usual, as it should only affect alphas. We need to handle accents a dieresis to use a non shifted
// version of the letter, as otherwise they emmit the wrong symbol. 
//
// ## Sources
//
// - The shift solution idea came from https://www.reddit.com/r/olkb/comments/k8wrge/which_layer_is_active_when_shift_key_is_held_down/ 


#include QMK_KEYBOARD_H

#include "oneshot.h"

extern uint8_t is_master;

// Layers:

#define _BASE 0
#define _NUMS 1
#define _FUN 2
#define _NAV 3
#define _SYM 4
#define _WIN 5

// Tap dances:

enum {
  TD_RESET = 0
};

enum custom_keycodes { 

  // Manual Shift keys (MS_XX_YY) are keys where we want a particular symbol when shift is pressed and another one when it is not

  MS_COM_QUE = SAFE_RANGE,  // , / ?
  MS_DOT_EXC,               // . / !
  MS_SLA_AT,                // / / @
  MS_CL_CTL,                // Ctrl / : / ;

  // Special symbols

  S_KAR,   // ->  (Kotlin Arrow)
  S_SAR,   // =>  (Scala Arrow)

  // Catalan symbols

  CA_ACCO ,    // ` / ^ (actually a Manual Shift)
  CA_ACC_DIE,  // ´ / ¨ (actually a Manual Shift)
  S_ELG,       // L·L   (actually a special symbol)

  // Retype keys: we want a keypress even if it is already pressed

  RT_E,        // Retype E

  // Callum's oneshot
  OS_SHFT,
  OS_CTRL,
  OS_ALT,
  OS_CMD,
  OS_NUMS,
  OS_FUN,
  OS_NAV,
  OS_SYM,
  OS_WIN
};

// Thumb layer tap
#define L_WIN KC_AGAIN             // Window movement layer


#define S_EUR A(S(KC_2))

#define TD_RST TD(TD_RESET) // Reset tap dance

#define TSFT OSM(MOD_RSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Base layer

  [_BASE] = LAYOUT_split_3x6_3( \
      KC_ESC,  KC_Q,    KC_W,    RT_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,       KC_O,       KC_P,      MS_SLA_AT,\
      KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,       KC_L,       KC_SCOLON, CA_ACC_DIE,\
      CA_ACCO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    MS_COM_QUE, MS_DOT_EXC, KC_MINS,   KC_QUOT,\
                                          OS_SYM , OS_NAV, L_WIN,      OS_SHFT,  OS_NUMS, OS_FUN \
  ),
  [_NUMS] = LAYOUT_split_3x6_3( \
      XXXXXXX, KC_PSLS, KC_7,    KC_8,    KC_9,    KC_PMNS,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
      KC_PERC, KC_PAST, KC_4,    KC_5,    KC_6,    KC_PPLS,                      XXXXXXX, OS_SHFT, OS_CMD,  OS_ALT,  OS_CTRL, XXXXXXX,\
      S_EUR,   KC_COMM, KC_1,    KC_2,    KC_3,    KC_DOT,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
                                          KC_BSPC, KC_0,    KC_EQL,     XXXXXXX, OS_NUMS, XXXXXXX \
    ),

  [_FUN] = LAYOUT_split_3x6_3( \
      TD_RST,  KC_F10,  KC_F7,   KC_F8,   KC_F9,   KC__VOLUP,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
      XXXXXXX, KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC__VOLDOWN,                  XXXXXXX, OS_SHFT, OS_CMD,  OS_ALT,  OS_CTRL, XXXXXXX,\
      XXXXXXX, KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC__MUTE,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
                                          KC_BSPC, KC_SPC,  XXXXXXX,    XXXXXXX, XXXXXXX, OS_FUN \
    ),

  [_NAV] = LAYOUT_split_3x6_3( \
      TD_RST,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PGUP, A(KC_LEFT), KC_UP,A(KC_RGHT),XXXXXXX,XXXXXXX,\
      KC_CAPS, OS_CTRL, OS_ALT,  OS_CMD,  OS_SHFT,  XXXXXXX,                   G(KC_LEFT), KC_LEFT, KC_DOWN, KC_RGHT,G(KC_RGHT),XXXXXXX,\
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PGDN, G(KC_V), G(KC_C), G(KC_X), XXXXXXX, XXXXXXX,\
                                          XXXXXXX, OS_NAV,  XXXXXXX,    KC_LSFT, KC_SPC,  KC_ENT \
    ),
  [_SYM] = LAYOUT_split_3x6_3(
      XXXXXXX, XXXXXXX, XXXXXXX, S_EUR,   XXXXXXX, XXXXXXX,                      KC_DLR,  KC_LBRC, KC_RBRC, KC_PIPE, KC_AMPR, KC_BSLS,\
      XXXXXXX, OS_CTRL, OS_ALT,  OS_CMD,  OS_SHFT, XXXXXXX,                      KC_HASH, KC_LPRN, KC_RPRN, S_ELG,   S_KAR,   S_SAR,\
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_CIRC, KC_LCBR, KC_RCBR, KC_LT,   KC_GT,   KC_TILD,\
                                          OS_SYM,  XXXXXXX, XXXXXXX,    XXXXXXX, KC_SPC,  KC_ENT \
    )
};

void register_non_shifted_key(uint16_t keycode){
  // https://docs.qmk.fm/#/feature_advanced_keycodes?id=checking-modifier-state
  // https://www.reddit.com/r/olkb/comments/5r0mfp/check_for_modifiersother_keys_in_macros/
  bool lsftActive = get_mods() & MOD_BIT(KC_LSFT);
  bool rsftActive = get_mods() & MOD_BIT(KC_RSFT);
  // TODO: CAPS LOCK not correctly handled for some reason. It does never send a KC_CAPS
  bool capsLocked = host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK);
  // Caps lock does not affect symbols, but it does affect KC_E and KC_U
  bool needToUnCaps = capsLocked && (keycode == A(KC_E) || keycode == A(KC_U) || keycode == A(KC_I));
  if (lsftActive) {
    unregister_mods(MOD_BIT(KC_LSFT));
  }
  if (rsftActive) {
    unregister_mods(MOD_BIT(KC_RSFT));
  }
  if (needToUnCaps) {
    tap_code(KC_CAPS);
  } 
  register_code16(keycode);
  if (needToUnCaps) {
    tap_code(KC_CAPS);
  } 
  if (lsftActive) {
    register_mods(MOD_BIT(KC_LSFT));
  }
  if (rsftActive) {
    register_mods(MOD_BIT(KC_RSFT));
  }  
};

void process_manual_shft(uint16_t keycodeWhenNotShift, uint16_t keycodeWhenShift, bool pressed){
    if(pressed){
      if(get_mods() & MOD_MASK_SHIFT){
        register_non_shifted_key(keycodeWhenShift);
      } else {
        register_code16(keycodeWhenNotShift);
      }
    } else {
      // We don't know which keycode was registered... so we unregister both
      // As they are supposed to be mapped to the same key, we don't have the issue of both codes being pressed at the same time and only one released
      unregister_code16(keycodeWhenShift);
      unregister_code16(keycodeWhenNotShift);
    }
};

void process_tap_sequence2(uint16_t tap0, uint16_t tap1, keyrecord_t *record){
  if (record->event.pressed) {
    tap_code16(tap0);
    tap_code16(tap1);
  }
};

void process_tap_sequence3(uint16_t tap0, uint16_t tap1, uint16_t tap2, keyrecord_t *record){
  if (record->event.pressed) {
    tap_code16(tap0);
    tap_code16(tap1);
    tap_code16(tap2);
  }
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case KC_ESC:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case KC_ESC:
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
    case OS_NUMS:
    case OS_FUN:
    case OS_NAV:
    case OS_SYM:
    case OS_WIN:
        return true;
    default:
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

oneshot_state os_layer_nums = os_up_unqueued;
oneshot_state os_layer_fun = os_up_unqueued;
oneshot_state os_layer_nav = os_up_unqueued;
oneshot_state os_layer_sym = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  update_oneshot_layer(&os_layer_nums, _NUMS, KC_SPC, OS_NUMS, keycode, record);
  update_oneshot_layer(&os_layer_fun, _FUN, KC_ENT, OS_FUN, keycode, record);
  update_oneshot_layer(&os_layer_nav, _NAV, KC_SPC, OS_NAV, keycode, record);
  update_oneshot_layer(&os_layer_sym, _SYM, KC_BSPC, OS_SYM, keycode, record);

  update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
  update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL, keycode, record);
  update_oneshot(&os_alt_state, KC_LALT, OS_ALT, keycode, record);
  update_oneshot(&os_cmd_state, KC_LCMD, OS_CMD, keycode, record);

  switch(keycode) { 
    case S_ELG:
      process_tap_sequence3(KC_L, S(A(KC_9)) ,KC_L, record);
      break;
    case S_KAR:
      process_tap_sequence2(KC_MINS, KC_GT, record);
      break;
    case S_SAR:
      process_tap_sequence2(KC_EQL, KC_GT, record);
      break;
    case MS_COM_QUE:  
      // See https://getreuer.info/posts/keyboards/custom-shift-keys/index.html for an alternative
      process_manual_shft(KC_COMMA, KC_QUESTION, record->event.pressed);
      break;
    case MS_DOT_EXC:  
      process_manual_shft(KC_DOT, KC_EXCLAIM, record->event.pressed);
      break;
    case MS_SLA_AT:  
      process_manual_shft(KC_SLASH, KC_AT, record->event.pressed);
      break;
    case CA_ACCO:  
      process_manual_shft(A(KC_GRV), A(KC_I), record->event.pressed);
      break;
    case MS_CL_CTL:  
      process_manual_shft(S(KC_SCOLON), KC_SCOLON, record->event.pressed);
      break;
    case CA_ACC_DIE:  
      if (record->event.pressed){
        // We want to tap the accent to avoid Alt being pressed after the accent is typed: 
        process_manual_shft(A(KC_E), A(KC_U), true); // ´ / ¨
        process_manual_shft(A(KC_E), A(KC_U), false);
      }
      break;

    // Tested:
    // A rapid succession of ´ + E may ignore E (when it happens before the keyup of ´) because ´ is, in fact A(KB_E).
    // So the custom keycode RT_E (for ReType) simply registers KC_E (which unregisters it if alerady pressed, see actions.c:804)
    // TODO: Do we need RT_U?  
    case RT_E:
      if (record->event.pressed){
        register_code(KC_E);
      } else {
        unregister_code(KC_E);
      }
      break;

    case L_WIN:
      if(record->event.pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        register_code(KC_LCTL);
      } else {
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
      }
      break;
  }
  return true;

};
  
// Tested:
void safe_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 5) {
    // Reset the keyboard if you tap the key more than 5 times
    reset_keyboard();
    reset_tap_dance(state);
  }
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_RESET] = ACTION_TAP_DANCE_FN(safe_reset)
};
