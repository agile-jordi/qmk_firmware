// https://docs.qmk.fm/#/keymap

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

enum custom_keycodes {
  // Non shifted keycodes (we want to register keypress without shift even if shift is currently pressed):
  NS_E = SAFE_RANGE,
  NS_U,
  NS_MINS,
  NS_EQL,
  NS_LBRC,
  NS_RBRC,
  NS_BSLS,
  NS_NUHS,
  NS_SCLN,
  NS_QUOT,
  NS_GRV,
  NS_COMM,
  NS_DOT,
  NS_SLSH,
  NS_NUBS,
  // Retype keys: we want a keypress even if it is already pressed
  RT_E
};

// TODO: ???
enum macro_keycodes {
  KC_SAMPLEMACRO,
};

// Home row modifiers
#define M_J_SFT LT(_SHIFTED, KC_J)
#define M_K_CMD CMD_T(KC_K)
#define M_L_ALT ALT_T(KC_L)
#define M_CL_CTL CTL_T(KC_COLON)
#define M_F_SFT LT(_SHIFTED, KC_F)
#define M_D_CMD CMD_T(KC_D)
#define M_S_ALT ALT_T(KC_S)
#define M_A_CTL CTL_T(KC_A)

// Thumb layer tap
// TODO: Can we LT to a modified key??
#define L_NAV_U LT(_NAV,G(KC_Z))
#define L_SYM_E LT(_SYM,KC_ENT)
#define L_NUM_S LT(_NUMS,KC_SPC)
#define L_FUN_B LT(_FUN,KC_BSPC)

// Aliases
// We use Non Shifted versions so that the key actually works even if shift is pressed
// TODO: Check this actually works, as when pressing Alt, shift may be still pressed
#define CA_ACCO A(NS_GRV)
#define CA_ACCT A(NS_E)
#define CA_DIE A(NS_U)

#define NV_WL A(KC_LEFT)
#define NV_WR A(KC_RGHT)
#define NV_LL LCMD(KC_LEFT)
#define NV_LR LCMD(KC_RGHT)


// TODO: A rapid succession of ´ + E may ignore E (when it happens before the keyup of ´) because é is, in fact A(KB_E). So I need to define a
// custom keycode for E so that if E is already pressed it releases E and presses it again
// I'll need to keep track of wether E has been pressed by hand, see 
// https://www.reddit.com/r/olkb/comments/5r0mfp/check_for_modifiersother_keys_in_macros/ 
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x6_3( \
      KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_SLASH,\
      KC_TAB,  M_A_CTL, M_S_ALT, M_D_CMD, M_F_SFT, KC_G,                         KC_H,    M_J_SFT, M_K_CMD, M_L_ALT, M_CL_CTL,CA_ACCT,\
      CA_ACCO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_MINS, KC_QUOT,\
                                          L_NAV_U, L_SYM_E, S(G(KC_Z)), KC_DEL,  L_NUM_S, L_FUN_B \
  ),

  // I can't use MT(...,S(...)), so I have to  solve ASD & ;LK programatically
  // I can't use LT if I want shift around the layer and I can't use LM(...) to add shift to a layer because then I can't tap
  // So I only apply shift to FUN and NAV layeers and I forget about tappiing them, so no shift + undo nor shift + backspace
  // Idea: I could better change the strategy to:
  //   1. When entering the shifted layer, programatically press lshift and rerlease it upon leaving the layer
  //     (https://docs.qmk.fm/#/custom_quantum_functions?id=layer-change-code)
  //   2. Map each key in the layer to KC_TRANS except for those we actually want to change
  //   3. Handle non shifted keys in the shifted layer by releasing shift and pressing it again
  [_SHIFTED] = LAYOUT_split_3x6_3( \
      _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, KC_AT,\
      _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, CA_DIE,\
      NS_EQL,  _______, _______, _______, _______, _______,                       _______, _______, KC_QUES, KC_EXLM, KC_UNDS, KC_DQT,\
                                          _______, _______, _______,     _______, _______, _______ \
    ),

  [_NUMS] = LAYOUT_split_3x6_3( \
      XXXXXXX, KC_PSLS, KC_7,    KC_8,    KC_9,    KC_PMNS,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
      XXXXXXX, KC_PAST, KC_4,    KC_5,    KC_6,    KC_PPLS,                      XXXXXXX, KC_RSFT, KC_RCMD, KC_RALT, KC_RCTL, XXXXXXX,\
      XXXXXXX, KC_PERC, KC_1,    KC_2,    KC_3,    XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
                                          XXXXXXX, KC_0,    XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX \
    ),

  [_FUN] = LAYOUT_split_3x6_3( \
      XXXXXXX, KC_F10,  KC_F7,   KC_F8,   KC_F9,   KC__VOLUP,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
      XXXXXXX, KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC__VOLDOWN,                  XXXXXXX, KC_RSFT, KC_RCMD, KC_RALT, KC_RCTL, XXXXXXX,\
      XXXXXXX, KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC__MUTE,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX \
    ),

  [_NAV] = LAYOUT_split_3x6_3( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PGUP, NV_WL,   KC_UP,   NV_WR,   XXXXXXX, XXXXXXX,\
      KC_CAPS, KC_LCTL, KC_LALT, KC_LCMD, KC_LSFT, XXXXXXX,                      NV_LL,   KC_LEFT, KC_DOWN, KC_RGHT, NV_LR,   XXXXXXX,\
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PGDN, G(KC_V), G(KC_C), G(KC_X), XXXXXXX, XXXXXXX,\
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX \
    ),
  [_SYM] = LAYOUT_split_3x6_3( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_DLR,  KC_LBRC, KC_RBRC, KC_PIPE, KC_AMPR, KC_BSLS,\
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_HASH, KC_LPRN, KC_RPRN, KC_RGHT, KC_SLSH, KC_PERC,\
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_CIRC, KC_LCBR, KC_RCBR, KC_LT,   KC_GT,   KC_TILD,\
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX \
    )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}


