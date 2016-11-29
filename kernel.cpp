#include <stdint.h>
#include "terminal.h"
#include "stdio.h"
#include "kernel.h"

using namespace kernel;

extern "C"
void kmain()
{
  void *frame = allocFrame(); // 4KB frame
  int *np = (int*)frame;
  *np = -10;

  printf("printf test:\n");
  printf("d = %d (expect -10), u = %u (expect 100), x = %x (expect 0xABC), "
         "s = %s (expect 'hello world')\n", *np, 100, 0xABC, "hello world");

  freeFrame(frame);

  for (;;) { }
}

