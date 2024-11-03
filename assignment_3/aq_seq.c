/**
 * @file   aq.c
 * @Author 02335 team
 * @date   October, 2024
 * @brief  Alarm queue skeleton implementation
 */

#include "aq.h"
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define CAPACITY 1000

typedef struct Queue {
  MsgKind *msgs[CAPACITY];
  int msgTypes[CAPACITY];
  int curr;
  int size;
} Queue;

AlarmQueue aq_create() {
  // Allocate queue struct
  Queue *q = malloc(sizeof(Queue));
  q->size = 0;
  q->curr = 0;
  return (AlarmQueue)q;
}

int aq_send(AlarmQueue aq, void *msg, MsgKind k) {
  // Cast aq to type QueueNode
  Queue *q = (Queue *)aq;
  // Check for more than more alarm queue
  int alarmExists = FALSE;
  // Check for multiple alarms
  if (k == AQ_ALARM) {
    // Return error if there already exists an alarm
    for (int i = 0; i < q->size; i++) {
      if (q->msgTypes[(q->curr + i) % CAPACITY] == AQ_ALARM) {
        alarmExists = TRUE;
      }
    }
  }
  // Place differently depending on the queue type
  if (k == AQ_ALARM) {
    if (alarmExists == TRUE) {
      return AQ_NO_ROOM;
    }
    // Loops around to the end of the array if out of bounds
    q->curr--;
    if (q->curr <= 0) {
      q->curr = CAPACITY - 1;
    }
    // Append message and message type to start and increment size by one
    q->msgs[q->curr] = msg;
    q->msgTypes[q->curr] = k;
  } else {
    // Append message and message type to the end and increment size by one
    q->msgs[(q->curr + q->size) % CAPACITY] = msg;
    q->msgTypes[(q->curr + q->size) % CAPACITY] = k;
  }
  q->size++;
  printf("curr: %i, size: %i\n", q->curr, q->size);
  return 0;
}

int aq_recv(AlarmQueue aq, void **msg) {
  // Cast aq to type QueueNode
  Queue *q = (Queue *)aq;
  // Check if queue is empty
  if (q->size == 0) {
    return AQ_NO_MSG;
  }
  *msg = q->msgs[q->curr];
  MsgKind msgType = q->msgTypes[q->curr];
  // Loops around to the end of the array if 0
  q->curr++;
  if (q->curr >= CAPACITY) {
    q->curr = 0;
  }
  q->size--;
  return msgType;
}

int aq_size(AlarmQueue aq) { return ((Queue *)aq)->size; }

int aq_alarms(AlarmQueue aq) {
  // Cast aq to type QueueNode
  Queue *q = (Queue *)aq;
  // Number of alarm messages
  int alarms = 0;
  for (int i = 0; i < q->size; i++) {
    if (q->msgTypes[(q->curr + i) % CAPACITY] == AQ_ALARM) {
      alarms++;
    }
  }
  return alarms;
}
