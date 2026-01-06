/*
--------------------------------------------------
Project: a4q1
File:    mysort.h
Author:  Manahil Bashir
Version: 2025-10-06
--------------------------------------------------
*/
#ifndef MYSORT_H
#define MYSORT_H 

/**
 * Use selection sort algorithm to sort array of pointers such that their pointed values 
 * are in increasing order.
 *
 * @param *a[] - array of void pointers.
 * @param left - start index.
 * @param right - end index.
 */
void select_sort(void *a[], int left, int right);


/**
 * Use quick sort algorithm to sort array of pointers such that their pointed values 
 * are in increasing order.
 *
 * @param *a[] - array of void pointers.
 * @param left - start index.
 * @param right - end index.
 */
void quick_sort(void *a[], int left, int right);

/**
 * Use either selection or quick sort algorithm to sort array of pointers 
 * based on a given comparison function.
 *
 * @param *a[] - array of void pointers.
 * @param left - start index.
 * @param right - end index.
 * @param (*cmp) - pointer to a comparison function.
 */
void my_sort(void *a[], int left, int right, int (*cmp)(void*, void*) );

#endif