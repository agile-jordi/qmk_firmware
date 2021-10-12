// https://docs.qmk.fm/#/keymap

// # Why a shifted layer?
//
// Each non function key in the ANSI layout has a main symbol and a symbol emitted when pressed alongside shift. The same goes for Alt
// and other modifiers. We can adjust almost everything, but deciding what symbol to emmit when a key is pressed alongside shift is not easy.
// This layer is an answer to that. We could do something similar for Alt.
// 
// ## How does it work?
//
// We don't define any key to act as shift. Instead, the key that will shift keys activates this layer.
// When entering the layer, shift is pressed, and it is released when leaving the layer.
// That way, any key not overriden in this layer behaves exactly as the key in the base layer when shifted in the ANSI US EN layout.
// But we can redefine certain keys to act differently.
// When one of those keys is a symbol that is not in shift position, we need to "unshift" before registering the key and reshift
// afterwards, so shift keeps pressed after that symbol.
//
// ## Alternatives
//
// I tried not registering shift but defining each key in the layer to be S(x) where x is the corresponding key in the base layer. But:
//
// - That implied a lot of duplication in the definition of this layer. If something in the base layer changed I needed to remember
// to make the same change in the shifted layer
// - ASD and ;LK needed to mod tap (like in the base layer), but with a mod on top of the layer (like ML). No feature combining these
// 2 functionalities exist and it is not as simple as using a custom keycode
//
// ## What about CAPS_LOCK?
//
// We can still use CAPS_LOCK as usual, as it should only affect alphas. We need to handle accents a dieresis to use a non shifted
// version of the letter, as otherwise they emmit the wrong symbol. 
//
// ## An alternative
//
// Acording to https://www.reddit.com/r/olkb/comments/k8wrge/which_layer_is_active_when_shift_key_is_held_down/ it may be far easier 
// to simply capture shifted keys I want to change and change them manually. This seems mostly what I do here with register_non_shifted_key
// but avoiding the whole shifted layer and having specific, hardcoded changes instead.


#include QMK_KEYBOARD_H

extern uint8_t is_master;

// Layers:
#define _BASE 0
#define _SHIFTED 1
#define _NUMS 2
#define _FUN 3
#define _NAV 4
#define _SYM 5
#define _WIN 6

enum {
  TD_RESET = 0
};

enum custom_keycodes {
  // Non shifted keycodes (we want to register keypress without shift even if shift is currently pressed):
  NS_E = SAFE_RANGE,
  NS_U,
  NS_EQL,
  NS_SCLN,
  NS_GRV,
  CA_ACCO,
  CA_ACCT,
  CA_DIE,
  // Retype keys: we want a keypress even if it is already pressed
  RT_E,
  // LT with shifted key
  M_CL_CTL,
  // Special function keys
  //NV_CMTB
  // Special symbols
  S_ELG,
  S_KAR,
  S_SAR
};

// Home row modifiers
#define M_J_SFT LT(_SHIFTED, KC_J)
#define M_K_CMD CMD_T(KC_K)
#define M_L_ALT ALT_T(KC_L)
#define M_F_SFT LT(_SHIFTED, KC_F)
#define M_D_CMD CMD_T(KC_D)
#define M_S_ALT ALT_T(KC_S)
#define M_A_CTL CTL_T(KC_A)

// Thumb layer tap
#define L_SYM_B LT(_SYM,KC_BSPC)
#define L_NAV_S LT(_NAV,KC_SPC)
#define L_NUM_S LT(_NUMS,KC_SPC)
#define L_FUN_E LT(_FUN,KC_ENT)
#define L_WIN KC_AGAIN             // Window movement layer / Redo
#define L_SFT LT(_SHIFTED, KC_DEL)


#define S_EUR A(S(KC_2))

#define TD_RST TD(TD_RESET)

