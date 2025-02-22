/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H




//void rgb_matrix_indicators_user(void) {
//	if (host_keyboard_led_state().caps_lock) {
//		rgb_matrix_set_color_all(RGB_RED);
//		return;
//	}
//}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
//    if (host_keyboard_led_state().caps_lock) {
//    	rgb_matrix_set_color_all(RGB_RED);
//    	/*
//        for (uint8_t i = led_min; i <= led_max; i++) {
//            if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
//                rgb_matrix_set_color(i, RGB_RED);
//            }
//        }
//        */
//    }

    uint8_t layer = get_highest_layer(layer_state);
    if(layer>1){
    	if (!host_keyboard_led_state().caps_lock) {
    		rgb_matrix_set_color_all(RGB_OFF);
    	}
    	//rgb_matrix_set_color(layer, RGB_PURPLE);
    	rgb_matrix_set_color(layer, RGB_RED);
    }
    /*
	switch (get_highest_layer(layer_state)) {
		case 2:
			rgb_matrix_set_color(2, RGB_PURPLE);
			return;
		case 3:
			rgb_matrix_set_color(3, RGB_PURPLE);
			return;
		case 4:
			rgb_matrix_set_color(4, RGB_PURPLE);
			return;
	}
	*/
}

void caplock_layer_rgb(layer_state_t state){
	if (host_keyboard_led_state().caps_lock) {
		rgb_matrix_enable_noeeprom();
		return;
	}
	switch (get_highest_layer(state)) {
		case 2:
			rgb_matrix_enable_noeeprom();
			return;
		case 3:
			rgb_matrix_enable_noeeprom();
			return;
		case 4:
			rgb_matrix_enable_noeeprom();
			return;
	}
	rgb_matrix_reload_from_eeprom();

}
bool led_update_user(led_t led_state) {
	caplock_layer_rgb(layer_state);
	/*
    static uint8_t caps_state = 0;
    if (caps_state != led_state.caps_lock) {
    	caps_state = led_state.caps_lock;
    	if(led_state.caps_lock){
    		rgb_matrix_enable_noeeprom();
    	}else{

    	}
        led_state.caps_lock ? PLAY_SONG(caps_on) : PLAY_SONG(caps_off);
    }
    */
    return true;
}


layer_state_t layer_state_set_user(layer_state_t state) {
	caplock_layer_rgb(state);
	/*
	if (host_keyboard_led_state().caps_lock) {
		rgb_matrix_enable_noeeprom();
		return state;
	}
	switch (get_highest_layer(state)) {
		case 2:
			rgb_matrix_enable_noeeprom();
			return state;
			break;
		case 3:
			rgb_matrix_enable_noeeprom();
			return state;
			break;
		case 4:
			rgb_matrix_enable_noeeprom();
			return state;
			break;
		default:
			break;
	}
	rgb_matrix_reload_from_eeprom();
	*/
	return state;
}





enum layers{
    MAC_BASE,
    WIN_BASE,
    _FN1,
    _FN2,
    _FN3
};

enum custom_keycodes {
    KC_MISSION_CONTROL = USER00,
    KC_LAUNCHPAD,
    KC_LOPTN,
    KC_ROPTN,
    KC_LCMMD,
    KC_RCMMD,
    KC_TASK_VIEW,
    KC_FILE_EXPLORER
};

#define KC_MCTL KC_MISSION_CONTROL
#define KC_LPAD KC_LAUNCHPAD
#define KC_TASK KC_TASK_VIEW
#define KC_FLXP KC_FILE_EXPLORER

typedef struct PACKED {
    uint8_t len;
    uint8_t keycode[2];
} key_combination_t;

key_combination_t key_comb_list[2] = {
    {2, {KC_LWIN, KC_TAB}},
    {2, {KC_LWIN, KC_E}}
};

