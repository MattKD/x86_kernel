# Interrupt Service Routines (IDT handlers) for IRQs
# These are wrappers that call actual IRQ handlers in C

.align 4

.global kernel_isr32
kernel_isr32:
  pusha
  cld
  push $0
  call kernel_irq_handler
  addl $4, %esp
  popa
  iret

.global kernel_isr33
kernel_isr33:
  pusha
  cld
  push $1
  call kernel_irq_handler
  addl $4, %esp
  popa
  iret

.global kernel_isr34
kernel_isr34:
  pusha
  cld
  push $2
  call kernel_irq_handler
  addl $4, %esp
  popa
  iret

.global kernel_isr35
kernel_isr35:
  pusha
  cld
  push $3
  call kernel_irq_handler
  addl $4, %esp
  popa
  iret

.global kernel_isr36
kernel_isr36:
  pusha
  cld
  push $4
  call kernel_irq_handler
  addl $4, %esp
  popa
  iret

.global kernel_isr37
kernel_isr37:
  pusha
  cld
  push $5
  call kernel_irq_handler
  addl $4, %esp
  popa
  iret

.global kernel_isr38
kernel_isr38:
  pusha
  cld
  push $6
  call kernel_irq_handler
  addl $4, %esp
  popa
  iret

.global kernel_isr39
kernel_isr39:
  pusha
  cld
  push $7
  call kernel_irq_handler
  addl $4, %esp
  popa
  iret

.global kernel_isr40
kernel_isr40:
  pusha
  cld
  push $8
  call kernel_irq_handler
  addl $4, %esp
  popa
  iret

.global kernel_isr41
kernel_isr41:
  pusha
  cld
  push $9
  call kernel_irq_handler
  addl $4, %esp
  popa
  iret

.global kernel_isr42
kernel_isr42:
  pusha
  cld
  push $10
  call kernel_irq_handler
  addl $4, %esp
  popa
  iret

.global kernel_isr43
kernel_isr43:
  pusha
  cld
  push $11
  call kernel_irq_handler
  addl $4, %esp
  popa
  iret

.global kernel_isr44
kernel_isr44:
  pusha
  cld
  push $12
  call kernel_irq_handler
  addl $4, %esp
  popa
  iret

.global kernel_isr45
kernel_isr45:
  pusha
  cld
  push $13
  call kernel_irq_handler
  addl $4, %esp
  popa
  iret

.global kernel_isr46
kernel_isr46:
  pusha
  cld
  push $14
  call kernel_irq_handler
  addl $4, %esp
  popa
  iret

.global kernel_isr47
kernel_isr47:
  pusha
  cld
  push $15
  call kernel_irq_handler
  addl $4, %esp
  popa
  iret

