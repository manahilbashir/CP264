/*
--------------------------------------------------
Project: a4q2
File:    myrecord.c
Author:  Manahil Bashir
Version: 2025-10-06
--------------------------------------------------
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "myrecord.h"
#include "mysort.h"

// ----------------------------
// Helper: compare scores (used in sorting RECORD pointers)
// ----------------------------
int cmp1(void *x, void *y) {
    float b = ((RECORD*) x)->score;
    float a = ((RECORD*) y)->score;
    if (a > b) return 1;
    else if (a < b) return -1;
    else return 0;
}

/* comparator for sorting float * elements in ascending order */
static int cmp_float_asc(void *x, void *y) {
    float a = *(float*)x;   
    float b = *(float*)y;   
    if (a > b) return 1;
    else if (a < b) return -1;
    else return 0;
}

// ----------------------------
// Helper: compute median
// ----------------------------
float compute_median(RECORD dataset[], int n) {
    if (n == 0) return 0;

    float *a[n];
    for (int i = 0; i < n; i++) {
        a[i] = &dataset[i].score;
    }

    my_sort((void *)a, 0, n - 1, (int (*)(void *, void *))cmp_float_asc);

    if (n % 2 == 1)
        return *a[n / 2];
    else
        return (*a[n / 2 - 1] + *a[n / 2]) / 2.0;
}

GRADE grade(float score){
    GRADE g;

    if (score >= 90) strcpy(g.letter_grade, "A+");
    else if (score >= 85) strcpy(g.letter_grade, "A");
    else if (score >= 80) strcpy(g.letter_grade, "A-");
    else if (score >= 77) strcpy(g.letter_grade, "B+");
    else if (score >= 73) strcpy(g.letter_grade, "B");
    else if (score >= 70) strcpy(g.letter_grade, "B-");
    else if (score >= 67) strcpy(g.letter_grade, "C+");
    else if (score >= 63) strcpy(g.letter_grade, "C");
    else if (score >= 60) strcpy(g.letter_grade, "C-");
    else if (score >= 57) strcpy(g.letter_grade, "D+");
    else if (score >= 53) strcpy(g.letter_grade, "D");
    else if (score >= 50) strcpy(g.letter_grade, "D-");
    else strcpy(g.letter_grade, "F");

    return g; 
}

int import_data(FILE *fp, RECORD *dataset) {
    if (fp == NULL) return 0;

    int count = 0;
    while (fscanf(fp, "%[^,],%f\n", dataset[count].name, &dataset[count].score) == 2) {
        count++;
    }
    return count;
}

STATS process_data(RECORD *dataset, int count) {    
    STATS stats = {0, 0.0, 0.0, 0.0};
    if (count <= 0) return stats;

    stats.count = count;

    float sum = 0;
    for (int i = 0; i < count; i++) {
        sum += dataset[i].score;
    }
    stats.mean = sum / count;

    float var_sum = 0;
    for (int i = 0; i < count; i++) {
        var_sum += pow(dataset[i].score - stats.mean, 2);
    }
    stats.stddev = sqrt(var_sum / count);

    stats.median = compute_median(dataset, count);

    return stats;
}


int report_data(FILE *fp, RECORD *dataset, STATS stats) {
    if (fp == NULL || stats.count < 1) return 0;

    int n = stats.count;
    RECORD *p[n];
    for (int i = 0; i < n; i++) {
        p[i] = &dataset[i];
    }

    my_sort((void *)p, 0, n - 1, cmp1);

    fprintf(fp, "Record Data Summary\n");
    fprintf(fp, "Count: %d\n", stats.count);
    fprintf(fp, "Mean: %.2f\n", stats.mean);
    fprintf(fp, "Stddev: %.2f\n", stats.stddev);
    fprintf(fp, "Median: %.2f\n\n", stats.median);

    fprintf(fp, "Name\tScore\tGrade\n");
    for (int i = 0; i < n; i++) {
        GRADE g = grade(p[i]->score);
        fprintf(fp, "%s\t%.1f\t%s\n", p[i]->name, p[i]->score, g.letter_grade);
    }

    return 1;
}
