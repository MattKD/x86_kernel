#ifndef KERNEL_KB_H_
#define KERNEL_KB_H_

#include <stdint.h>

namespace kernel {

struct KeyEvent {
  int keycode;
  int ascii;
  bool keydown; 
};

void keyboardInit();
void disableKeyboardInput();
void enableKeyboardInput();
bool isKeyboardDisabled();

enum Key {
  KEY_ESCAPE = 0,
  KEY_BTICK = 1,
  KEY_HYPHEN = 2,
  KEY_EQUAL = 3,
  KEY_BACKSPACE = 4,
  KEY_TAB = 5,
  KEY_LBRACKET = 6,
  KEY_RBRACKET = 7,
  KEY_BSLASH = 8,
  KEY_CAPS_LOCK = 9,
  KEY_SEMICOLON = 10,
  KEY_SQUOTE = 11,
  KEY_ENTER = 12,
  KEY_LSHIFT = 13,
  KEY_COMMA = 14,
  KEY_PERIOD = 15,
  KEY_SLASH = 16,
  KEY_RSHIFT = 17,
  KEY_LCONTROL = 18,
  KEY_LSUPER = 19,
  KEY_LALT = 20,
  KEY_SPACE = 21,
  KEY_RALT = 22,
  KEY_RSUPER = 23,
  KEY_APPS = 24,
  KEY_RCONTROL = 25,
  KEY_0 = 26,
  KEY_1 = 27,
  KEY_2 = 28,
  KEY_3 = 29,
  KEY_4 = 30,
  KEY_5 = 31,
  KEY_6 = 32,
  KEY_7 = 33,
  KEY_8 = 34,
  KEY_9 = 35,
  KEY_A = 36,
  KEY_B = 37,
  KEY_C = 38,
  KEY_D = 39,
  KEY_E = 40,
  KEY_F = 41,
  KEY_G = 42,
  KEY_H = 43,
  KEY_I = 44,
  KEY_J = 45,
  KEY_K = 46,
  KEY_L = 47,
  KEY_M = 48,
  KEY_N = 49,
  KEY_O = 50,
  KEY_P = 51,
  KEY_Q = 52,
  KEY_R = 53,
  KEY_S = 54,
  KEY_T = 55,
  KEY_U = 56,
  KEY_V = 57,
  KEY_W = 58,
  KEY_X = 59,
  KEY_Y = 60,
  KEY_Z = 61,
  KEY_PRINT = 62,
  KEY_SCROLL_LOCK = 63,
  KEY_PAUSE = 64,
  KEY_INSERT = 65,
  KEY_HOME = 66,
  KEY_PAGEUP = 67,
  KEY_DELETE = 68,
  KEY_END = 69,
  KEY_PAGEDOWN = 70,
  KEY_UP = 71,
  KEY_LEFT = 72,
  KEY_DOWN = 73,
  KEY_RIGHT = 74,
  KEY_NUM_LOCK = 75,
  KEY_PAD_DIV = 76,
  KEY_PAD_MULT = 77,
  KEY_PAD_MINUS = 78,
  KEY_PAD_PLUS = 79,
  KEY_PAD_DOT = 80,
  KEY_PAD_ENTER = 81,
  KEY_PAD_0 = 82,
  KEY_PAD_1 = 83,
  KEY_PAD_2 = 84,
  KEY_PAD_3 = 85,
  KEY_PAD_4 = 86,
  KEY_PAD_5 = 87,
  KEY_PAD_6 = 88,
  KEY_PAD_7 = 89,
  KEY_PAD_8 = 90,
  KEY_PAD_9 = 91,
  KEY_F1 = 92,
  KEY_F2 = 93,
  KEY_F3 = 94,
  KEY_F4 = 95,
  KEY_F5 = 96,
  KEY_F6 = 97,
  KEY_F7 = 98,
  KEY_F8 = 99,
  KEY_F9 = 100,
  KEY_F10 = 101,
  KEY_F11 = 102,
  KEY_F12 = 103,
  NUM_KEYS = 104
}; // enum Key

} // namespace kernel

#endif
