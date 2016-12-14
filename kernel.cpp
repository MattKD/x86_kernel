#include <stdint.h>
#include "terminal.h"
#include "stdio.h"
#include "kernel.h"

using namespace kernel;

extern "C"
void kmain()
{
  /*
  void *frame = allocFrame(); // 4KB frame
  int *np = (int*)frame;
  *np = -10;
  */

  printf("printf test:\n");
  printf("%% = %% (percent sign), d = %d (-10), u = %u (100), "
         "x = %x (0xABC), f = %f (3.141592), "
         "s = %s ('hello world')\n",
         -10, 100, 0xABC, 3.141592, "hello world");

  //freeFrame(frame);

  for (;;) { }
}

