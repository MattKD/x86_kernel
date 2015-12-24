#include <stdarg.h>
#include "terminal.h"

extern "C" {

void puts(const char *str)
{
  Terminal &t = Terminal::activeTerm();
  t.puts(str);
}

void printf(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);

  Terminal &term = Terminal::activeTerm();

  while (*fmt) {
    if (*fmt != '%') {
      term.putchar(*fmt);
    } else {
      ++fmt;
      if (*fmt == 'd') {
        term.put_d(va_arg(args, int));
      } else if (*fmt == 'u') {
        term.put_u(va_arg(args, unsigned));
      } else if (*fmt == 'x') {
        term.put_x(va_arg(args, unsigned));
      } else if (*fmt == 's') {
        const char *str = va_arg(args, const char *);
        for (; *str; ++str) {
          term.putchar(*str);
        }
      }
    }
    ++fmt;
  }
  va_end(args);
}

} // extern C
