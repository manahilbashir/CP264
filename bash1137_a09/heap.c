/*
--------------------------------------------------
Project: a9q3
File:    heap.c
Author:  Manahil Bashir
Version: 2025-11-05
--------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "heap.h"

#define PARENT(i) ((i - 1) / 2)
#define LEFT(i) (2*i + 1)
#define RIGHT(i) (2*i + 2)

HEAP *new_heap(int capacity)
{
  HEAP *hp = (HEAP*) malloc(sizeof(HEAP));
  if (hp == NULL) return NULL;
  hp->hda = (HEAPDATA *) malloc(sizeof(HEAPDATA) * capacity);
  if ( hp->hda == NULL) { free(hp); return NULL; };
  hp->capacity = capacity;
  hp->size = 0;
  return hp;
}

// you may add this function to be used other functions.
int heapify_up(HEAPDATA *hda, int index) {

    while (index > 0) {
        int parent = PARENT(index);
        if (hda[index].key < hda[parent].key) {
            HEAPDATA temp = hda[index];
            hda[index] = hda[parent];
            hda[parent] = temp;
            index = parent;
        } else break;
    }
    return index;
}

// you may add this function to be used other functions.
int heapify_down(HEAPDATA *hda, int n, int index) {

    while (1) {
        int left = LEFT(index);
        int right = RIGHT(index);
        int smallest = index;

        if (left < n && hda[left].key < hda[smallest].key)
            smallest = left;
        if (right < n && hda[right].key < hda[smallest].key)
            smallest = right;

        if (smallest != index) {
            HEAPDATA temp = hda[index];
            hda[index] = hda[smallest];
            hda[smallest] = temp;
            index = smallest;
        } else break;
    }
    return index;
}

void heap_insert(HEAP *heap, HEAPDATA new_node)
{
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->hda = realloc(heap->hda, heap->capacity * sizeof(HEAPDATA));
    }

    heap->hda[heap->size] = new_node;
    heapify_up(heap->hda, heap->size);
    heap->size++;
}

HEAPDATA heap_find_min(HEAP *heap)
{
    return heap->hda[0];
}

HEAPDATA heap_extract_min(HEAP *heap)
{
     HEAPDATA min = heap->hda[0];

    heap->size--;
    heap->hda[0] = heap->hda[heap->size];

    heapify_down(heap->hda, heap->size, 0);

    if (heap->size <= heap->capacity / 4 && heap->capacity > 4) {
        heap->capacity /= 2;
        heap->hda = (HEAPDATA*) realloc(heap->hda, sizeof(HEAPDATA) * heap->capacity);
    }

    return min;
}

int heap_change_key(HEAP *heap, int index, KEYTYPE new_key)
{
    KEYTYPE old = heap->hda[index].key;
    heap->hda[index].key = new_key;

    int new_index;

    if (new_key < old)
        new_index = heapify_up(heap->hda, index);
    else
        new_index = heapify_down(heap->hda, heap->size, index);

    return new_index;
}

int heap_search_value(HEAP *heap, VALUETYPE data) {

    for (int i = 0; i < heap->size; i++) {
        if (heap->hda[i].value == data)
            return i;
    }
    return -1;
}

void heap_sort(HEAPDATA *arr, int n){

    for (int i = n/2 - 1; i >= 0; i--)
        heapify_down(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        HEAPDATA temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify_down(arr, i, 0);
    }
}

void heap_clean(HEAP **heapp) {
  if (heapp) {
    HEAP *heap = *heapp;
    if (heap->capacity > 0) {
      heap->capacity = 0;
      heap->size = 0;
      free(heap->hda);
      free(heap);
    }
    *heapp = NULL;
  }
}
