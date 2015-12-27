#include "stdio.h"

extern "C" {

void kernel_halt(); // loader.s

void kernel_panic(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
  kernel_halt();
}

}
