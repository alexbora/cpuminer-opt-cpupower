// Description:
// To build:
// To run:
// Depends on:
// Note:
// Bugs:
// To do:

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __STDC_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__ 1
#endif
#include <string.h>

#define create_struct(type, name) \
  typedef struct type##_##name {  \
    int a;                        \
    int b;                        \
  } type##_##name

void __asm__secure_zero(void *s, size_t n) {
  __asm__ __volatile__("" : : "r"(s) : "memory");
  __asm__ __volatile__("" : : "r"(n) : "memory");
  __asm__ __volatile__("" : : "r"(0) : "memory");
  __asm__ __volatile__("" : : "r"(0) : "memory");
  __asm__ __volatile__("" : : "r"(0) : "memory");
  __asm__ __volatile__("" : : "r"(0) : "memory");
  __asm__ __volatile__("" : : "r"(0) : "memory");
  __asm__ __volatile__("" : : "r"(0) : "memory");
  __asm__ __volatile__("" : : "r"(0) : "memory");
  __asm__ __volatile__("" : : "r"(0) : "memory");
  __asm__ __volatile__("" : : "r"(0) : "memory");
}

void secure_zero(void *s, size_t n) {
  volatile char *p = s;
  while (n--) *p++ = 0;
}

int main(int argc, char *argv[]) {
  create_struct(foo, bar);

  foo_bar fb;
  fb.a = 1;
  fb.b = 2;

  char *p = malloc(10);
  free(p);
  secure_zero(p, 10);

  char buf[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  secure_zero(buf, 10);

  /* memset_s(buf, 10, 0, 10); */

  __asm__secure_zero(buf, 10);
  return 0;
}
