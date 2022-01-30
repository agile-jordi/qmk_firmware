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

  // Special


};

// Home row modifiers
#define M_J_SFT RSFT_T(KC_J)        // Shift / J
#define M_K_CMD RCMD_T(KC_K)        // Cmd / K
#define M_L_ALT RALT_T(KC_L)        // Alt / L
                                    // Ctrl / : / ; is a user key code
#define M_F_SFT SFT_T(KC_F)         // Shift / F
#define M_D_CMD CMD_T(KC_D)         // Cmd / D
#define M_S_ALT ALT_T(KC_S)         // Alt / S
#define M_A_CTL CTL_T(KC_A)         // Ctrl / A

// Thumb layer tap
// TODO: Test OSL (https://docs.qmk.fm/#/one_shot_keys)
#define L_SYM_B LT(_SYM,KC_BSPC)
#define L_NAV_S LT(_NAV,KC_SPC)
#define L_NUM_S LT(_NUMS,KC_SPC)
#define L_FUN_E LT(_FUN,KC_ENT)
#define L_WIN KC_AGAIN             // Window movement layer / Redo
#define L_SFT SFT_T(KC_DEL)


#define S_EUR A(S(KC_2))

#define TD_RST TD(TD_RESET) // Reset tap dance

#define TSFT OSM(MOD_RSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Base layer

  [_BASE] = LAYOUT_split_3x6_3( \
      KC_ESC,  KC_Q,    KC_W,    RT_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,       KC_O,       KC_P,    MS_SLA_AT,\
      KC_TAB,  M_A_CTL, M_S_ALT, M_D_CMD, M_F_SFT, KC_G,                         KC_H,    M_J_SFT, M_K_CMD,    M_L_ALT,    MS_CL_CTL,CA_ACC_DIE,\
      CA_ACCO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    MS_COM_QUE, MS_DOT_EXC, KC_MINS, KC_QUOT,\
                                          L_SYM_B, L_NAV_S, L_WIN,      TSFT,    L_NUM_S, L_FUN_E \
  ),
  [_NUMS] = LAYOUT_split_3x6_3( \
      XXXXXXX, KC_PSLS, KC_7,    KC_8,    KC_9,    KC_PMNS,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
      KC_PERC, KC_PAST, KC_4,    KC_5,    KC_6,    KC_PPLS,                      XXXXXXX, KC_RSFT, KC_RCMD, KC_RALT, KC_RCTL, XXXXXXX,\
      S_EUR,   KC_COMM, KC_1,    KC_2,    KC_3,    KC_DOT,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
                                          KC_BSPC, KC_0,    KC_EQL,     XXXXXXX, XXXXXXX, XXXXXXX \
    ),

  [_FUN] = LAYOUT_split_3x6_3( \
      TD_RST,  KC_F10,  KC_F7,   KC_F8,   KC_F9,   KC__VOLUP,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
      XXXXXXX, KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC__VOLDOWN,                  XXXXXXX, KC_RSFT, KC_RCMD, KC_RALT, KC_RCTL, XXXXXXX,\
      XXXXXXX, KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC__MUTE,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX \
    ),

  [_NAV] = LAYOUT_split_3x6_3( \
      TD_RST,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PGUP, A(KC_LEFT), KC_UP,A(KC_RGHT),XXXXXXX,XXXXXXX,\
      KC_CAPS, KC_LCTL, KC_LALT, KC_LCMD, KC_LSFT, XXXXXXX,                   G(KC_LEFT), KC_LEFT, KC_DOWN, KC_RGHT,G(KC_RGHT),XXXXXXX,\
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PGDN, G(KC_V), G(KC_C), G(KC_X), XXXXXXX, XXXXXXX,\
                                          XXXXXXX, XXXXXXX, XXXXXXX,    KC_LSFT, KC_SPC,  XXXXXXX \
    ),
  [_SYM] = LAYOUT_split_3x6_3(
      XXXXXXX, XXXXXXX, XXXXXXX, S_EUR,   XXXXXXX, XXXXXXX,                      KC_DLR,  KC_LBRC, KC_RBRC, KC_PIPE, KC_AMPR, KC_BSLS,\
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_HASH, KC_LPRN, KC_RPRN, S_ELG,   S_KAR,   S_SAR,\
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_CIRC, KC_LCBR, KC_RCBR, KC_LT,   KC_GT,   KC_TILD,\
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_SPC,  XXXXXXX \
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
}

