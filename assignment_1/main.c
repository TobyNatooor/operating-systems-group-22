#include "utils.h"

/* You are not allowed to use <stdio.h> */
#include "io.h"

/**
 * @name  main
 * @brief This function is the entry point to your program
 * @return 0 for success, anything else for failure
 *
 *
 * Then it has a place for you to implementation the command
 * interpreter as  specified in the handout.
 */
int main() {
  /*-----------------------------------------------------------------
   *TODO:  You need to implement the command line driver here as
   *       specified in the assignment handout.
   *
   * The following pseudo code describes what you need to do
   *
   *  Declare the counter and the collection structure variables
   *
   *
   *  In a loop
   *    1) Read a command from standard in using read_char function
   *    2) If the command is not 'a', 'b', 'c': then break the loop
   *    3) Process the command as specified in the handout
   *  End loop
   *
   *  Print your collection of elements as specified in the handout
   *    as a comma delimited series of integers
   *-----------------------------------------------------------------*/

  char c;
  int count = 0;
  struct Node *collection = NULL;
  struct Node *node;

  do {
    c = read_char();
    switch (c) {
    case 'a':
      node = malloc(sizeof(struct Node));
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
      free(value);
    }
    if (collection != NULL) {
      write_char(',');
    }
  }
  write_string(";\n");

  return 0;
}
