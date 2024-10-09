#include "io.h"
#include "list.h"

int main() {
  char c;
  int count = 0;
  struct Node *collection = NULL;
  struct Node *node;

  do {
    c = read_char();
    switch (c) {
    case 'a':
      node = simple_malloc(sizeof(struct Node));
      node->value = count;
      node->next = NULL;
      node->prev = NULL;
      push(&collection, node);
      break;
    case 'c':
      pop(&collection);
      break;
    }
    count++;
  } while (c == 'a' || c == 'b' || c == 'c');

  while (collection != NULL) {
    int *value = dequeue(&collection);
    if (value != NULL) {
      write_int(*value);
      simple_free(value);
    }
    if (collection != NULL) {
      write_char(',');
    }
  }
  write_string(";\n");

  return 0;
}
