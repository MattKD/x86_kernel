#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>
#include "kb.h"

namespace kernel {

class Terminal {
public:
  Terminal(bool make_active = true);
  ~Terminal();

  void makeActiveTerm();
  void setColor(uint8_t c) { color = c; }
  void setCsrPos(int x, int y);
  void clear();
  void scrollDown();
  void putchar(char c);

  void putstr(const char *str)
  {
    while (*str) {
      putchar(*str++);
    }
  }

  void puts(const char *str)
  {
    putstr(str);
    putchar('\n');
  }

  void put_d(int);
  void put_x(unsigned);
  void put_u(unsigned);
  void put_f(double);

  static Terminal& activeTerm() { return *active_term; }
  static Terminal& mainTerm() { return *main_term; }
  static void initMainTerm();
  static void sendKeyEvent(const KeyEvent &kevent);

private:
  static const int SCREEN_WIDTH = 80;
  static const int SCREEN_HEIGHT = 25;
  static const int VRAM_BUF_LEN = SCREEN_WIDTH * SCREEN_HEIGHT;

  int x, y;
  uint16_t buff[VRAM_BUF_LEN];
  uint8_t color;

  void updateCsr();
  int index() { return y * SCREEN_WIDTH + x; }
  void writeChar(char c); 
  void restoreScreen();

  static uint16_t *const vram;
  static Terminal *active_term;
  static Terminal *main_term;
};

} // namespace kernel
#endif
