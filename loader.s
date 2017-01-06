# Multiboot header
.set MB_ALIGN, 1 # align loaded modules on page boundaries
.set MB_MEMINFO, 2 # provide memory map
# .set MB_ADDR, 16 # use load addresses in header. Not necessary in ELF exe. */
# .set MB_FLAGS, MB_ALIGN | MB_MEMINFO | MB_ADDR  
.set MB_FLAGS, MB_ALIGN | MB_MEMINFO  
.set MB_MAGIC, 0x1BADB002 # multiboot 'magic number' to find header
.set MB_CHECKSUM, -(MB_MAGIC + MB_FLAGS)  # multiboot checksum 

.section .multiboot
.align 4
.long MB_MAGIC
.long MB_FLAGS
.long MB_CHECKSUM
/*
.long _mb_header_addr # .multiboot addr
.long _mb_load_addr # .text addr
.long _mb_load_end_addr # .data end addr
.long _mb_bss_end_addr # .bss end addr
.long loader # addr of OS start
*/

# reserve initial kernel stack space
.set STACKSIZE, 0x4000  # 16k.
.lcomm stack, STACKSIZE # place stack in .bss

.section .text
.global loader # making entry point visible to linker
loader:
    movl $(stack + STACKSIZE), %esp # set up the stack
    push %ebx # Multiboot info structure pointer
    push %eax # Multiboot magic number
    cli
    call kernelInit
    sti
    addl $8, %esp # pop Multiboot info/magic
    call _init # call global ctors
    call kmain # should never return
    push $0 # pass null to __cxa_finalize to call all global dtors
    call __cxa_finalize
    call _fini
    jmp kernel_halt

# halt machine forever on unrecoverable errors
.global kernel_halt_loop
kernel_halt_loop:
    cli
    hlt 
    jmp kernel_halt

# put cpu to sleep until interrupt received
.global kernel_halt
kernel_halt:
    hlt 
    ret

