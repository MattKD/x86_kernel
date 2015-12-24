#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>

extern "C" {

void *memset(void *dest, int ch, size_t count);
void *memset16(void *dest, uint16_t val, size_t count);
void *memcpy(void *dest, const void *src, size_t count);

}
#endif
