#ifndef IDT_H
#define IDT_H

namespace kernel {

enum IDT_FLAG {
  TASK16 = 5,
  INT16 = 6,
  TRAP16 = 7,
  TASK32 = 13,
  INT32 = 14,
  TRAP32 = 15,
  RING3 = 96,
  PRESENT = 128
};

void IDT_init();
void IDT_add_ISR(int idx, void (*isr)());

} // namespace kernel

#endif
