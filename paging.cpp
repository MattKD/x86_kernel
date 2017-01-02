#include "stdio.h"
#include "paging.h"

extern "C" {

void kernel_enable_paging(); // defined in enable_paging.s
alignas(4096) uint32_t page_directory[1024];

}

namespace {

alignas(4096) uint32_t page_tables[1024][1024];

}

namespace kernel {

void enablePaging()
{
  // Identity map first 12Mb of memory, so kernel address doens't change
  uint32_t flags = PageWriteFlag | PagePresentFlag;
  for (int i = 0; i < 1024; ++i) {
    page_tables[0][i] = (i * 4096) | flags;
    page_tables[1][i] = (1024*4096 + i * 4096) | flags;
    page_tables[2][i] = (2*1024*4096 + i * 4096) | flags;
  }

  for (int i = 0; i < 1024; ++i) {
    page_directory[i] = (uint32_t)page_tables[i] | flags;
  }

  kernel_enable_paging();  
}

}

