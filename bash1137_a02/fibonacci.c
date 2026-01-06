/*
--------------------------------------------------
Project: a2q1
File:    fibonacci.c
Author:  Manahil Bashir
Version: 2025-09-24
--------------------------------------------------
*/
#include <limits.h>
#include "fibonacci.h"

/**
 * Recursive Fibonacci calculation.
 * Uses recursion to compute F(n). Returns -1 if overflow occurs.
 */
int recursive_fibonacci(int n) {
    if (n < 0) return -1;
    if (n == 0) return 0;
    if (n == 1) return 1;

    int f1 = recursive_fibonacci(n - 1);
    int f2 = recursive_fibonacci(n - 2);

    if (f1 == -1 || f2 == -1) return -1;
    if (f1 > INT_MAX - f2) return -1; 

    return f1 + f2;
}

/**
 * Iterative Fibonacci calculation.
 * Uses a loop to compute F(n). Returns -1 if overflow occurs.
 */
int iterative_fibonacci(int n)
{
    if (n < 0) return -1;
    if (n == 0) return 0;
    if (n == 1) return 1;

    int a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        if (b > INT_MAX - a) {
            return -1; 
        }
        int temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

/**
 * Dynamic Programming - Bottom-Up.
 * Uses an external array f[n+1].
 * Returns F(n) or -1 if overflow occurs.
 */
int dpbu_fibonacci(int *f, int n) {
    if (n < 0) return -1;

    f[0] = 0;
    if (n > 0) f[1] = 1;

    for (int i = 2; i <= n; i++) {
        if (f[i-1] > INT_MAX - f[i-2]) {
            return -1; 
        }
        f[i] = f[i-1] + f[i-2];
    }
    return f[n];
}

/**
 * Dynamic Programming - Top-Down.
 * Uses recursion with memoization in external array f[n+1].
 * Returns F(n) or -1 if overflow occurs.
 */
int dptd_fibonacci(int *f, int n) {
    if (n < 0) return -1;

    if (n == 0) return 0;
    if (n == 1) return 1;

    if (f[n] != 0) return f[n];

    int f1 = dptd_fibonacci(f, n - 1);
    int f2 = dptd_fibonacci(f, n - 2);

    if (f1 == -1 || f2 == -1) return -1;
    if (f1 > INT_MAX - f2) return -1; 

    f[n] = f1 + f2;
    return f[n];
}