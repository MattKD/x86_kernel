
.align 4

# void kernel_outport(uint16_t port, uint8_t data)
.global kernel_outport
kernel_outport:
  movw 4(%esp), %dx # move port to dx
  movb 8(%esp), %al # move data byte to al
  outb %al, %dx 
  ret

# uint8_t kernel_inport(uint16_t port)
.global kernel_inport
kernel_inport:
  movw 4(%esp), %dx # move port to dx
  xor %eax, %eax
  inb %dx, %al # return byte in %eax
  ret