// https://docs.qmk.fm/#/custom_quantum_functions?id=layer-change-code
layer_state_t layer_state_set_user(layer_state_t state) {
  // I asssume IS_LAYER_ON returns wether the layer is on before applying state
  // I try to register KC_LSFT only when the _SHIFTED layer is activated, not every timee it is active
  if(IS_LAYER_OFF(_SHIFTED) && IS_LAYER_ON_STATE(state, _SHIFTED)){
    // https://docs.qmk.fm/#/feature_macros?id=advanced-macro-functions
    register_code(KC_LSFT);

  } else if (IS_LAYER_ON(_SHIFTED) && IS_LAYER_OFF_STATE(state, _SHIFTED)){
    unregister_code(KC_LSFT);
  }
  return state;
}

uint8_t nonShiftedCode(uint16_t keycode) {
  switch(keycode) {
    case NS_E: return KC_E;
    case NS_U: return KC_U;
    case NS_MINS: return KC_MINS;
    case NS_EQL: return KC_EQL;
    case NS_LBRC: return KC_LBRC;
    case NS_RBRC: return KC_RBRC;
    case NS_BSLS: return KC_BSLS;
    case NS_NUHS: return KC_NUHS;
    case NS_SCLN: return KC_SCLN;
    case NS_QUOT: return KC_QUOT;
    case NS_GRV: return KC_GRV;
    case NS_COMM: return KC_COMM;
    case NS_DOT: return KC_DOT;
    case NS_SLSH: return KC_SLSH;
    case NS_NUBS: return KC_NUBS;
    default: return keycode;
  }
}

bool process_non_shifted_key(keyrecord_t *record, uint8_t normalKeycode){
  if(record->event.pressed) {
      // https://www.reddit.com/r/olkb/comments/5r0mfp/check_for_modifiersother_keys_in_macros/
      uint8_t mods = keyboard_report->mods;
      if (mods & MOD_BIT(KC_LSFT)) {
        unregister_code(KC_LSFT);
      }
      if (mods & MOD_BIT(KC_RSFT)) {
        unregister_code(KC_RSFT);
      }
      register_code(nonShiftedCode(normalKeycode));
      if (mods & MOD_BIT(KC_LSFT)) {
        register_code(KC_LSFT);
      }
      if (mods & MOD_BIT(KC_RSFT)) {
        register_code(KC_RSFT);
      }
      return false;
    } else {
      unregister_code(normalKeycode);
      return false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Non Shifted key codes when shift is pressed:
  if (keycode >= NS_E && keycode <= NS_NUBS) {
    return process_non_shifted_key(record, nonShiftedCode(keycode));
  }

  // A rapid succession of ´ + E may ignore E (when it happens before the keyup of ´) because é is, in fact A(KB_E).
  // So the custom keycode RT_E (for ReType) simply rregisters KC_E (which unregisters it if alerady perssed, see actions.c:804)
  if (keycode == RT_E) {
    if (record->event.pressed){
      register_code(KC_E);
    } else {
      unregister_code(KC_E);
    }
  } 

  return true;
}
