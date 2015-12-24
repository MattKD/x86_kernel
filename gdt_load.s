# gdt_ptr defined in gdt.cpp
# gdt has 3 entries: 0x00=null, 0x08=code, 0x10=data

.align 4
.global kernel_gdt_load
kernel_gdt_load:
  lgdt gdt_ptr
  ljmp $0x08, $load_rest # long jump to to cs register

load_rest: # load other segements as data
  movl $0x10, %eax
  movl %eax, %ds
  movl %eax, %es
  movl %eax, %fs
  movl %eax, %gs
  movl %eax, %ss
  ret
