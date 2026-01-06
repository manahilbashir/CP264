/*
--------------------------------------------------
Project: a6q1
File:    queue.c
Author:  Manahil Bashir
Version: 2025-10-22
--------------------------------------------------
*/

#include <stdio.h>
#include "queue.h"

void enqueue(QUEUE *qp, NODE *np) {
    if (np != NULL) {
        np->next = NULL;

        if (qp->front == NULL) {
            qp->front = np;
            qp->rear = np;
        } else {
            qp->rear->next = np;
            qp->rear = np;
        }

        qp->length++;
    }
}  

NODE *dequeue(QUEUE *qp) {
    NODE *np = NULL;

    if (qp->front != NULL) {
        np = qp->front;
        qp->front = qp->front->next;

        if (qp->front == NULL) {
            qp->rear = NULL;
        }

        np->next = NULL;
        qp->length--;
    }

    return np;
}

void clean_queue(QUEUE *qp) {
  clean(&(qp->front));
  qp->front = NULL;
  qp->rear = NULL;
  qp->length=0;
}
