# idt_ptr defined in idt.cpp

.align 4
.global kernel_idt_load
kernel_idt_load:
  lidt idt_ptr
  ret
