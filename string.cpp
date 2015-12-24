#include "string.h"

extern "C" {

void *memset(void *dest, int ch, size_t count)
{
  unsigned char *p = (unsigned char *) dest;
  for (; count > 0; --count) {
    *p = ch;
    p++;
  }
  return dest;
}

void *memset16(void *dest, uint16_t val, size_t count)
{
  uint16_t *p = (uint16_t *)dest;
  for (; count > 0; --count) {
    *p = val;
    p++;
  }
  return dest;
}

void* memcpy(void *dest, const void *src, size_t count)
{
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (unsigned char *)src;
  for (; count > 0; --count) {
    *d = *s;
    ++d;
    ++s;
  }
  return dest;
}

} // extern C
