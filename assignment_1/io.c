
#include "utils.h"
#include <errno.h>
#include <unistd.h>

#include "io.h"

/* Reads next char from stdin. If no more characters, it returns EOF */
int read_char() {
  char c;
  ssize_t size = read(0, &c, 1);
  if (size == -1)
    return EOF;
  return c;
}

/* Writes c to stdout.  If no errors occur, it returns 0, otherwise EOF */
int write_char(char c) {
  ssize_t result = write(1, &c, 1);
  if (result == -1)
    return EOF;
  return 0;
}

/* Writes a null-terminated string to stdout.  If no errors occur, it returns 0,
 * otherwise EOF */
int write_string(char *s) {
  if (s == NULL)
    return EOF;
  while (*s != '\0') {
    ssize_t result = write(1, s, 1);
    if (result == -1)
      return EOF;
    s = s + 1;
  }
  return 0;
}

/* Writes n to stdout (without any formatting).
 * If no errors occur, it returns 0, otherwise EOF
 */
int write_int(int n) {
  struct Node *stack = NULL;
  do {
    struct Node *node = malloc(sizeof(struct Node));
    node->value = n % 10;
    node->next = NULL;
    node->prev = NULL;
    push(&stack, node);
    n = n / 10;
  } while (n != 0);
  while (stack != NULL) {
    int *value = pop(&stack);
    if (value != NULL) {
      char c = *value + '0';
      write_char(c);
    }
  }
  return 0;
}
