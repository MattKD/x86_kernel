#include <stdint.h>
#include "terminal.h"
#include "stdio.h"

using namespace kernel;

extern "C"
void kmain()
{
  printf("d = %d, u = %u, x = %x, s = %s\n", -10, 100, 0xABC, "hello world");
  for (;;) { }
}

