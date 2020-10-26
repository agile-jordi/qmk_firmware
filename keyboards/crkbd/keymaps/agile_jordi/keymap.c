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
// enum macro_keycodes {
//   KC_SAMPLEMACRO,
// };

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
// TODO: Can we LT to a modified key?? NO
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

#define S_EUR A(KC_2)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Base layer

  [_BASE] = LAYOUT_split_3x6_3( \
      KC_ESC,  KC_Q,    KC_W,    RT_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_SLASH,\
      KC_TAB,  M_A_CTL, M_S_ALT, M_D_CMD, M_F_SFT, KC_G,                         KC_H,    M_J_SFT, M_K_CMD, M_L_ALT, M_CL_CTL,CA_ACCT,\
      CA_ACCO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_MINS, KC_QUOT,\
                                          L_NAV_U, L_SYM_E, S(G(KC_Z)), KC_DEL,  L_NUM_S, L_FUN_B \
  ),

  // # Why a shifted layer?
  //
  // Each non function key in the ANSI layout has a main symbol and a symbol emitted when pressed alongside shift. The same goes for Alt
  // and other modifiers. We can adjust almost everything, but deciding what symbol to emmit when a key is pressed alongside shift is not easy.
  // This layer is an answer to that. We could do something similar for Alt.
  // 
  // ## How does it work?
  //
  // We don't define any key to act as shift. Instead, the key that will shift keys activates this layer.
  // When entering the layer, shift is prerssed, and it is released when leaving the layer.
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
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PGUP, A(KC_LEFT), KC_UP,A(KC_RGHT),XXXXXXX,XXXXXXX,\
      KC_CAPS, KC_LCTL, KC_LALT, KC_LCMD, KC_LSFT, XXXXXXX,                   G(KC_LEFT), KC_LEFT, KC_DOWN, KC_RGHT,G(KC_RGHT),XXXXXXX,\
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PGDN, G(KC_V), G(KC_C), G(KC_X), XXXXXXX, XXXXXXX,\
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX \
    ),
  [_SYM] = LAYOUT_split_3x6_3( \
      XXXXXXX, XXXXXXX, S_EUR,   XXXXXXX, XXXXXXX, XXXXXXX,                      KC_DLR,  KC_LBRC, KC_RBRC, KC_PIPE, KC_AMPR, KC_BSLS,\
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
  // I try to register KC_LSFT MOD only when the _SHIFTED layer is activated, not every time it is active
  // I assume registering the KC_LSFT MOD is somehow better than registering a key, but this is pure speculation
  if(IS_LAYER_OFF(_SHIFTED) && IS_LAYER_ON_STATE(state, _SHIFTED)){
    // https://docs.qmk.fm/#/feature_macros?id=advanced-macro-functions
    register_mods(MOD_BIT(KC_LSFT));
    // register_code(KC_LSFT);

  } else if (IS_LAYER_ON(_SHIFTED) && IS_LAYER_OFF_STATE(state, _SHIFTED)){
    unregister_mods(MOD_BIT(KC_LSFT));
    // unregister_code(KC_LSFT);
  }
  return state;
}

uint16_t nonShiftedCode(uint16_t keycode) {
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
      bool lsftActive = get_mods() & MOD_BIT(KC_LSFT);
      bool rsftActive = get_mods() & MOD_BIT(KC_RSFT);
      bool capsLocked = host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK);
      // Caps lock does not affect symbols, but it does affect KC_E and KC_U
      bool needToUnCaps = capsLocked && (normalKeycode == KC_E || normalKeycode == KC_U);
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
      register_code16(nonShiftedCode(normalKeycode));
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
    } else {
      unregister_code(normalKeycode);
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Non Shifted key codes when shift is pressed:
  if (keycode >= NS_E && keycode <= NS_NUBS) {
    return process_non_shifted_key(record, nonShiftedCode(keycode));
  }

  // A rapid succession of ´ + E may ignore E (when it happens before the keyup of ´) because ´ is, in fact A(KB_E).
  // So the custom keycode RT_E (for ReType) simply registers KC_E (which unregisters it if alerady perssed, see actions.c:804)
  if (keycode == RT_E) {
    if (record->event.pressed){
      register_code(KC_E);
    } else {
      unregister_code(KC_E);
    }
    return false;
  } 

  return true;
}
