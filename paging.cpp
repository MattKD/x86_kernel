#include "stdio.h"
#include <stdint.h>

extern "C" {

void kernel_enable_paging(); // defined in enable_paging.s
alignas(4096) uint32_t page_directory[1024];

}

namespace {

// Mapped to first 8MB of memory where kernel is located
alignas(4096) uint32_t page_table1[1024];
alignas(4096) uint32_t page_table2[1024];

enum PageFlags {
  PagePresentFlag = 1,
  PageWriteFlag = 2,
  PageUserFlag = 4,
  PageWriteThroughFlag = 8,
  PageCacheDisableFlag = 16,
  PageAccessedFlag = 32,
  PageSizeFlag = 128,
  PageGlobalFlag = 256
};

}

namespace kernel {

void enablePaging()
{
  // Identity map first 8Mb of memory, so kernel address doens't change
  uint32_t flags = PageWriteFlag | PagePresentFlag;
  for (int i = 0; i < 1024; ++i) {
    page_table1[i] = (i * 4096) | flags;
    page_table2[i] = (1024*4096 + i * 4096) | flags;
  }
  page_directory[0] = (uint32_t)page_table1 | flags;
  page_directory[1] = (uint32_t)page_table2 | flags;

  kernel_enable_paging();  
}

}

