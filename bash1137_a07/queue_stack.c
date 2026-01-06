/*
 -------------------------------------------------------
 About:    queue and stack DS implementation
 Author:   HBF
 Version:  2025-10-28
 -------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue_stack.h"

/* ---------- Queue functions ---------- */
void enqueue(QUEUE *qp, TNODE *node) {
    QNODE *p = (QNODE *)malloc(sizeof(QNODE));
    if (p != NULL) {
        p->data = node;
        p->next = NULL;
        if (qp->rear == NULL) {
            qp->front = p;
            qp->rear = p;
        } else {
            qp->rear->next = p;
            qp->rear = p;
        }
    }
}

TNODE *dequeue(QUEUE *qp) {
    TNODE *r = NULL;
    if (qp->front != NULL) {
        QNODE *p = qp->front;
        r = p->data;
        qp->front = p->next;
        if (qp->front == NULL) {
            qp->rear = NULL;
        }
        free(p);
    }
    return r;
}

int is_empty_queue(QUEUE *qp) {
    return (qp->front == NULL);
}

/* ---------- Stack functions ---------- */
void push(STACK *sp, TNODE *node) {
    SNODE *p = (SNODE *)malloc(sizeof(SNODE));
    if (p != NULL) {
        p->data = node;
        p->next = sp->top;
        sp->top = p;
    }
}

TNODE *pop(STACK *sp) {
    TNODE *r = NULL;
    if (sp->top != NULL) {
        SNODE *p = sp->top;
        r = p->data;
        sp->top = p->next;
        free(p);
    }
    return r;
}

int is_empty_stack(STACK *sp) {
    return (sp->top == NULL);
}