#include "utils.h"

int pop(struct Node **stack) {
  struct Node *top = *stack;
  *stack = top->next;
  int value = top->value;
  free(top);
  return value;
}

void push(struct Node **stack, struct Node *node) {
  if (*stack == NULL) {
    *stack = node;
    return;
  }
  node->next = *stack;
  *stack = node;
}

