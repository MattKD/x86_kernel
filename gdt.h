#ifndef GDT_H
#define GDT_H

namespace kernel {

enum GDT_Access {
  ReadWrite = 2, // Read for code, Write for data
  MemGrowsDown = 4, // for data
  LowerPrivAccess = 4, // for code
  Exec = 8, // code segment
  NonSystem = 16, // code/data segment
  Ring3 = 96,
  Present = 128 // For all segments
};

enum GDT_Flag {
  BLOCK_4K = 128,
  SIZE_32BIT = 64
};

void GDT_init();
void GDT_setDescriptor(int idx, uint32_t base, uint32_t limit, 
                       uint8_t access, uint8_t flags);

} // namespace kernel

#endif
