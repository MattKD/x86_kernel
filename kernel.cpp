#include <stdint.h>
#include "kernel.h"
#include "terminal.h"
#include "stdio.h"
#include "timer.h"

using namespace kernel;

extern "C"
void kmain()
{

  printf("printf test:\n");
  printf("%% = %% (percent sign), d = %d (-10), u = %u (100), "
         "x = %x (0xABC), f = %f (3.141592), "
         "s = %s ('hello world')\n",
         -10, 100, 0xABC, 3.141592, "hello world");

  // allocFrame used just for testing
  void *frame = allocFrame(); // 4KB frame
  printf("frame address %x\n", (unsigned)frame);
  // causes page fault, and kernel panic
  int *np = (int*)frame;
  *np = -10;
  freeFrame(frame);

  printf("Sleep for 5 secs\n");
  for (int i = 0; i < 5; i++) {
    sleep(1000);
    printf("%d\n", i+1);
  }
  printf("Done sleeping\n");

  // loop forever
  for (;;) { }
}

