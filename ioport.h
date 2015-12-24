#ifndef KERNEL_IOPORT_H
#define KERNEL_IOPORT_H

#include <stdint.h>

extern "C" {

void kernel_outport(uint16_t port, uint8_t data);
uint8_t kernel_inport(uint16_t port);

}

#endif
