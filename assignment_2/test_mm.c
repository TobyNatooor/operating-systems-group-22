
#include <stdint.h>
#include <stdio.h>

#include "mm.h"

/**
 * Test program that makes some simple allocations and enables
 * you to inspect the result.
 *
 * Elaborate on your own.
 */

int main(int argc, char **argv) {

  /* Ensure that macros are working */
  int ret = simple_macro_test();
  if (ret > 0) {
    printf("Macro test returned %d\n", ret);
    return 1;
  }

  void *a = simple_malloc(32);
  printf("1: %p\n", a);
  void *b = simple_malloc(20);
  printf("2: %p\n", b);
  void *c = simple_malloc(10);
  printf("3: %p\n", c);
  simple_free(a);

  // void * a = simple_malloc(0x200);
  // printf("1: %p\n", a);
  //
  // void * b = simple_malloc(0x100);
  // printf("2: %p\n", b);
  //
  // simple_free(a);
  // printf("3: %p\n", a);
  //
  // simple_malloc(0x100);
  //
  // simple_free(b);
  // printf("4\n");

  simple_block_dump();

  return 0;
}
