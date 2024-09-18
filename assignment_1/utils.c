#include "utils.h"

int* pop(struct Node **stack) {
  if (*stack == NULL) {
    return NULL;
  }
  struct Node *last = *stack;
  while(last->next != NULL) {
    last = last->next;
  }
  if (last->prev != NULL) {
    last->prev->next = NULL;
  }
  int *value = malloc(sizeof(int));
  *value = last->value;
  if ((*stack)->next == NULL) {
    *stack = NULL;
  }
  free(last);
  return value;
}

void push(struct Node **stack, struct Node *node) {
  if (*stack == NULL) {
    *stack = node;
    return;
  }
  struct Node *last = *stack;
  while(last->next != NULL) {
    last = last->next;
  }
  last->next = node;
  node->prev = last;
}

int* dequeue(struct Node **stack) {
  if (*stack == NULL) {
    return NULL;
  }
  struct Node *first = *stack;
  *stack = first->next;
  int *value = malloc(sizeof(int));
  *value = first->value;
  free(first);
  return value;
}
