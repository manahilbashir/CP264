/*
--------------------------------------------------
Project: a9q1
File:    hash.c
Author:  Manahil Bashir
Version: 2025-11-05
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "hash.h"

HNODE *hashtable_search(HASHTABLE *ht, char *name) {
    int index = hash(name, ht->size);
    HNODE *p = ht->hna[index];

    while (p != NULL) {
        if (strcmp(p->data.name, name) == 0) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

int hashtable_insert(HASHTABLE *ht, DATA data) {
    int index = hash(data.name, ht->size);
    HNODE *p = ht->hna[index];

    while (p != NULL) {
        if (strcmp(p->data.name, data.name) == 0) {
            p->data.value = data.value;
            return 0;    
        }
        p = p->next;
    }

    HNODE *node = (HNODE*) malloc(sizeof(HNODE));
    node->data = data;
    node->next = ht->hna[index];
    ht->hna[index] = node;
    ht->count++;

    return 1;
}

int hashtable_delete(HASHTABLE *ht, char *name) {
    int index = hash(name, ht->size);
    HNODE *p = ht->hna[index];
    HNODE *prev = NULL;
    int deleted = 0;

    while (p != NULL && deleted == 0) {
        if (strcmp(p->data.name, name) == 0) {
            if (prev == NULL) {
                ht->hna[index] = p->next;
            } else {
                prev->next = p->next;
            }
            free(p);
            ht->count--;
            deleted = 1;
        } else {
            prev = p;
            p = p->next;
        }
    }
    return deleted;
}


int hash(char* key, int size) {
    unsigned int hash = 0;
    while (*key) {
        hash += *key++;
    }
    return hash % size;
}

HASHTABLE *new_hashtable(int size) {
    HASHTABLE *ht = (HASHTABLE*) malloc(sizeof(HASHTABLE));
    ht->hna = (HNODE**) malloc(sizeof(HNODE**) * size);
    int i;
    for (i = 0; i < size; i++)
        *(ht->hna + i) = NULL;

    ht->size = size;
    ht->count = 0;
    return ht;
}


void hashtable_clean(HASHTABLE **htp) {
    if (*htp == NULL)
        return;
    HASHTABLE *ht = *htp;
    HNODE *p, *temp;
    int i;
    for (i = 0; i < ht->size; i++) {
        p = ht->hna[i];
        while (p) {
            temp = p;
            p = p->next;
            free(temp);
        }
        ht->hna[i] = NULL;
    }
    free(ht->hna);
    ht->hna = NULL;
    *htp = NULL;
}
