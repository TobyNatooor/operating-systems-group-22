#include <stdlib.h>

struct Node {
  struct Node *next;
  int value;
};

int pop(struct Node **stack);
void push(struct Node **stack, struct Node *node);
