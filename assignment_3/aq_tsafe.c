/**
 * @file   aq.c
 * @Author 02335 team
 * @date   October, 2024
 * @brief  Alarm queue skeleton implementation
 */

#include "aq.h"
// #include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode {
  struct QueueNode *next;
  MsgKind *msg;
  int msgType;
} QueueNode;

// typedef struct {
//   int value;
// } Msg;

#define FALSE 0
#define TRUE 1

static pthread_mutex_t mutex;
static pthread_cond_t cond_rec, cond_send;
// static pthread_cond_t cond_wait;

AlarmQueue aq_create() {
  // TODO: remove header queue?

  // Create empty header queue nodde
  QueueNode *start_aq = malloc(sizeof(QueueNode));
  start_aq->msg = NULL;
  start_aq->next = NULL;
  start_aq->msgType = -1;
  return (AlarmQueue)start_aq;
}

int aq_send(AlarmQueue aq, void *msg, MsgKind k) {
  // Lock mutex until finished sending queue
  pthread_mutex_lock(&mutex);
  // if?
  // pthread_cond_wait(&cond_rec, &mutex);
  // Cast aq to type QueueNode
  QueueNode *q = (QueueNode *)aq;
  // Check for more than more alarm queue
  int alarmExists = FALSE;
  // Get the last queue node
  while (q->next != NULL) {
    // Check if an alarm exists
    if (q->next->msgType == AQ_ALARM) {
      alarmExists = TRUE;
    }
    // Get next queue node
    q = q->next;
  }
  // Create new queue node
  QueueNode *new_aq = malloc(sizeof(QueueNode));
  new_aq->msg = msg;
  new_aq->msgType = k;
  // Place differently depending on the queue type
  if (k == AQ_ALARM) {
    printf("alarm queue\n");
    if (alarmExists) {
      return AQ_NO_ROOM;
    }
    q = (QueueNode *)aq;
    if (q->next == NULL) {
      q->next = new_aq;
    } else {
      new_aq->next = q->next;
      q->next = new_aq;
    }
  } else {
    printf("normal queue\n");
    q->next = new_aq;
  }
  printf("# of msgs: %i\n", aq_alarms(aq));
  pthread_cond_signal(&cond_rec);
  pthread_mutex_unlock(&mutex);
  return 0;
}

int aq_recv(AlarmQueue aq, void **msg) {
  // Lock mutex until finished recieving queue
  pthread_mutex_lock(&mutex);
  printf("yyy %i \n", aq_alarms(aq));
  while (aq_alarms(aq) == 0) {
    pthread_cond_wait(&cond_rec, &mutex);
  }
  printf("zzz\n");
  // Cast aq to type QueueNode
  QueueNode *q = (QueueNode *)aq;
  // Check if queue is empty
  if (q->next == NULL) {
    return AQ_NO_MSG;
  }
  QueueNode *aq_rec = q->next;
  q->next = aq_rec->next;
  *msg = aq_rec->msg;
  int msgType = aq_rec->msgType;
  free(aq_rec);

  pthread_cond_signal(&cond_send);
  pthread_mutex_unlock(&mutex);

  return msgType;
}

int aq_size(AlarmQueue aq) {
  // Cast aq to type QueueNode
  QueueNode *q = (QueueNode *)aq;
  // Number of messages
  int size = 0;
  while (q->next != NULL) {
    size++;
    q = q->next;
    // printf("message: %i\n", ((Msg*)q->msg)->value);
  }
  return size;
}

int aq_alarms(AlarmQueue aq) {
  // Cast aq to type QueueNode
  QueueNode *q = (QueueNode *)aq;
  // Number of alarm messages
  int size = 0;
  // Get the last queue node
  while (q->next != NULL) {
    // Check if an alarm exists
    if (q->next->msgType == AQ_ALARM) {
      size++;
    }
    // Get next queue node
    q = q->next;
  }
  return size;
}
