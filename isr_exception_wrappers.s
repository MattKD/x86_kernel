# Interrupt Service Routines (IDT handlers) for interrupt exceptions
# These are wrappers that call actual exceptin handlers in C

.align 4

.global kernel_isr0
kernel_isr0:
  pusha
  cld
  call kernel_exception0 
  popa
  iret

.global kernel_isr1
kernel_isr1:
  pusha
  cld
  call kernel_exception1
  popa
  iret

.global kernel_isr2
kernel_isr2:
  pusha
  cld
  call kernel_exception2 
  popa
  iret

.global kernel_isr3
kernel_isr3:
  pusha
  cld
  call kernel_exception3 
  popa
  iret

.global kernel_isr4
kernel_isr4:
  pusha
  cld
  call kernel_exception4 
  popa
  iret

.global kernel_isr5
kernel_isr5:
  pusha
  cld
  call kernel_exception5 
  popa
  iret

.global kernel_isr6
kernel_isr6:
  pusha
  cld
  call kernel_exception6 
  popa
  iret

.global kernel_isr7
kernel_isr7:
  pusha
  cld
  call kernel_exception7 
  popa
  iret

.global kernel_isr8
kernel_isr8:
  pusha
  cld
  call kernel_exception8 
  popa
  addl $4, %eax
  iret

.global kernel_isr9
kernel_isr9:
  pusha
  cld
  call kernel_exception9 
  popa
  iret

.global kernel_isr10
kernel_isr10:
  pusha
  cld
  call kernel_exception10 
  popa
  addl $4, %eax
  iret

.global kernel_isr11
kernel_isr11:
  pusha
  cld
  call kernel_exception11 
  popa
  addl $4, %eax
  iret

.global kernel_isr12
kernel_isr12:
  pusha
  cld
  call kernel_exception12 
  popa
  addl $4, %eax
  iret

.global kernel_isr13
kernel_isr13:
  pusha
  cld
  call kernel_exception13 
  popa
  addl $4, %eax
  iret

.global kernel_isr14
kernel_isr14:
  #pusha
  #cld
  movl %cr2, %eax
  pushl %eax
  call kernel_exception14 
  #popa
  #addl $4, %eax
  addl $8, %esp
  iret

.global kernel_isr15
kernel_isr15:
  pusha
  cld
  call kernel_exception15 
  popa
  iret

.global kernel_isr16
kernel_isr16:
  pusha
  cld
  call kernel_exception16 
  popa
  iret

.global kernel_isr17
kernel_isr17:
  pusha
  cld
  call kernel_exception17 
  popa
  iret

.global kernel_isr18
kernel_isr18:
  pusha
  cld
  call kernel_exception18 
  popa
  iret

.global kernel_isr19
kernel_isr19:
  pusha
  cld
  push $19
  call kernel_exception_reserved
  addl $4, %esp
  popa
  iret

.global kernel_isr20
kernel_isr20:
  pusha
  cld
  push $20
  call kernel_exception_reserved
  addl $4, %esp
  popa
  iret

.global kernel_isr21
kernel_isr21:
  pusha
  cld
  push $21
  call kernel_exception_reserved
  addl $4, %esp
  popa
  iret

.global kernel_isr22
kernel_isr22:
  pusha
  cld
  push $22
  call kernel_exception_reserved
  addl $4, %esp
  popa
  iret

.global kernel_isr23
kernel_isr23:
  pusha
  cld
  push $23
  call kernel_exception_reserved
  addl $4, %esp
  popa
  iret

.global kernel_isr24
kernel_isr24:
  pusha
  cld
  push $24
  call kernel_exception_reserved
  addl $4, %esp
  popa
  iret

.global kernel_isr25
kernel_isr25:
  pusha
  cld
  push $25
  call kernel_exception_reserved
  addl $4, %esp
  popa
  iret

.global kernel_isr26
kernel_isr26:
  pusha
  cld
  push $26
  call kernel_exception_reserved
  addl $4, %esp
  popa
  iret

.global kernel_isr27
kernel_isr27:
  pusha
  cld
  push $27
  call kernel_exception_reserved
  addl $4, %esp
  popa
  iret

.global kernel_isr28
kernel_isr28:
  pusha
  cld
  push $28
  call kernel_exception_reserved
  addl $4, %esp
  popa
  iret

.global kernel_isr29
kernel_isr29:
  pusha
  cld
  push $29
  call kernel_exception_reserved
  addl $4, %esp
  popa
  iret

.global kernel_isr30
kernel_isr30:
  pusha
  cld
  push $30
  call kernel_exception_reserved
  addl $4, %esp
  popa
  iret

.global kernel_isr31
kernel_isr31:
  pusha
  cld
  push $31
  call kernel_exception_reserved
  addl $4, %esp
  popa
  iret
