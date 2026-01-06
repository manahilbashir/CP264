/*
--------------------------------------------------
Project: a4q1
File:    mysort.c
Author:  Manahil Bashir
Version: 2025-10-06
--------------------------------------------------
*/
#include "mysort.h"

/* ---- Helper function prototypes ---- */
void swap(void **x, void **y);
int cmp(void *x, void *y);
int partition(void *a[], int left, int right);

// swap pointers
void swap(void **x, void **y) {
     void *temp = *y;
     *y = *x;
     *x = temp;
}

// a compare floating values pointed by void pointers. 
int cmp(void *x, void *y) {
   float a = *(float*)x;
   float b = *(float*)y; 
     if (a > b) return 1;
     else if (a < b) return -1;
     else return 0;
}   

void select_sort(void *a[], int left, int right)
{
    int i, j, min_index;
    for (i = left; i < right; i++) {
        min_index = i;
        for (j = i + 1; j <= right; j++) {
            if (cmp(a[j], a[min_index]) < 0) {
                min_index = j;
            }
        }
        if (min_index != i)
            swap(&a[i], &a[min_index]);
    }
}

/* ---- Partition for Quick Sort ---- */
int partition(void *a[], int left, int right) {
    void *pivot = a[right];
    int i = left - 1;
    int j;
    for (j = left; j < right; j++) {
        if (cmp(a[j], pivot) <= 0) {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[right]);
    return i + 1;
}

void quick_sort(void *a[], int left, int right)
{ 
    if (left < right) {
        int p = partition(a, left, right);
        quick_sort(a, left, p - 1);
        quick_sort(a, p + 1, right);
    }
}

void my_sort(void *a[], int left, int right, int (*cmp_fn)(void*, void*)) {
    int i, j;
    for (i = left; i < right; i++) {
        for (j = i + 1; j <= right; j++) {
            if (cmp_fn(a[i], a[j]) > 0) {  
                swap(&a[i], &a[j]);
            }
        }
    }
}