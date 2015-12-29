#include <stdint.h>
#include "string.h"
#include "idt.h"
#include "kernel_panic.h"


using namespace kernel;

namespace {

struct IDT_Descriptor {
  uint16_t handler_addr_lo;
  uint16_t segment_selector;
  uint8_t null;
  uint8_t flags;
  uint16_t handler_addr_hi;
} __attribute__((packed));

static_assert(sizeof(IDT_Descriptor) == 8, "IDT_Descriptor must be 8 bytes");

struct IDT_Ptr {
  uint16_t limit;
  uint32_t idt_addr;
} __attribute__((packed));

static_assert(sizeof(IDT_Ptr) == 6, "IDT_Ptr must be 6 bytes");

const int IDT_SIZE = 256;
IDT_Descriptor idt[IDT_SIZE];

} // unnamed namespace

extern "C" {

void kernel_idt_load(); // idt_load.s

IDT_Ptr idt_ptr = { IDT_SIZE * 8 - 1, (uint32_t)idt };

}

namespace kernel {

void IDT_init() 
{
  memset(idt, 0, IDT_SIZE * 8);
  kernel_idt_load();
}

void IDT_add_ISR(int idx, void (*isr)())
{
  if (idx < 0 || idx >= IDT_SIZE) {
    kernel_panic("IDT_add_ISR called with idx out of range.\n"
        "idx = %d, range=[0,%d]", idx, IDT_SIZE-1);
    return;
  }

  IDT_Descriptor &d = idt[idx];
  d.handler_addr_lo = (uint32_t)isr & 0xFFFF;
  d.segment_selector = 0x08; // code selector in gdt
  d.null = 0;
  d.flags = INT32 | PRESENT;
  d.handler_addr_hi = (uint32_t)isr >> 16;
}

} // namespace kernel
