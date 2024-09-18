#include "utils.h"

int* pop(struct Node **stack) {
  if (*stack == NULL) {
    return NULL;
  }
  struct Node *top = *stack;
  (*stack)->prev = NULL;
  *stack = top->next;
  int *value = malloc(sizeof(int));
  *value = top->value;
  free(top);
  return value;
}

void push(struct Node **stack, struct Node *node) {
  if (*stack == NULL) {
    *stack = node;
    return;
  }
  node->next = *stack;
  (*stack)->prev = node;
  *stack = node;
}

int* dequeue(struct Node **stack) {
  struct Node *first = *stack;
  *stack = first->next;
  while (first->next != NULL) {
    first = first->next;
  }
  int *value = malloc(sizeof(int));
  *value = first->value;
  free(first);
  return value;
}
