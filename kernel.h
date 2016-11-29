#ifndef KERNEL_H
#define KERNEL_H

extern "C" void kernel_panic(const char *fmt, ...);

namespace kernel {

void* allocFrame();
void freeFrame(void *frame);

}
#endif
