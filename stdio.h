#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>

extern "C" {

void puts(const char *str);
void vprintf(const char *fmt, va_list args);

inline void printf(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
}

} // extern C

#endif
