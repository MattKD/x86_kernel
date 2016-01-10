#include "multiboot.h"
#include "terminal.h"
#include "gdt.h"
#include "idt.h"
#include "isr_exceptions.h"
#include "isr_irqs.h"
#include "kb.h"
#include "timer.h"
#include "stdio.h"

using namespace kernel;

extern "C"
void kernelInit(uint32_t mb_magic, multiboot_info_t *mb_info)
{
  Terminal::initMainTerm();
  GDT_init();
  IDT_init();
  PIC_init();
  IDT_install_Exception_ISRs();
  IDT_install_IRQ_ISRs();
  keyboardInit();
  timerInit();

  Terminal &term = Terminal::activeTerm();
  term.clear();

  if (mb_magic == MULTIBOOT_BOOTLOADER_MAGIC) {
    multiboot_memory_map_t *mmap = 
      (multiboot_memory_map_t *) mb_info->mmap_addr;
    multiboot_memory_map_t *mmap_end = (multiboot_memory_map_t *)
      (mb_info->mmap_addr + mb_info->mmap_length);

    while(mmap < mmap_end) {
      printf("address: %x, ", mmap->addr);
      printf("length: %x, ", mmap->len);
      printf("type: %s\n", mmap->type == 1 ? "Available" : "Reserved");
      mmap = (multiboot_memory_map_t *) 
        ((uint32_t)mmap + mmap->size + sizeof(mmap->size));
    }
  }

}
