#ifndef KERNEL_PAGING_H
#define KERNEL_PAGING_H

#include <stdint.h>

namespace kernel {

void enablePaging();

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

extern "C" {

extern uint32_t page_directory[1024];

}

#endif
