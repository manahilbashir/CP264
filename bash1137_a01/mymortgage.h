/*
--------------------------------------------------
Project: a1q3
File:    mymortgage.h
Author:  Manahil Bashir
Version: 2025-09-15
--------------------------------------------------
*/

#ifndef MYMORTGAGE_H
#define MYMORTGAGE_H

/**
 * Compute the monthly payment of given mortgage principal.
 */
float monthly_payment(float principal_amount, float annual_interest_rate, int years);

/**
 * Compute the total payment for the mortgage.
 */
float total_payment(float principal_amount, float annual_interest_rate, int years);

/**
 * Compute the total interest paid over the mortgage term.
 */
float total_interest(float principal_amount, float annual_interest_rate, int years);

#endif