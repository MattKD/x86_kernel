#include "kernel.h"
#include "idt.h"
#include "isr_exceptions.h"
#include "paging.h"

extern "C" {

void kernel_isr0();
void kernel_isr1();
void kernel_isr2();
void kernel_isr3();
void kernel_isr4();
void kernel_isr5();
void kernel_isr6();
void kernel_isr7();
void kernel_isr8();
void kernel_isr9();
void kernel_isr10();
void kernel_isr11();
void kernel_isr12();
void kernel_isr13();
void kernel_isr14();
void kernel_isr15();
void kernel_isr16();
void kernel_isr17();
void kernel_isr18();
void kernel_isr19();
void kernel_isr20();
void kernel_isr21();
void kernel_isr22();
void kernel_isr23();
void kernel_isr24();
void kernel_isr25();
void kernel_isr26();
void kernel_isr27();
void kernel_isr28();
void kernel_isr29();
void kernel_isr30();
void kernel_isr31();
} // extern C

namespace kernel {

void IDT_install_Exception_ISRs()
{
  IDT_add_ISR(0, ::kernel_isr0);
  IDT_add_ISR(1, ::kernel_isr1);
  IDT_add_ISR(2, ::kernel_isr2);
  IDT_add_ISR(3, ::kernel_isr3);
  IDT_add_ISR(4, ::kernel_isr4);
  IDT_add_ISR(5, ::kernel_isr5);
  IDT_add_ISR(6, ::kernel_isr6);
  IDT_add_ISR(7, ::kernel_isr7);
  IDT_add_ISR(8, ::kernel_isr8);
  IDT_add_ISR(9, ::kernel_isr9);
  IDT_add_ISR(10, ::kernel_isr10);
  IDT_add_ISR(11, ::kernel_isr11);
  IDT_add_ISR(12, ::kernel_isr12);
  IDT_add_ISR(13, ::kernel_isr13);
  IDT_add_ISR(14, ::kernel_isr14);
  IDT_add_ISR(15, ::kernel_isr15);
  IDT_add_ISR(16, ::kernel_isr16);
  IDT_add_ISR(17, ::kernel_isr17);
  IDT_add_ISR(18, ::kernel_isr18);
  IDT_add_ISR(19, ::kernel_isr19);
  IDT_add_ISR(20, ::kernel_isr20);
  IDT_add_ISR(21, ::kernel_isr21);
  IDT_add_ISR(22, ::kernel_isr22);
  IDT_add_ISR(23, ::kernel_isr23);
  IDT_add_ISR(24, ::kernel_isr24);
  IDT_add_ISR(25, ::kernel_isr25);
  IDT_add_ISR(26, ::kernel_isr26);
  IDT_add_ISR(27, ::kernel_isr27);
  IDT_add_ISR(28, ::kernel_isr28);
  IDT_add_ISR(29, ::kernel_isr29);
  IDT_add_ISR(30, ::kernel_isr30);
  IDT_add_ISR(31, ::kernel_isr31);
}

} // namespace kernel

using namespace kernel;

extern "C" {

void kernel_exception0()
{
  kernel_panic("Division By Zero Exception\n");
}

void kernel_exception1()
{
  kernel_panic("Debug Exception\n");
}

void kernel_exception2()
{
  kernel_panic("NMI Exception\n");
}

void kernel_exception3()
{
  kernel_panic("Breakpoint Exception\n");
}

void kernel_exception4()
{
  kernel_panic("Into Detected Overflow Exception\n");
}

void kernel_exception5()
{
  kernel_panic("Out of Bounds Exception\n");
}

void kernel_exception6()
{
  kernel_panic("Invalid Opcode Exception\n");
}

void kernel_exception7()
{
  kernel_panic("No Coprocessor Exception\n");
}

void kernel_exception8(int err)
{
  kernel_panic("Double Fault Exception, Err: %d\n", err);
}

void kernel_exception9()
{
  kernel_panic("Coprocessor Segment Overrun Exception\n");
}

void kernel_exception10(int err)
{
  kernel_panic("Bad TSS Exception, Err: %d\n", err);
}

void kernel_exception11(int err)
{
  kernel_panic("Segment Not Present Exception, Err: %d\n", err);
}

void kernel_exception12(int err)
{
  kernel_panic("Stack Fault Exception, Err: %d\n", err);
}

void kernel_exception13(int err)
{
  kernel_panic("General Protection Fault Exception, Err: %d\n", err);
}

static void page_fault_panic(unsigned addr, int err)
{
  bool present = (err & 1) == 1;
  bool write = (err & 2) == 2;
  bool user = (err & 4) == 4;

  kernel_panic("Page Fault: address = %x, err = %s, %s, %s\n", addr, 
               present ? "Present" : "Not-Present",
               write ? "Write" : "Read",
               user ? "User": "Supervisor");
}

void kernel_exception14(unsigned addr, int err)
{
  uint32_t dir_idx = addr >> 22; // bits 23-32
  uint32_t tbl_idx = (addr >> 12) & 1023; // bits 13-22
  uint32_t dir_entry = page_directory[dir_idx];

  if ((dir_entry & PagePresentFlag) == 0) {
    uint32_t tbl_addr = getPageTable();
    if (tbl_addr == 0) {
      page_fault_panic(addr, err);
    }
    page_directory[dir_idx] = tbl_addr | PageWriteFlag | PagePresentFlag; 
    dir_entry = page_directory[dir_idx];

    uint32_t *page_table = (uint32_t*)tbl_addr;
    for (int i = 0; i < 1024; ++i) {
      page_table[i] = 0;
    }
  }

  uint32_t *page_table = (uint32_t*)(dir_entry & ~1023);
  uint32_t tbl_entry = page_table[tbl_idx];

  if ((tbl_entry & PagePresentFlag) == 0) {
    uint32_t page_addr = (uint32_t)allocFrame();
    if (page_addr == 0) {
      page_fault_panic(addr, err);
    }
    page_table[tbl_idx] = page_addr | PageWriteFlag | PagePresentFlag; 
    tbl_entry = page_directory[dir_idx];
  }
}

void kernel_exception15()
{
  kernel_panic("Unknown Interrupt Exception\n");
}

void kernel_exception16()
{
  kernel_panic("Coprocessor Fault Exception\n");
}

void kernel_exception17(int err)
{
  kernel_panic("Alignment Check Exception, Err: %d\n", err);
}

void kernel_exception18()
{
  kernel_panic("Machine Check Exception\n");
}

// Exception 19-29,31
void kernel_exception_reserved(int exception_num)
{
  kernel_panic("Reserved Exception %d\n", exception_num);
}

void kernel_exception30(int err)
{
  kernel_panic("Security Exception, Err: %d\n", err);
}


} // extern C
