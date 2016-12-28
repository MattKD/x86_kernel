#include "stdio.h"
#include "paging.h"

extern "C" {

void kernel_enable_paging(); // defined in enable_paging.s
alignas(4096) uint32_t page_directory[1024];

}

namespace {

int num_page_tables;
alignas(4096) uint32_t page_tables[1024][1024];

// Mapped to first 8MB of memory where kernel is located
//alignas(4096) uint32_t page_table1[1024];
//alignas(4096) uint32_t page_table2[1024];
}

namespace kernel {

uint32_t getPageTable()
{
  if (num_page_tables == 1024) {
    return 0;
  }
  return (uint32_t)::page_tables[num_page_tables++];
}

void enablePaging()
{
  // Identity map first 8Mb of memory, so kernel address doens't change
  uint32_t flags = PageWriteFlag | PagePresentFlag;
  for (int i = 0; i < 1024; ++i) {
    page_tables[0][i] = (i * 4096) | flags;
    page_tables[1][i] = (1024*4096 + i * 4096) | flags;
    page_tables[2][i] = (2*1024*4096 + i * 4096) | flags;
  }
  page_directory[0] = (uint32_t)page_tables[0] | flags;
  page_directory[1] = (uint32_t)page_tables[1] | flags;
  page_directory[2] = (uint32_t)page_tables[2] | flags;
  num_page_tables = 3;

  kernel_enable_paging();  
}

}