// bool tap_unshifted_modded_key(uint16_t keycode, keyrecord_t *record, uint8_t mods){
//   if (record->event.pressed){
//     register_mods(mods);
//     register_non_shifted_key(keycode);
//     unregister_code(keycode);
//     unregister_mods(mods);
//   }
//   return false;

// }

bool process_manual_shft(uint16_t keycodeWhenNotShift, uint16_t keycodeWhenShift, bool pressed){
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
  return false;

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  static uint16_t win_again_timer;
  // static uint16_t sym_undo_timer;
  static uint16_t cln_ctl_timer;

  switch(keycode) { 

    case MS_COM_QUE:  // , / ?
      return process_manual_shft(KC_COMMA, KC_QUESTION, record->event.pressed);
    case MS_DOT_EXC:  // . / !
      return process_manual_shft(KC_DOT, KC_EXCLAIM, record->event.pressed);
    case MS_SLA_AT:   // / / @
      return process_manual_shft(KC_SLASH, KC_AT, record->event.pressed);
    case CA_ACC_DIE:  // ´ / ¨
      return process_manual_shft(A(KC_E), A(KC_U), record->event.pressed);
    case CA_ACCO:     // ` / ^
      return process_manual_shft(A(KC_GRV), A(KC_I), record->event.pressed);
   

    // We need to handle this case with by hand because one tap seems not to allow custom keycodes
    // Tested:
    // Poor man's LT/MT used when we want a shifted or otherwise modified key code
    // See https://thomasbaart.nl/2018/12/09/qmk-basics-tap-and-hold-actions/#a-workaround-for-mod-tap 
    // See also https://docs.qmk.fm/#/mod_tap?id=intercepting-mod-taps  
    case MS_CL_CTL:
      if (record->event.pressed){
        cln_ctl_timer = timer_read();
        register_code(KC_RCTL);
      } else {
        unregister_code(KC_RCTL);
        if (timer_elapsed(cln_ctl_timer) < TAPPING_TERM) {
          process_manual_shft(S(KC_SCOLON), KC_SCOLON, true);
          process_manual_shft(S(KC_SCOLON), KC_SCOLON, false);
        }
      }
      return false;



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
      return false;

    case S_ELG: // L·L
      if (record->event.pressed) {
        tap_code(KC_L);
        tap_code16(S(A(KC_9)));
        tap_code(KC_L);
      }  
      return false;

    case S_KAR: // ->
      if (record->event.pressed) {
        tap_code(KC_MINS);
        tap_code16(KC_GT);
       }  
      return false;

    case S_SAR: // =>
      if (record->event.pressed) {
        tap_code16(KC_EQL);
        tap_code16(KC_GT);
       }  
      return false;

    // Issue: Typing SYM + ( faster than the TAPPING_TERM taps the symbol and thenUNDO
    // case L_SYM_U:
    //   if (record->event.pressed){
    //     sym_undo_timer = timer_read();
    //     layer_on(_SYM);
    //   } else {
    //     layer_off(_SYM);
    //     if (timer_elapsed(sym_undo_timer) < TAPPING_TERM) {
    //       tap_code16(G(KC_Z));
    //     }
    //   }
    //   return false;
    case L_WIN:
      if(record->event.pressed) {
        win_again_timer = timer_read();
        register_code(KC_LALT);
        register_code(KC_LSFT);
        register_code(KC_LCTL);
      } else {
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        if (timer_elapsed(win_again_timer) < TAPPING_TERM) {
          // REDO
          tap_code16(S(G(KC_Z)));
        }
      }
      return false;

    default:
      return true;
  }

}
  
// Tested:
void safe_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 5) {
    // Reset the keyboard if you tap the key more than 5 times
    reset_keyboard();
    reset_tap_dance(state);
  }
}
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_RESET] = ACTION_TAP_DANCE_FN(safe_reset)
};
