/*
--------------------------------------------------
Project: a10q1
File:    edgelist.c
Author:  Manahil Bashir
Version: 2025-11-05
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h> 
#include "edgelist.h"

EDGELIST *new_edgelist() {
    EDGELIST *tp = malloc(sizeof(EDGELIST));
    tp->size = 0;
    tp->start = NULL;
    tp->end = NULL;
    return tp;
}

void insert_edge_end(EDGELIST *g, int from, int to, int weight) {

    EDGENODE *np = malloc(sizeof(EDGENODE));
    np->from = from;
    np->to = to;
    np->weight = weight;
    np->next = NULL;

    if (g->start == NULL) {        
        g->start = np;
        g->end = np;
    } else {
        g->end->next = np;
        g->end = np;
    }
    g->size++;
}

void insert_edge_start(EDGELIST *g, int from, int to, int weight) {

    EDGENODE *np = malloc(sizeof(EDGENODE));
    np->from = from;
    np->to = to;
    np->weight = weight;

    np->next = g->start;       
    g->start = np;           

    if (g->end == NULL) {       
        g->end = np;
    }
    g->size++;
}

void delete_edge(EDGELIST *g, int from, int to) {

    if (g->start == NULL) {
        return;
    }

    EDGENODE *prev = NULL;
    EDGENODE *cur = g->start;

    while (cur != NULL) {

        if (cur->from == from && cur->to == to) {

            if (prev == NULL) {            
                g->start = cur->next;
            } else {
                prev->next = cur->next;
            }

            if (cur == g->end) {           
                g->end = prev;
            }

            free(cur);
            g->size--;
            return;
        }

        prev = cur;
        cur = cur->next;
    }
}

int weight_edgelist(EDGELIST *g) {

    int total = 0;
    EDGENODE *p = g->start;

    while (p != NULL) {
        total += p->weight;
        p = p->next;
    }

    return total;
}

void clean_edgelist(EDGELIST **gp) {
    EDGELIST *g = *gp;
    EDGENODE *temp, *p = g->start;
    while (p) {
        temp = p;
        p = p->next;
        free(temp);
    }
    free(g);
    *gp = NULL;
}

void display_edgelist(EDGELIST *g) {
    if (g == NULL)
        return;
    printf("size %d ", g->size);
    printf("(from to weight) ");
    EDGENODE *p = g->start;
    while (p) {
        printf("(%d %d %d) ", p->from, p->to, p->weight);
        p = p->next;
    }
}