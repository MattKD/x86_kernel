#include "kb.h"
#include "ioport.h"
#include "isr_irqs.h"
#include "terminal.h"

using namespace kernel;

namespace {

bool caps_lock = false;
//bool num_lock = false;
//bool scroll_lock = false;

struct Key {
  int keycode;
  int ascii;
  int shift_ascii;
};

Key keymap[128] =
{
  /* 0 */   {-1, -1, -1},              {KEY_ESCAPE, 27, 27},      {KEY_1, '1', '!'},  
            {KEY_2, '2', '@'},         {KEY_3, '3', '#'},         {KEY_4, '4', '$'},      
            {KEY_5, '5', '%'},         {KEY_6, '6', '^'},         {KEY_7, '7', '&'},     
  /* 9 */   {KEY_8, '8', '*'},         {KEY_9, '9', '('},         {KEY_0, '0', ')'},   
            {KEY_HYPHEN, '-', '_'},    {KEY_EQUAL, '=', '+'},     {KEY_BACKSPACE, '\b', '\b'},
            {KEY_TAB, '\t', '\t'},     {KEY_Q, 'q', 'Q'},         {KEY_W, 'w', 'W'},     
  /* 18 */  {KEY_E, 'e', 'E'},         {KEY_R, 'r', 'R'},         {KEY_T, 't', 'T'},       
            {KEY_Y, 'y', 'Y'},         {KEY_U, 'u', 'U'},         {KEY_I, 'i', 'I'},       
            {KEY_O, 'o', 'O'},         {KEY_P, 'p', 'P'},         {KEY_LBRACKET, '[', '{'},
  /* 27 */  {KEY_RBRACKET, ']', '}'},  {KEY_ENTER, '\r', '\r'},   {KEY_LCONTROL, -1, -1}, 
            {KEY_A, 'a', 'A'},         {KEY_S, 's', 'S'},         {KEY_D, 'd', 'D'},      
            {KEY_F, 'f', 'F'},         {KEY_G, 'g', 'G'},         {KEY_H, 'h', 'H'},         
  /* 36 */  {KEY_J, 'j', 'J'},         {KEY_K, 'k', 'K'},         {KEY_L, 'l', 'L'},    
            {KEY_SEMICOLON, ';', ':'}, {KEY_SQUOTE, '\'', '\"'},  {KEY_BTICK, '`', '~'},  
            {KEY_LSHIFT, -1, -1},	     {KEY_BSLASH, '\\', '|'},   {KEY_Z, 'z', 'Z'},  
  /* 45 */  {KEY_X, 'x', 'X'},         {KEY_C, 'c', 'C'},         {KEY_V, 'v', 'V'},    
            {KEY_B, 'b', 'B'},         {KEY_N, 'n', 'N'},         {KEY_M, 'm', 'M'},     
            {KEY_COMMA, ',', '<'},     {KEY_PERIOD, '.', '>'},    {KEY_SLASH, '/', '?'},   
  /* 54 */  {KEY_RSHIFT, -1, -1},      {KEY_PAD_MULT, '*', '*'},  {KEY_LALT, -1, -1},   
            {KEY_SPACE, ' ', ' '},     {KEY_CAPS_LOCK, -1, -1},   {KEY_F1, -1, -1},   
            {KEY_F2, -1, -1},          {KEY_F3, -1, -1},          {KEY_F4, -1, -1},   
  /* 63 */  {KEY_F5, -1, -1},          {KEY_F6, -1, -1},          {KEY_F7, -1, -1},     
            {KEY_F8, -1, -1},          {KEY_F9, -1, -1},          {KEY_F10, -1, -1}, 
            {KEY_NUM_LOCK, -1, -1},    {KEY_SCROLL_LOCK, -1, -1}, {KEY_PAD_7, '7', '7'}, 
  /* 72 */  {KEY_PAD_8, '8', '8'},     {KEY_PAD_9, '9', '9'},     {KEY_PAD_MINUS, '-', '-'}, 
            {KEY_PAD_4, '4', '4'},     {KEY_PAD_5, '5', '5'},     {KEY_PAD_6, '6', '6'},  
            {KEY_PAD_PLUS, '+', '+'},  {KEY_PAD_1, '1', '1'},     {KEY_PAD_2, '2', '2'},  
  /* 81 */  {KEY_PAD_3, '3', '3'},     {KEY_PAD_0, '0', '0'},     {KEY_PAD_DOT, '.', '.'}, 
            {-1, -1, -1},              {-1, -1, -1},              {-1, -1, -1},      
            {KEY_F11, -1, -1},         {KEY_F12, -1, -1},         {-1, -1, -1},               
  /* 90 */  {-1, -1, -1},              {-1, -1, -1},              {-1, -1, -1},               
            {-1, -1, -1},              {-1, -1, -1},              {-1, -1, -1},               
            {-1, -1, -1},              {-1, -1, -1},              {-1, -1, -1},               
  /* 99 */  {-1, -1, -1},              {-1, -1, -1},              {-1, -1, -1},               
            {-1, -1, -1},              {-1, -1, -1},              {-1, -1, -1},               
            {-1, -1, -1},              {-1, -1, -1},              {-1, -1, -1},               
  /* 108 */ {-1, -1, -1},              {-1, -1, -1},              {-1, -1, -1},               
            {-1, -1, -1},              {-1, -1, -1},              {-1, -1, -1},               
            {-1, -1, -1},              {-1, -1, -1},              {-1, -1, -1},               
  /* 117 */ {-1, -1, -1},              {-1, -1, -1},              {-1, -1, -1},               
            {-1, -1, -1},              {-1, -1, -1},              {-1, -1, -1},               
            {-1, -1, -1},              {-1, -1, -1},              {-1, -1, -1},               
  /* 126 */ {-1, -1, -1},              {-1, -1, -1}
};		

Key mb_keymap[128] =
{
  /* 0 */   {-1, -1, -1},           {-1, -1, -1},                {-1, -1, -1},         
            {-1, -1, -1},           {-1, -1, -1},                {-1, -1, -1},      
            {-1, -1, -1},           {-1, -1, -1},                {-1, -1, -1},        
  /* 9 */   {-1, -1, -1},           {-1, -1, -1},                {-1, -1, -1},        
            {-1, -1, -1},           {-1, -1, -1},                {-1, -1, -1},
            {-1, -1, -1},           {-1, -1, -1},                {-1, -1, -1},    
  /* 18 */  {-1, -1, -1},           {KEY_PAUSE, -1, -1},         {-1, -1, -1},     
            {-1, -1, -1},           {-1, -1, -1},                {-1, -1, -1},     
            {-1, -1, -1},           {-1, -1, -1},                {-1, -1, -1},         
  /* 27 */  {-1, -1, -1},           {KEY_PAD_ENTER, '\r', '\r'}, {KEY_RCONTROL, -1, -1}, 
            {-1, -1, -1},           {-1, -1, -1},                {-1, -1, -1},     
            {-1, -1, -1},           {-1, -1, -1},                {-1, -1, -1},      
  /* 36 */  {-1, -1, -1},           {-1, -1, -1},                {-1, -1, -1},        
            {-1, -1, -1},           {-1, -1, -1},                {-1, -1, -1},        
            {-1, -1, -1},	          {-1, -1, -1},                {-1, -1, -1},              
  /* 45 */  {-1, -1, -1},           {-1, -1, -1},                {-1, -1, -1},      
            {-1, -1, -1},           {-1, -1, -1},                {-1, -1, -1},  
            {-1, -1, -1},           {-1, -1, -1},                {KEY_PAD_DIV, '/', '/'},
  /* 54 */  {-1, -1, -1},           {KEY_PRINT, -1, -1},         {KEY_RALT, -1, -1},    
            {-1, -1, -1},           {-1, -1, -1},                {-1, -1, -1},  
            {-1, -1, -1},           {-1, -1, -1},                {-1, -1, -1},    
  /* 63 */  {-1, -1, -1},           {-1, -1, -1},                {-1, -1, -1},     
            {-1, -1, -1},           {-1, -1, -1},                {-1, -1, -1},         
            {-1, -1, -1},           {-1, -1, -1},                {KEY_HOME, -1, -1},  
  /* 72 */  {KEY_UP, -1, -1},       {KEY_PAGEUP, -1, -1},         {-1, -1, -1}, 
            {KEY_LEFT, -1, -1},     {-1, -1, -1},                {KEY_RIGHT, -1, -1},  
            {-1, -1, -1},           {KEY_END, -1, -1},           {KEY_DOWN, -1, -1}, 
  /* 81 */  {KEY_PAGEDOWN, -1, -1}, {KEY_INSERT, -1, -1},        {KEY_DELETE, -1, -1},   
            {-1, -1, -1},           {-1, -1, -1},                {-1, -1, -1},       
            {-1, -1, -1},           {-1, -1, -1},                {-1, -1, -1},         
  /* 90 */  {-1, -1, -1},           {KEY_LSUPER, -1, -1},        {KEY_RSUPER, -1, -1}, 
            {KEY_APPS, -1, -1},     {-1, -1, -1},                {-1, -1, -1},      
            {-1, -1, -1},	          {-1, -1, -1},                {-1, -1, -1},              
  /* 99 */  {-1, -1, -1},	          {-1, -1, -1},                {-1, -1, -1},              
            {-1, -1, -1},	          {-1, -1, -1},                {-1, -1, -1},              
            {-1, -1, -1},	          {-1, -1, -1},                {-1, -1, -1},              
  /* 108 */ {-1, -1, -1},	          {-1, -1, -1},                {-1, -1, -1},              
            {-1, -1, -1},	          {-1, -1, -1},                {-1, -1, -1},              
            {-1, -1, -1},	          {-1, -1, -1},                {-1, -1, -1},              
  /* 117 */ {-1, -1, -1},	          {-1, -1, -1},                {-1, -1, -1},              
            {-1, -1, -1},	          {-1, -1, -1},                {-1, -1, -1},              
            {-1, -1, -1},	          {-1, -1, -1},                {-1, -1, -1},              
  /* 126 */ {-1, -1, -1},	          {-1, -1, -1}
};		

bool kb_state[NUM_KEYS] = {0};

// IRQ 1
// Handles the keyboard interrupt
void IRQ_keyboardHandler()
{
  bool keydown = true;
  bool shift = false;
  int scancode;
  Key k;

  // Read from the keyboard's data
  scancode = kernel_inport(0x60);
  if (scancode < 0xE0) { // standard 1 byte keys
    if (scancode & 0x80) { // check if key is being released
      scancode -= 0x80;
      keydown = false;
    }    
    k = keymap[scancode];
  } else { // key is one of 17 multibyte keys
    scancode = kernel_inport(0x60); // get second byte
    if (scancode & 0x80) { // check if key is being released
      scancode -= 0x80;
      keydown = false;
    }    
    k = mb_keymap[scancode];
  }
  
  if (k.keycode != -1) {
    KeyEvent kevent;
    kevent.keycode = k.keycode;
    kb_state[kevent.keycode] = keydown;

    if (keydown && kevent.keycode == KEY_CAPS_LOCK) {
      caps_lock = caps_lock ? false : true;
    }

    if (kb_state[KEY_LSHIFT] || kb_state[KEY_RSHIFT]) {
      shift = true;
    }

    // only use caps lock for ascii characters
    if (k.ascii >= 'a' && k.ascii <= 'z') {
      if (caps_lock) {
        shift = !shift;
      }
    }

    kevent.ascii = shift ? k.shift_ascii : k.ascii;
    kevent.keydown = keydown;
   
    Terminal::sendKeyEvent(kevent);
  }
}

} // unnamed namespace

namespace kernel {

void keyboardInit()
{
  IRQ_addHandler(1, IRQ_keyboardHandler);
}

}
