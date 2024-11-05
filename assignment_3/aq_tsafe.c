
/**
 * @file   aq.c
 * @Author 02335 team
 * @date   October, 2024
 * @brief  Alarm queue skeleton implementation
 */

#include "aq.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define CAPACITY 1000

static pthread_mutex_t mutex;
static pthread_cond_t cond_rec, cond_send;

typedef struct NormalMsg {
  struct NormalMsg *next;
  MsgKind *normalMsg;
} NormalMsg;

typedef struct QueueHead {
  NormalMsg *normalMsgs;
  MsgKind *alarmMsg;
  int size;
} QueueHead;

AlarmQueue aq_create() {
  // Allocate QueueHead struct
  QueueHead *q = malloc(sizeof(QueueHead));
  q->normalMsgs = NULL;
  q->alarmMsg = NULL;
  q->size = 0;
  return (AlarmQueue)q;
}

int aq_send(AlarmQueue aq, void *msg, MsgKind k) {
  pthread_mutex_lock(&mutex);
  // Cast aq to type QueueNode
  QueueHead *q = (QueueHead *)aq;
  // Check for multiple alarms
  if (k == AQ_ALARM) {
    // Return error if there already exists an alarm
    while (aq_alarms(aq) == 1) {
      pthread_cond_wait(&cond_send, &mutex);
    }
    q->alarmMsg = msg;
    q->size++;
    pthread_cond_signal(&cond_rec);
    pthread_mutex_unlock(&mutex);
    return 0;
  }
  // Create new message node
  NormalMsg *nmNew = malloc(sizeof(NormalMsg));
  nmNew->normalMsg = msg;
  nmNew->next = NULL;
  q->size++;
  NormalMsg *nm = q->normalMsgs;
  if (nm == NULL) {
    q->normalMsgs = nmNew;
  } else {
    while (nm->next != NULL) {
      nm = nm->next;
    }
    nm->next = nmNew;
  }
  pthread_cond_signal(&cond_rec);
  pthread_mutex_unlock(&mutex);
  return 0;
}

int aq_recv(AlarmQueue aq, void **msg) {
  pthread_mutex_lock(&mutex);
  while (aq_size(aq) == 0) {
    pthread_cond_wait(&cond_rec, &mutex);
  }
  // Cast aq to type QueueNode
  QueueHead *q = (QueueHead *)aq;
  // Check if queue is empty
  if (q->alarmMsg == NULL) {
    if (q->normalMsgs == NULL) {
      pthread_mutex_unlock(&mutex);
      return AQ_NO_MSG;
    }
    NormalMsg *nm = q->normalMsgs;
    q->normalMsgs = nm->next;
    q->size--;
    *msg = nm->normalMsg;
    free(nm);
    pthread_cond_signal(&cond_send);
    pthread_mutex_unlock(&mutex);
    return AQ_NORMAL;
  }
  *msg = q->alarmMsg;
  q->alarmMsg = NULL;
  q->size--;
  pthread_cond_signal(&cond_send);
  pthread_mutex_unlock(&mutex);
  return AQ_ALARM;
}

int aq_size(AlarmQueue aq) { return ((QueueHead *)aq)->size; }

int aq_alarms(AlarmQueue aq) {
  // Cast aq to type QueueNode
  QueueHead *q = (QueueHead *)aq;
  if (q->alarmMsg == NULL) {
    return 0;
  }
  return 1;
}
