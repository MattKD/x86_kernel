#include "stdio.h"

extern "C" {

void kernel_halt(); // loader.s

void kernel_panic(const char *msg)
{
  puts(msg);
  kernel_halt();
}

}
