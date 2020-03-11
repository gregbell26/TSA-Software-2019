//
// Created by Corbin Estes on 3/4/20.
//

#ifndef ACRYLIC2D_KEYS_H
#define ACRYLIC2D_KEYS_H

#include <functional>
#include <map>
#include "../BackendAPIs/Plexi2DRenderer/acrylic_plexiRenderer_core.hpp"

enum KeyCode {
    A2D_SPACE = ' ', A2D_APOSTROPHE /* ' */ = '\'', A2D_COMMA /* , */ = ',', A2D_MINUS /* - */ = '-',
    A2D_PERIOD /* . */ = '.', A2D_SLASH = '/', A2D_0 = '0', A2D_1 = '1', A2D_2 = '2', A2D_3 = '3', A2D_4 = '4',
    A2D_5 = '5', A2D_6 = '6', A2D_7='7', A2D_8 = '8', A2D_9='9', A2D_SEMICOLON =';', A2D_EQUAL = '=', A2D_A = 'A',
    A2D_B = 'B', A2D_C = 'C', A2D_D = 'D', A2D_E = 'E', A2D_F = 'F', A2D_G = 'G', A2D_H = 'H', A2D_I='I', A2D_J='J',
    A2D_K='K',A2D_L='L', A2D_M='M', A2D_N='N', A2D_O='O', A2D_P='P', A2D_Q='Q', A2D_R='R', A2D_S='S', A2D_T='T',
    A2D_U='U', A2D_V='V', A2D_W='W', A2D_X='X', A2D_Y='Y', A2D_Z='Z', A2D_LEFT_BRACKET ='[', A2D_BACKSLASH='\\',
    A2D_RIGHT_BRACKET =']',A2D_GRAVE_ACCENT ='`', A2D_ESCAPE = 27, A2D_ENTER='\n', A2D_a = 'a', A2D_b = 'b',
    A2D_c = 'c', A2D_d = 'd', A2D_e = 'e', A2D_f = 'f', A2D_g = 'g', A2D_h = 'h', A2D_i='i', A2D_j='j',
    A2D_k='k',A2D_l='l', A2D_m='m', A2D_n='n', A2D_o='o', A2D_p='p', A2D_q='q', A2D_r='r', A2D_s='s', A2D_t='t',
    A2D_u='u', A2D_v='v', A2D_w='w', A2D_x='x', A2D_y='y', A2D_z='z', A2D_LEFT_PAREN='(', A2D_RIGHT_PAREN=')',
    A2D_LEFT_CURL = '{', A2D_RIGHT_CURL = '}', A2D_UNDERSCORE = '_', A2D_PLUS = '+', A2D_TILDA = '~', A2D_ASTERIX = '*',
    A2D_EXCLAMATION = '!', A2D_AT = '@', A2D_POUND = '#', A2D_DOLLAR = '$',
    A2D_TAB='\t',
    A2D_BACKSPACE='\b',
    A2D_INSERT,
    A2D_DELETE=127,
    A2D_RIGHT,
    A2D_LEFT,
    A2D_DOWN,
    A2D_UP,
    A2D_PAGE_UP,
    A2D_PAGE_DOWN,
    A2D_HOME,
    A2D_END,
    A2D_CAPS_LOCK,
    A2D_SCROLL_LOCK,
    A2D_NUM_LOCK,
    A2D_PRINT_SCREEN,
    A2D_PAUSE,
    A2D_F1,
    A2D_F2,
    A2D_F3,
    A2D_F4,
    A2D_F5,
    A2D_F6,
    A2D_F7,
    A2D_F8,
    A2D_F9,
    A2D_F10,
    A2D_F11,
    A2D_F12,
    A2D_F13,
    A2D_F14,
    A2D_F15,
    A2D_F16,
    A2D_F17,
    A2D_F18,
    A2D_F19,
    A2D_F20,
    A2D_F21,
    A2D_F22,
    A2D_F23,
    A2D_F24,
    A2D_F25,
    A2D_KP_0,
    A2D_KP_1,
    A2D_KP_2,
    A2D_KP_3,
    A2D_KP_4,
    A2D_KP_5,
    A2D_KP_6,
    A2D_KP_7,
    A2D_KP_8,
    A2D_KP_9,
    A2D_KP_DECIMAL,
    A2D_KP_DIVIDE,
    A2D_KP_MULTIPLY,
    A2D_KP_SUBTRACT,
    A2D_KP_ADD,
    A2D_KP_ENTER,
    A2D_KP_EQUAL,
    A2D_LEFT_SHIFT,
    A2D_LEFT_CONTROL,
    A2D_LEFT_ALT,
    A2D_LEFT_SUPER,
    A2D_RIGHT_SHIFT,
    A2D_RIGHT_CONTROL,
    A2D_RIGHT_ALT,
    A2D_RIGHT_SUPER,
    A2D_MENU,
};

enum MouseButtons {
    A2D_MOUSE_BUTTON_LEFT =  0,
    A2D_MOUSE_BUTTON_RIGHT =  1,
    A2D_MOUSE_BUTTON_3 =  2,
    A2D_MOUSE_BUTTON_4 =  3,
    A2D_MOUSE_BUTTON_5 =  4,
    A2D_MOUSE_BUTTON_6 =  5,
    A2D_MOUSE_BUTTON_7 =  6,
    A2D_MOUSE_BUTTON_8 =  7,
};

enum ModCode {
    A2D_MOD_NONE = 0,
    A2D_MOD_SHIFT = 1,
    A2D_MOD_CONTROL = 2,
    A2D_MOD_ALT = 4,
    A2D_MOD_SUPER = 8,
    A2D_MOD_CAPS_LOCK = 16,
    A2D_MOD_NUM_LOCK = 32,
};

enum keyEvents{
    pressed,
    held,
    released,
};

struct KeyMod{
    KeyCode key;
    int mods;
    keyEvents event;
    explicit KeyMod(KeyCode _key){
        key = _key;
        mods = 0;
        event = pressed;
    }
    KeyMod(KeyCode _key, int modSum){
        key = _key;
        mods = modSum;
        event = pressed;
    }
    KeyMod(KeyCode _key, int modSum, keyEvents _event){
        key = _key;
        mods = modSum;
        event = _event;
    }
};

struct A2D_coordPair{
    double x;
    double y;
};

#endif //ACRYLIC2D_KEYS_H
