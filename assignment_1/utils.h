#include <stdlib.h>

struct Node {
  struct Node *next;
  struct Node *prev;
  int value;
};

int* pop(struct Node **stack);
void push(struct Node **stack, struct Node *node);
int* dequeue(struct Node **stack);
