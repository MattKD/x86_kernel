#include "kernel.h"
#include "idt.h"
#include "isr_irqs.h"
#include "ioport.h"
#include "stdio.h"

extern "C" {

void kernel_isr32();
void kernel_isr33();
void kernel_isr34();
void kernel_isr35();
void kernel_isr36();
void kernel_isr37();
void kernel_isr38();
void kernel_isr39();
void kernel_isr40();
void kernel_isr41();
void kernel_isr42();
void kernel_isr43();
void kernel_isr44();
void kernel_isr45();
void kernel_isr46();
void kernel_isr47();

} // extern C

namespace {

kernel::IRQ_Handler irq_handlers[16] = { 0 };

enum PIC_Constants {
  PIC1_CMD = 0x20,
  PIC2_CMD = 0xA0,
  PIC1_DATA = 0x21,
  PIC2_DATA = 0xA1
};
 
} // unnamed namespace

namespace kernel {
 
void PIC_init()
{
  uint8_t mask1 = kernel_inport(PIC1_DATA); // save PIC1 mask
  uint8_t mask2 = kernel_inport(PIC2_DATA); // save PIC1 mask
  kernel_outport(PIC1_CMD, 0x11); //ICW1 Init w/bit 0 for ICW4
  kernel_outport(PIC2_CMD, 0x11); //ICW1 Init w/bit 0 for ICW4
  kernel_outport(PIC1_DATA, 32); // IRQ0 = idt[32]
  kernel_outport(PIC2_DATA, 40); // IRQ0 = idt[40]
  // PIC1 is connected to PIC2 through IRQ2 (bit 2 = 4)
  kernel_outport(PIC1_DATA, 4); 
  kernel_outport(PIC2_DATA, 2); // PIC2 ID is 2 for IRQ2
  kernel_outport(PIC1_DATA, 1); // for 8086
  kernel_outport(PIC2_DATA, 1); // for 8086
  kernel_outport(PIC1_DATA, mask1); // restore PIC1 mask
  kernel_outport(PIC2_DATA, mask2); // restore PIC1 mask
}

void IDT_install_IRQ_ISRs()
{
  IDT_add_ISR(32, ::kernel_isr32);
  IDT_add_ISR(33, ::kernel_isr33);
  IDT_add_ISR(34, ::kernel_isr34);
  IDT_add_ISR(35, ::kernel_isr35);
  IDT_add_ISR(36, ::kernel_isr36);
  IDT_add_ISR(37, ::kernel_isr37);
  IDT_add_ISR(38, ::kernel_isr38);
  IDT_add_ISR(39, ::kernel_isr39);
  IDT_add_ISR(40, ::kernel_isr40);
  IDT_add_ISR(41, ::kernel_isr41);
  IDT_add_ISR(42, ::kernel_isr42);
  IDT_add_ISR(43, ::kernel_isr43);
  IDT_add_ISR(44, ::kernel_isr44);
  IDT_add_ISR(45, ::kernel_isr45);
  IDT_add_ISR(46, ::kernel_isr46);
  IDT_add_ISR(47, ::kernel_isr47);
}

void IRQ_addHandler(int irq, IRQ_Handler f)
{
  if (irq < 0 || irq > 15) {
    kernel_panic("Cannot add IRQ handler outside range 0 - 15");
  }
  ::irq_handlers[irq] = f;
}

} // namespace kernel

extern "C" {
 
void kernel_irq_handler(int irq)
{
  kernel::IRQ_Handler f = irq_handlers[irq];
  if (f) {
    f();
  }

  // Send End of Interrupt to PIC2 if IRQ 8-15
  if (irq > 7) {
    kernel_outport(PIC2_CMD, 0x20); 
  }

  kernel_outport(PIC1_CMD, 0x20); // Always send End of Interrupt to PIC1
}

} // extern C

