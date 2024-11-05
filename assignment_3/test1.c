
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "aq.h"

#include "aux.h"

static AlarmQueue q;

void *producer_alarms(void *arg) {
  put_alarm(q, 1);
  put_alarm(q, 2);

  return 0;
}

void *producer_normal(void *arg) {
  msleep(400);
  put_normal(q, 3);

  return 0;
}

void *consumer(void *arg) {
  msleep(800);
  get(q);

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
  pthread_t t3;

  void *res1;
  void *res2;
  void *res3;

  printf("----------------\n");

  /* Fork threads */
  pthread_create(&t1, NULL, producer_alarms, NULL);
  pthread_create(&t2, NULL, producer_normal, NULL);
  pthread_create(&t3, NULL, consumer, NULL);
  /* Join with all threads */
  pthread_join(t1, &res1);
  pthread_join(t2, &res2);
  pthread_join(t3, &res3);

  printf("----------------\n");
  printf("Threads terminated with %ld, %ld, %ld\n", (uintptr_t)res1,
         (uintptr_t)res2, (uintptr_t)res3);

  print_sizes(q);

  return 0;
}
