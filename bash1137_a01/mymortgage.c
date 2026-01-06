/*
--------------------------------------------------
Project: a1q3
File:    mymortgage.c
Author:  Manahil Bashir
Version: 2025-09-15
--------------------------------------------------
*/

#include "mymortgage.h"
#include <math.h>   

float monthly_payment(float principal_amount, float annual_interest_rate, int years) {
    float r = annual_interest_rate / 100.0 / 12.0;
    int n = years * 12;

    // Formula: (P * r * (1+r)^n) / ((1+r)^n - 1)
    float numerator = principal_amount * r * pow(1 + r, n);
    float denominator = pow(1 + r, n) - 1;

    return numerator / denominator;
}

float total_payment(float principal_amount, float annual_interest_rate, int years) {
    float m = monthly_payment(principal_amount, annual_interest_rate, years);
    int n = years * 12;
    return m * n;
}

float total_interest(float principal_amount, float annual_interest_rate, int years) {
    float total = total_payment(principal_amount, annual_interest_rate, years);
    return total - principal_amount;
}