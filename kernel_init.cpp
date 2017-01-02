#include "multiboot.h"
#include "terminal.h"
#include "gdt.h"
#include "idt.h"
#include "isr_exceptions.h"
#include "isr_irqs.h"
#include "kb.h"
#include "timer.h"
#include "stdio.h"
#include "paging.h"
#include "kernel.h"
#include <stdint.h>

using namespace kernel;

static const int max_num_frames = 1 << 20; // 1mb of 4kb frames = 4gb
static void* frames[max_num_frames];
static int num_free_frames = 0;

namespace kernel {

void* allocFrame()
{
  if (num_free_frames > 0) {
    return frames[--num_free_frames];
  }
  return nullptr;
}

void freeFrame(void *frame)
{
  frames[num_free_frames++] = frame;
}

} // end namespace kernel

bool allocFrameInit(uint32_t mb_magic, multiboot_info_t *mb_info);

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

  printf("kernel start = %x\n", &_kernel_start_addr);
  printf("kernel end = %x\n", &_kernel_end_addr);

  if (allocFrameInit(mb_magic, mb_info)) {
    printf("Number of 4KB frames: %d\n", num_free_frames);
    enablePaging();
  } else {
    kernel_panic("Error: Couldn't initialize frame allocator\n");
  }
}

static inline
uintptr_t align4K(uintptr_t addr)
{
  if (addr % 4096 != 0) {
    addr += 4096;
    addr &= ~4095;
  }
  return addr;
}

bool allocFrameInit(uint32_t mb_magic, multiboot_info_t *mb_info)
{
  if (mb_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
    return false;
  }

  multiboot_memory_map_t *mmap = 
    (multiboot_memory_map_t *) mb_info->mmap_addr;
  multiboot_memory_map_t *mmap_end = (multiboot_memory_map_t *)
    (mb_info->mmap_addr + mb_info->mmap_length);

  while(mmap < mmap_end) {
    printf("address: %x, ", mmap->addr);
    printf("length: %x, ", mmap->len);
    printf("type: %s\n", mmap->type == 1 ? "Available" : "Reserved");

    if (mmap->type == 1) {
      uintptr_t frame = (uintptr_t)mmap->addr;
      uintptr_t mem_end = (uintptr_t)mmap->addr + mmap->len;
      // align frame on 4kb boundary
      frame = align4K(frame);

      while (frame+4095 < mem_end && num_free_frames < max_num_frames) {
        // skip any memory within kernel or 1st MB
        if (frame < (uintptr_t)&_kernel_end_addr) {
          printf("within kernel 2\n");
          frame = (uintptr_t)&_kernel_end_addr;
          frame = align4K(frame);
          continue;
        }

        frames[num_free_frames++] = (void*)frame;
        frame += 4096;
      }
    }

    mmap = (multiboot_memory_map_t *) 
      ((uint32_t)mmap + mmap->size + sizeof(mmap->size));
  }
  
  return true;
}
