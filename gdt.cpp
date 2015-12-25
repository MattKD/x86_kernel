#include <stdint.h>
#include "gdt.h"
#include "kernel_panic.h"

using namespace kernel;

namespace {

struct GDT_Descriptor {
  uint16_t limit_lo;
  uint16_t base_lo;
  uint8_t base_mid;
  uint8_t access;
  uint8_t flags_limit_hi;
  uint8_t base_hi;
} __attribute__((packed));

static_assert(sizeof(GDT_Descriptor) == 8, "GDT_Descriptor must be 8 bytes");

struct GDT_Ptr {
  uint16_t size;
  uint32_t offset;
} __attribute__((packed));

static_assert(sizeof(GDT_Ptr) == 6, "GDT_Ptr must be 6 bytes");

const int GDT_SIZE = 3;
GDT_Descriptor gdt[GDT_SIZE];

} // unnamed namespace

extern "C" {

void kernel_gdt_load(); // gdt_load.s

GDT_Ptr gdt_ptr = { GDT_SIZE * 8 - 1, (uint32_t)gdt };

}

namespace kernel {

void GDT_setDescriptor(int idx, uint32_t base, uint32_t limit, 
                       uint8_t access, uint8_t flags)
{
  if (idx < 0 || idx >= GDT_SIZE) {
    kernel_panic("GDT_setDescriptor called with idx out of range");
    return;
  }

  GDT_Descriptor &d = gdt[idx];
  d.limit_lo = limit & 0xFFFF;
  d.base_lo = base & 0xFFFF;
  d.base_mid = (base >> 16) & 0xFF;
  d.access = access;
  d.flags_limit_hi = flags | ((limit >> 16) & 0x0F);
}

void GDT_init()
{
  const uint8_t code_access = Present | NonSystem | Exec | ReadWrite; //0x9A
  const uint8_t data_access = Present | NonSystem | ReadWrite; //0x92
  const uint8_t flags = BLOCK_4K | SIZE_32BIT;
  const int limit = 0xFFFFF; // 20bit 

  // Flat memory setup
  // Base: 0, Limit: 4G (2^20 w/4K blocks), Flags: 4K blocks | 32bit
  GDT_setDescriptor(0, 0, 0, 0, 0);
  GDT_setDescriptor(1, 0, limit, code_access, flags);
  GDT_setDescriptor(2, 0, limit, data_access, flags);
  kernel_gdt_load(); // gdt_load.s
}

} // namespace kernel


