#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

extern "C" {

void kernel_panic(const char *fmt, ...);

extern uint32_t _kernel_start_addr;
extern uint32_t _kernel_end_addr;

}


namespace kernel {

void* allocFrame();
void freeFrame(void *frame);

}
#endif