#define TSFT OSL(_SHIFTED)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Base layer

  [_BASE] = LAYOUT_split_3x6_3( \
      KC_ESC,  KC_Q,    KC_W,    RT_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_SLASH,\
      KC_TAB,  M_A_CTL, M_S_ALT, M_D_CMD, M_F_SFT, KC_G,                         KC_H,    M_J_SFT, M_K_CMD, M_L_ALT, M_CL_CTL,CA_ACCT,\
      CA_ACCO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_MINS, KC_QUOT,\
                                          L_SYM_B, L_NAV_S, L_WIN,      TSFT,    L_NUM_S, L_FUN_E \
  ),

  [_SHIFTED] = LAYOUT_split_3x6_3( \
      _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, KC_AT,\
      _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, NS_SCLN, CA_DIE,\
      NS_EQL,  _______, _______, _______, _______, _______,                       _______, _______, KC_QUES, KC_EXLM, KC_UNDS, KC_DQT,\
                                          _______, _______, XXXXXXX,     XXXXXXX, _______, _______ \
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

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Tested:
// Register a shifted mod upon entering the shifted layer, unregister upon leaving it
// https://docs.qmk.fm/#/custom_quantum_functions?id=layer-change-code
layer_state_t layer_state_set_user(layer_state_t state) {
  // IS_LAYER_ON returns wether the layer is on before applying state
  // I register KC_LSFT MOD only when the _SHIFTED layer is activated, not every time it is active
  // I assume registering the KC_LSFT MOD is somehow better than registering a key, but this is pure speculation
  if(IS_LAYER_OFF(_SHIFTED) && (IS_LAYER_ON_STATE(state, _SHIFTED))){
    // https://docs.qmk.fm/#/feature_macros?id=advanced-macro-functions
    register_mods(MOD_BIT(KC_LSFT));
    // register_code(KC_LSFT);

  } else if (IS_LAYER_ON(_SHIFTED) && IS_LAYER_OFF_STATE(state, _SHIFTED)){
    unregister_mods(MOD_BIT(KC_LSFT));
    // unregister_code(KC_LSFT);
  }
  return state;
}

// Trying to make OLT(_SHIFTED) work...
void oneshot_layer_changed_user(uint8_t layer) {
  if(layer == _SHIFTED){
    set_oneshot_mods(MOD_BIT(KC_LSFT));
  }
}

uint16_t nonShiftedCode(uint16_t keycode) {
  switch(keycode) {
    case NS_E: return KC_E;
    case NS_U: return KC_U;
    case NS_EQL: return KC_EQL;
    case NS_SCLN: return KC_SCLN;
    case NS_GRV: return KC_GRV;
    default: return keycode;
  }
}

void register_non_shifted_key(uint16_t keycode){
  // https://www.reddit.com/r/olkb/comments/5r0mfp/check_for_modifiersother_keys_in_macros/
  bool lsftActive = get_mods() & MOD_BIT(KC_LSFT);
  bool rsftActive = get_mods() & MOD_BIT(KC_RSFT);
  bool capsLocked = host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK);
  // Caps lock does not affect symbols, but it does affect KC_E and KC_U
  bool needToUnCaps = capsLocked && (keycode == KC_E || keycode == KC_U);
  if (lsftActive) {
    unregister_mods(MOD_BIT(KC_LSFT));
    // unregister_code(KC_LSFT);
  }
  if (rsftActive) {
    unregister_mods(MOD_BIT(KC_RSFT));
    // unregister_code(KC_RSFT);
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
    // register_code(KC_LSFT);
  }
  if (rsftActive) {
    register_mods(MOD_BIT(KC_RSFT));
    // register_code(KC_RSFT);
  }  
}

bool process_non_shifted_key(bool pressed, uint16_t keycode){
  if(pressed) {
    register_non_shifted_key(keycode);
  } else {
    unregister_code(keycode);
  }
  return false;
}

// void update_swapper(uint16_t keycode, keyrecord_t *record){
//   static bool swapper_active = false;
//   if (keycode == NV_CMTB){
//     if (record->event.pressed){
//       if (!swapper_active){
//         swapper_active = true;
//         register_code(KC_LCMD);
//       } 
//       register_code(KC_TAB);
//     } else {
//       unregister_code(KC_TAB);
//     }
//   } else if (swapper_active && (keycode == KC_ESC || keycode == KC_ENT)){
//     unregister_code(KC_LCMD);
//     swapper_active = false;

//   }
// } 

bool tap_unshifted_modded_key(uint16_t keycode, keyrecord_t *record, uint8_t mods){
  if (record->event.pressed){
    register_mods(mods);
    register_non_shifted_key(keycode);
    unregister_code(keycode);
    unregister_mods(mods);
  }
  return false;

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  static uint16_t win_again_timer;
  // static uint16_t sym_undo_timer;
  static uint16_t cln_ctl_timer;

  // Non Shifted key codes when shift is pressed:
  if (keycode >= NS_E && keycode <= NS_GRV) {
    return process_non_shifted_key(record->event.pressed, nonShiftedCode(keycode));
  }

  // update_swapper(keycode, record);

  switch(keycode) { 

    // TODO: This still does not work with caps lock. It disables caps lock for some reason...
    case CA_ACCO: // A(NS_GRV)
      return tap_unshifted_modded_key(KC_GRV, record, MOD_BIT(KC_LALT));
    case CA_ACCT: // A(NS_E)
      return tap_unshifted_modded_key(KC_E, record, MOD_BIT(KC_LALT));
    case CA_DIE:  // A(NS_U)
      return tap_unshifted_modded_key(KC_U, record, MOD_BIT(KC_LALT));

    // Tested:
    // A rapid succession of ´ + E may ignore E (when it happens before the keyup of ´) because ´ is, in fact A(KB_E).
    // So the custom keycode RT_E (for ReType) simply registers KC_E (which unregisters it if alerady pressed, see actions.c:804)
    case RT_E:
      if (record->event.pressed){
        register_code(KC_E);
      } else {
        unregister_code(KC_E);
      }
      return false;

    case S_ELG:
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

    // Tested:
    // Poor man's LT/MT used when we want a shifted or otherwise modified key code
    // See https://thomasbaart.nl/2018/12/09/qmk-basics-tap-and-hold-actions/#a-workaround-for-mod-tap 
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

    case M_CL_CTL:
      if (record->event.pressed){
        cln_ctl_timer = timer_read();
        register_code(KC_RCTL);
      } else {
        unregister_code(KC_RCTL);
        if (timer_elapsed(cln_ctl_timer) < TAPPING_TERM) {
          tap_code16(KC_COLN);
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
    // Reset the keyboard if you tap the key more than three times
    reset_keyboard();
    reset_tap_dance(state);
  }
}
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_RESET] = ACTION_TAP_DANCE_FN(safe_reset)
};
