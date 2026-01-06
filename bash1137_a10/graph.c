/*
--------------------------------------------------
Project: a10q2
File:    graph.c
Author:  Manahil Bashir
Version: 2025-11-05
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue_stack.h"
#include "graph.h"

GRAPH *new_graph(int order) {
  GRAPH *gp = malloc(sizeof(GRAPH));
  gp->nodes = malloc(order * sizeof(GNODE*));
  
  int i;
  for (i = 0; i < order; i++) {
    gp->nodes[i] = malloc(sizeof(GNODE));
    gp->nodes[i]->nid = i;
    strcpy(gp->nodes[i]->name, "null");
    gp->nodes[i]->neighbor = NULL;
  }
  
  gp->order = order;
  gp->size = 0;  
 
  return gp;
}

void insert_edge_graph(GRAPH *g, int from, int to, int weight) {

    ADJNODE *p = g->nodes[from]->neighbor;

    while (p != NULL) {
        if (p->nid == to) {
            p->weight = weight;
            return;
        }
        p = p->next;
    }

    ADJNODE *np = malloc(sizeof(ADJNODE));
    np->nid = to;
    np->weight = weight;
    np->next = NULL;

    if (g->nodes[from]->neighbor == NULL) {
        g->nodes[from]->neighbor = np;
    } else {
        p = g->nodes[from]->neighbor;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = np;
    }

    g->size++;
}

void delete_edge_graph(GRAPH *g, int from, int to) {

    ADJNODE *p = g->nodes[from]->neighbor;
    ADJNODE *prev = NULL;

    while (p != NULL) {
        if (p->nid == to) {
            if (prev == NULL)
                g->nodes[from]->neighbor = p->next;
            else
                prev->next = p->next;

            free(p);
            g->size--;
            return;
        }
        prev = p;
        p = p->next;
    }
}

int get_edge_weight(GRAPH *g, int from, int to) {

    ADJNODE *p = g->nodes[from]->neighbor;

    while (p != NULL) {
        if (p->nid == to)
            return p->weight;
        p = p->next;
    }

    return INFINITY;
}

void traverse_bforder(GRAPH *g, int start) {

    int visited[g->order];
    int i;

    for (i = 0; i < g->order; i++)
        visited[i] = 0;

    QUEUE q = {NULL, NULL};

    int *sp = malloc(sizeof(int));
    *sp = start;
    enqueue(&q, sp);

    visited[start] = 1;

    while (q.front != NULL) {
        int *vp = (int*) dequeue(&q);
        int nid = *vp;
        free(vp);

        printf("(%d %s) ", nid, g->nodes[nid]->name);

        ADJNODE *p = g->nodes[nid]->neighbor;
        while (p != NULL) {
            if (!visited[p->nid]) {
                visited[p->nid] = 1;

                int *np = malloc(sizeof(int));
                *np = p->nid;

                enqueue(&q, np);
            }
            p = p->next;
        }
    }

    clean_queue(&q);
}

void traverse_dforder(GRAPH *g, int start) {

    int visited[g->order];
    int i;

    for (i = 0; i < g->order; i++)
        visited[i] = 0;

    STACK s = {NULL};

    int *sp = malloc(sizeof(int));
    *sp = start;
    push(&s, sp);

    while (s.top != NULL) {
        int *vp = pop(&s);
        int nid = *vp;
        free(vp);

        if (!visited[nid]) {
            visited[nid] = 1;
            printf("(%d %s) ", nid, g->nodes[nid]->name);

            ADJNODE *p = g->nodes[nid]->neighbor;

            int count = 0;
            ADJNODE *tmp = p;
            while (tmp != NULL) {
                count++;
                tmp = tmp->next;
            }

            int arr[count];
            int k = 0;
            tmp = p;
            while (tmp != NULL) {
                arr[k++] = tmp->nid;
                tmp = tmp->next;
            }

            for (i = count - 1; i >= 0; i--) {
                if (!visited[arr[i]]) {
                    int *np = malloc(sizeof(int));
                    *np = arr[i];
                    push(&s, np);
                }
            }
        }
    }

    clean_stack(&s);
}

void clean_graph(GRAPH **gp) {
  int i;
  GRAPH *g = *gp;
  ADJNODE *temp, *ptr;
  for (i = 0; i < g->order; i++) {
    ptr = g->nodes[i]->neighbor;
    while (ptr != NULL) {
      temp = ptr;
      ptr = ptr->next;
      free(temp);
    }
    free(g->nodes[i]);
  }
  free(g->nodes);
  free(g);
  *gp = NULL;
}

void display_graph(GRAPH *g) {
  if (g ) {
  printf("order %d ", g->order);
  printf("size %d ", g->size);
  printf("(from to weight) ");
  int i;
  ADJNODE *ptr;
  for (i = 0; i < g->order; i++) {
    //printf("\n%d:", g->nodes[i]->nid);
    ptr = g->nodes[i]->neighbor;
    while (ptr != NULL) {
      printf("(%d %d %d) ", i,  ptr->nid, ptr->weight);
      ptr = ptr->next;
    }
  }
  }
}
