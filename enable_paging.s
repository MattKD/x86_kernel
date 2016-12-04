# page_directory is defined in paging.cpp

.align 4
.global kernel_enable_paging
kernel_enable_paging:
  push %ebp
  mov %esp, %ebp
  mov $page_directory, %eax
  mov %eax, %cr3
  mov %cr0, %eax
  or $0x80000000, %eax
  mov %eax, %cr0
  mov %ebp, %esp
  pop %ebp
  ret
