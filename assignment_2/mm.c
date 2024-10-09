/**
 * @file   mm.c
 * @Author 02335 team
 * @date   September, 2024
 * @brief  Memory management skeleton.
 *
 */

#include <stdint.h>
#include <stdio.h>

#include "mm.h"

/* Proposed data structure elements */

/* Macros to handle the free flag at bit 0 of the next pointer of header pointed
 * at by p */
// Masks out free flag
#define GET_NEXT(p) (void *)((uintptr_t)(p->next) >> 1 << 1)
// Preserves free flag
#define SET_NEXT(p, n) p->next = (void *)n + GET_FREE(p)
#define GET_FREE(p) (uint8_t)((uintptr_t)(p->next) & 0x1)
// Change free bit to f
#define SET_FREE(p, f)                                                         \
  p->next = (void *)(((uintptr_t)GET_NEXT(p) >> 1 << 1) + (f == 0 ? 0 : 1))
#define SIZE(p)                                                                \
  (size_t)((uintptr_t)GET_NEXT(p) - ((uintptr_t)(p) >> 1 << 1) - 8)

#define MIN_SIZE (8)

static BlockHeader *first = NULL;
static BlockHeader *current = NULL;

/**
 * @name    simple_init
 * @brief   Initialize the block structure within the available memory
 *
 */
void simple_init() {
  uintptr_t aligned_memory_start = (memory_start + 7) & ~7;
  uintptr_t aligned_memory_end = memory_end & ~7;
  BlockHeader *last;

  /* Already initalized ? */
  if (first == NULL) {
    /* Check that we have room for at least one free block and an end header
     */
    if (aligned_memory_start + 2 * sizeof(BlockHeader) + MIN_SIZE <=
        aligned_memory_end) {
      /* TODO: Place first and last blocks and set links and free flags
      properly
       */
      first = (BlockHeader *)aligned_memory_start;
      last = (BlockHeader *)aligned_memory_end - sizeof(BlockHeader);
      SET_NEXT(first, last);
      SET_FREE(first, 1);
      SET_NEXT(last, first);
      SET_FREE(last, 0);
    }
    current = first;
  }
}

/**
 * @name    simple_malloc
 * @brief   Allocate at least size contiguous bytes of memory and return a
 * pointer to the first byte.
 *
 * This function should behave similar to a normal malloc implementation.
 *
 * @param size_t size Number of bytes to allocate.
 * @retval Pointer to the start of the allocated memory or NULL if not possible.
 *
 */
void *simple_malloc(size_t size) {

  if (first == NULL) {
    simple_init();
    if (first == NULL)
      return NULL;
  }

  size_t aligned_size = (size + 7) & ~7;

  /* Search for a free block */
  BlockHeader *search_start = current;
  do {

    if (GET_FREE(current)) {

      /* Possibly coalesce consecutive free blocks here */
      BlockHeader *tmp = current;
      while (GET_FREE(tmp)) {
        tmp = GET_NEXT(tmp);
      }
      if (tmp != current) {
        SET_NEXT(current, tmp);
      }

      /* Check if free block is large enough */
      if (SIZE(current) >= aligned_size) {
        /* Will the remainder be large enough for a new block? */
        if (SIZE(current) - aligned_size < sizeof(BlockHeader) + MIN_SIZE) {
          /* TODO: Use block as is, marking it non-free*/
          SET_FREE(current, 0);
        } else {
          /* TODO: Carve aligned_size from block and allocate new free block for
           * the rest */
          BlockHeader *next = GET_NEXT(current);
          BlockHeader *new = (void *)((uintptr_t)current +
                                      sizeof(struct header *) + aligned_size);
          SET_NEXT(current, new);
          SET_NEXT(new, next);
          SET_FREE(current, 0);
          SET_FREE(new, 1);
        }
        // return (void *) NULL; /* TODO: Return address of current's user_block
        // and advance current */
        BlockHeader *prev = current;
        current = GET_NEXT(current);
        return prev->user_block;
      }
    }

    current = GET_NEXT(current);
  } while (current != search_start);

  /* None found */
  return NULL;
}

/**
 * @name    simple_free
 * @brief   Frees previously allocated memory and makes it available for
 * subsequent calls to simple_malloc
 *
 * This function should behave similar to a normal free implementation.
 *
 * @param void *ptr Pointer to the memory to free.
 *
 */
void simple_free(void *ptr) {
  BlockHeader *block = ptr - sizeof(struct header);
  if (GET_FREE(block)) {
    /* Block is not in use -- probably an error */
    return;
  }

  /* TODO: Free block */
  SET_FREE(block, 1);

  /* Possibly coalesce consecutive free blocks here */
  BlockHeader *next = GET_NEXT(block);
  if (GET_FREE(next)) {
    SET_NEXT(block, GET_NEXT(next));
  }
}

#include "mm_aux.c"
