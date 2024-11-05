
#include <assert.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "aq.h"

#include "aux.h"

static AlarmQueue q;

void *producer(void *arg) {
  msleep(500);
  put_alarm(q, 1);
  put_normal(q, 2);
  put_normal(q, 3);
  put_normal(q, 4);
  put_alarm(q, 5);

  return 0;
}

void *consumer(void *arg) {
  assert(get(q) == 1);
  msleep(500);
  assert(get(q) == 5);
  assert(get(q) == 2);
  assert(get(q) == 3);
  assert(get(q) == 4);

  return 0;
}

int main(int argc, char **argv) {
  int ret;

  q = aq_create();

  if (q == NULL) {
    printf("Alarm queue could not be created\n");
    exit(1);
  }

  pthread_t t1;
  pthread_t t2;

  void *res1;
  void *res2;

  printf("----------------\n");

  /* Fork threads */
  pthread_create(&t1, NULL, producer, NULL);
  pthread_create(&t2, NULL, consumer, NULL);
  /* Join with all threads */
  pthread_join(t1, &res1);
  pthread_join(t2, &res2);

  printf("----------------\n");
  printf("Threads terminated with %ld, %ld\n", (uintptr_t)res1,
         (uintptr_t)res2);

  print_sizes(q);

  return 0;
}
