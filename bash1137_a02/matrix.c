/*
--------------------------------------------------
Project: a2q3
File:    matrix.c
Author:  Manahil Bashir
Version: 2025-09-24
--------------------------------------------------
*/
#include <math.h>
#include "matrix.h"

/**
 * Compute Euclidean norm of vector v.
 */
float norm(float *v, int n) {
    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        sum += v[i] * v[i];
    }
    return sqrtf(sum);
}

/**
 * Normalize vector vin -> vout (unit length).
 */
void normalize(const float *vin, float *vout, int n) {
    float length = norm((float*)vin, n);
    if (length == 0.0f) {
        for (int i = 0; i < n; i++) vout[i] = 0.0f;
    } else {
        for (int i = 0; i < n; i++) {
            vout[i] = vin[i] / length;
        }
    }
}

/**
 * Multiply matrix A by scalar and store in B.
 */
void matrix_scalar_multiply(const float *A, float scalar, float *B, int rows, int cols) {
    for (int i = 0; i < rows * cols; i++) {
        B[i] = A[i] * scalar;
    }
}

/**
 * Transpose matrix A (rows x cols) into B (cols x rows).
 */
void matrix_transpose(const float *A, float *B, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            B[j * rows + i] = A[i * cols + j];
        }
    }
}

/**
 * Add matrices A and B into C.
 */
void matrix_add(const float *A, const float *B, float *C, int rows, int cols) {
    for (int i = 0; i < rows * cols; i++) {
        C[i] = A[i] + B[i];
    }
}

/**
 * Multiply matrices A (rowsA x colsA) and B (colsA x colsB) into C (rowsA x colsB).
 */
void matrix_multiply(const float *A, const float *B, float *C, int rowsA, int colsA, int colsB) {
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            float sum = 0.0f;
            for (int k = 0; k < colsA; k++) {
                sum += A[i * colsA + k] * B[k * colsB + j];
            }
            C[i * colsB + j] = sum;
        }
    }
}