static uint8_t mac_keycode[4] = { KC_LOPT, KC_ROPT, KC_LCMD, KC_RCMD };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_all(
                                                                                                                                                    KC_VOLD, KC_VOLU,
        KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,     KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,             KC_MUTE,
        KC_TAB,  KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,     KC_U,     KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,             KC_DEL,
        KC_CAPS, KC_A,     KC_S,     KC_D,    KC_F,    KC_G,              KC_H,     KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,              KC_HOME,
        KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,     KC_B,     KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, KC_UP,
        KC_LCTL, KC_LOPTN, KC_LCMMD,          KC_SPC,           MO(_FN1), MO(_FN3),          KC_SPC,            KC_RCMMD,           KC_LEFT, KC_DOWN,    KC_RGHT),

    [WIN_BASE] = LAYOUT_all(
                                                                                                                                                    KC_VOLD, KC_VOLU,
        KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,     KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,             KC_MUTE,
        KC_TAB,  KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,     KC_U,     KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,             KC_DEL,
        KC_CAPS, KC_A,     KC_S,     KC_D,    KC_F,    KC_G,              KC_H,     KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,              KC_HOME,
        KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,     KC_B,     KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, KC_UP,
        KC_LCTL, KC_LWIN,  KC_LALT,           KC_SPC,           MO(_FN2), MO(_FN3),          KC_SPC,            KC_RALT,            KC_LEFT, KC_DOWN,    KC_RGHT),

    [_FN1] = LAYOUT_all(
                                                                                                                                                    RGB_VAD, RGB_VAI,
        KC_GRV,  KC_BRID,  KC_BRIU,  KC_MCTL, KC_LPAD, RGB_VAD, RGB_VAI,  KC_MPRV,  KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,             RGB_TOG,
        RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI, _______,  _______,  _______, _______, _______,  _______,  _______,  _______,             _______,
        _______, RGB_RMOD, RGB_VAD,  RGB_HUD, RGB_SAD, RGB_SPD,           _______,  _______, _______, _______,  _______,  _______,  _______,             _______,
        _______,           _______,  _______, _______, _______, _______,  _______,  NK_TOGG, _______, _______,  _______,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,  _______,           _______,           _______,            _______, _______,    _______),

    [_FN2] = LAYOUT_all(
                                                                                                                                                    RGB_VAD, RGB_VAI,
        KC_GRV,  KC_BRID,  KC_BRIU,  KC_TASK, KC_FLXP, RGB_VAD, RGB_VAI,  KC_MPRV,  KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,             RGB_TOG,
        RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI, _______,  _______,  _______, _______, _______,  _______,  _______,  _______,             _______,
        _______, RGB_RMOD, RGB_VAD,  RGB_HUD, RGB_SAD, RGB_SPD,           _______,  _______, _______, _______,  _______,  _______,  _______,             _______,
        _______,           _______,  _______, _______, _______, _______,  _______,  NK_TOGG, _______, _______,  _______,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,  _______,           _______,           _______,            _______, _______,    _______),

    [_FN3] = LAYOUT_all(
                                                                                                                                                    _______, _______,
        KC_TILD, KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_F7,    KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   _______,             _______,
        RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI, _______,  _______,  _______, _______, _______,  _______,  _______,  _______,             _______,
        _______, RGB_RMOD, RGB_VAD,  RGB_HUD, RGB_SAD, RGB_SPD,           _______,  _______, _______, _______,  _______,  _______,  _______,             _______,
        _______,           _______,  _______, _______, _______, _______,  _______,  _______, _______, _______,  _______,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,  _______,           _______,           _______,            _______, _______,    _______)
};

// clang-format on

#if defined(VIA_ENABLE) && defined(ENCODER_ENABLE)

#define ENCODERS 1

static uint8_t  encoder_state[ENCODERS] = {0};
static keypos_t encoder_cw[ENCODERS]    = {{ 4, 4 }};
static keypos_t encoder_ccw[ENCODERS]  = {{ 5, 4 }};

void encoder_action_unregister(void) {
    for (int index = 0; index < ENCODERS; ++index) {
        if (encoder_state[index]) {
            keyevent_t encoder_event = (keyevent_t) {
                .key = encoder_state[index] >> 1 ? encoder_cw[index] : encoder_ccw[index],
                .pressed = false,
                .time = (timer_read() | 1)
            };
            encoder_state[index] = 0;
            action_exec(encoder_event);
        }
    }
}

void encoder_action_register(uint8_t index, bool clockwise) {
    keyevent_t encoder_event = (keyevent_t) {
        .key = clockwise ? encoder_cw[index] : encoder_ccw[index],
        .pressed = true,
        .time = (timer_read() | 1)
    };
    encoder_state[index] = (clockwise ^ 1) | (clockwise << 1);
    action_exec(encoder_event);
}

void matrix_scan_user(void) {
    encoder_action_unregister();
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    encoder_action_register(index, clockwise);
    return false;
};

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_MCTL:
            if (record->event.pressed) {
                host_consumer_send(0x29F);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
        case KC_LPAD:
            if (record->event.pressed) {
                host_consumer_send(0x2A0);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
        case KC_LOPTN:
        case KC_ROPTN:
        case KC_LCMMD:
        case KC_RCMMD:
            if (record->event.pressed) {
                register_code(mac_keycode[keycode - KC_LOPTN]);
            } else {
                unregister_code(mac_keycode[keycode - KC_LOPTN]);
            }
            return false;  // Skip all further processing of this key
        case KC_TASK:
        case KC_FLXP:
            if (record->event.pressed) {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    register_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            } else {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    unregister_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            }
            return false;  // Skip all further processing of this key
        default:
            return true;  // Process all other keycodes normally
    }
}
