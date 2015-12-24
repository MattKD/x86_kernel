#include <stdarg.h>
#include <stdint.h>
#include "string.h"
#include "terminal.h"
#include "ioport.h"

static char main_term_buff[sizeof(kernel::Terminal)] 
  alignas(kernel::Terminal); 

namespace kernel {

uint16_t *const Terminal::vram = (uint16_t *)0xB8000;
Terminal *Terminal::active_term = nullptr;
Terminal *Terminal::main_term = nullptr;

void Terminal::initMainTerm()
{
  if (main_term == nullptr) {
    main_term = new(main_term_buff) Terminal(true);
  }
}

Terminal::Terminal(bool make_active) : x{0}, y{0}, color{0x0F} 
{ 
  if (make_active){
    active_term = this; 
  }
  clear();
}

Terminal::~Terminal() 
{ 
  main_term->makeActiveTerm(); 
}

void Terminal::makeActiveTerm() 
{ 
  active_term = this; 
  restoreScreen();
}

void Terminal::restoreScreen()
{
  memcpy(vram, buff, 2 * VRAM_BUF_LEN);
}

void Terminal::setCsrPos(int x_, int y_)
{
  if (x_ < 0) {
    x = 0; 
  } else if (x >= SCREEN_WIDTH) {
    x = SCREEN_WIDTH - 1;
  } else {
   x = x_;
  }

  if (y_ < 0) {
    y = 0; 
  } else if (y >= SCREEN_WIDTH) {
    y = SCREEN_WIDTH - 1;
  } else {
   y = y_;
  }

  updateCsr();
}

void Terminal::updateCsr()
{
  int idx = y * SCREEN_WIDTH + x; 

  kernel_outport(0x3D4, 14);
  kernel_outport(0x3D5, idx >> 8);
  kernel_outport(0x3D4, 15);
  kernel_outport(0x3D5, idx);
}

void Terminal::clear()
{
  uint16_t blank = ' ' | (color << 8);
  x = y = 0;
  memset16(vram, blank, VRAM_BUF_LEN);
  memset16(buff, blank, VRAM_BUF_LEN);
  updateCsr();
}

void Terminal::scrollDown()
{
  uint16_t *p = vram;

  for (int i = 0; i < SCREEN_HEIGHT - 1; ++i) {
    memcpy(p, p + SCREEN_WIDTH, 2 * SCREEN_WIDTH);
    p += SCREEN_WIDTH;
  }

  uint16_t blank = ' ' | (color << 8);
  memset16(p, blank, SCREEN_WIDTH);

  if (y > 0) {
    --y;
    updateCsr();
  }
}

void Terminal::writeChar(char c) 
{ 
  vram[index()] = buff[index()] = c | (color << 8);
}

void Terminal::putchar(char c)
{
  if (c == '\n' || c == '\r') {
    x = 0;
    ++y;
  } else if (c == '\b') {
    if (x > 0) {
      --x;
    } else if (y > 0) {
      x = SCREEN_WIDTH - 1;
      --y;
    } 
    writeChar(' ');
  } else {
    writeChar(c);

    if (++x == SCREEN_WIDTH) {
      x = 0;
      ++y;
    }
  }

  if (y == SCREEN_HEIGHT) {
    scrollDown();
  } else {
    updateCsr();
  }
}

void Terminal::puts(const char *str)
{
  while (*str) {
    putchar(*str++);
  }
}

void Terminal::put_d(int n)
{
  char nstr[20];
  int digits = 0;
  int negative = 0;

  if (n < 0) {
    negative = 1;
    n *= -1;
  }

  do {
    nstr[digits++] = (n % 10) + 48;
    n /= 10;
  } while (n != 0);

  if (negative) {
    nstr[digits++] = '-';
  }

  for (; digits > 0; --digits) {
    putchar(nstr[digits - 1]);
  }
}

void Terminal::put_u(unsigned n)
{
  char nstr[20];
  int digits = 0;

  do {
    nstr[digits++] = (n % 10) + 48;
    n /= 10;
  } while (n != 0);

  for (; digits > 0; --digits) {
    putchar(nstr[digits - 1]);
  }
}

void Terminal::put_x(unsigned n)
{
  char hex_chars[16] = {
    '0', '1', '2', '3', '4', '5', '6', '7', 
    '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
  };
  char nstr[20];
  int digits = 0;
  int digit;

  do {
    digit = n % 16;
    nstr[digits++] = hex_chars[digit];
    n /= 16;
  } while (n != 0);

  puts("0x");

  for (; digits > 0; --digits) {
    putchar(nstr[digits - 1]);
  }
}

void Terminal::sendKeyEvent(const KeyEvent &key_event)
{
  if (key_event.ascii != -1 && key_event.keydown) {
    Terminal::activeTerm().putchar(key_event.ascii);
  }
}

} // namespace kernel

