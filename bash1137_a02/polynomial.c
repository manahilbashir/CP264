/*
--------------------------------------------------
Project: a2q2
File:    polynomial.c
Author:  Manahil Bashir
Version: 2025-09-24
--------------------------------------------------
*/
#include <stdio.h>
#include "polynomial.h"
#define EPSILON 1e-6
#define MAXCOUNT 100

/**
 * Evaluate polynomial p(x) using Horner's method.
 * p(x) = p[0]*x^(n-1) + ... + p[n-1]
 */
float horner(float *p, int n, float x)
{
    float result = p[0];
    for (int i = 1; i < n; i++) {
        result = result * x + p[i];
    }
    return result;
}

/**
 * Compute derivative polynomial coefficients.
 * If p(x) = p[0]*x^(n-1) + ... + p[n-1],
 * then d(x) = (n-1)*p[0]*x^(n-2) + ... + 1*p[n-2]
 */
void derivative(float *p, float *d, int n)
{
    for (int i = 0; i < n - 1; i++) {
        d[i] = (float)(n - 1 - i) * p[i];
    }
}

/**
 * Newton’s method to approximate a real root of p(x).
 * x_{k+1} = x_k - p(x_k)/p’(x_k)
 * Stops if |p(x)| < EPSILON or max iterations reached.
 */
float newton(float *p, int n, float x0)
{
    float d[100];  
    derivative(p, d, n);

    float x = x0;
    for (int i = 0; i < MAXCOUNT; i++) {
        float fx = horner(p, n, x);
        if (fx > -EPSILON && fx < EPSILON) {
            return x; 
        }

        float fpx = horner(d, n - 1, x);
        if (fpx == 0) break; 

        x = x - fx / fpx;
    }
    return x0; 
}