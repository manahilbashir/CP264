/*
--------------------------------------------------
Project: a1q2
File:    powersum.c
Author:  Manahil Bashir
Version: 2025-09-15
--------------------------------------------------
*/

#include "powersum.h"

int power_overflow(int b, int n)
{
    int p = 1;
    for (int i = 1; i <= n; i++) {
        int temp = p * b;
        if (temp / b != p) {
            return 1;
        }
        p = temp;
    }
    return 0;
}

int mypower(int b, int n)
{
    int p = 1;
    for (int i = 1; i <=n; i++) {
        int temp = p * b;
        if (temp / b != p) {
            return 0;
        }
        p = temp;
    }
    return p;
}

int powersum(int b, int n)
{
    int sum = 0;
    int p = 1;
    for (int i = 0; i <= n; i++) {
        if (sum + p < sum) {
            return 0;
        }
        sum += p;

        if (i < n) {
            int temp = p * b;
            if (temp / b != p) {
                return 0;
            }
            p = temp;
        }
    }
    return sum;
}