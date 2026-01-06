/*
--------------------------------------------------
Project: a7q3
File:    myrecord_bst.c
Author:  Manahil Bashir
Version: 2025-11-05
--------------------------------------------------
*/
 
#include <stdio.h>
#include <math.h>
#include "bst.h"
#include "myrecord_bst.h"

void add_record(BSTDS *ds, RECORD record) {
    float x = record.score;

    bst_insert(&ds->root, record);

    if (ds->count == 0) {
        ds->count = 1;
        ds->mean = x;
        ds->stddev = 0;
    } else {
        int n = ds->count;
        float old_mean = ds->mean;
        float old_std = ds->stddev;

        ds->count++;
        ds->mean = old_mean + (x - old_mean) / ds->count;
        ds->stddev = sqrt(((n - 1) * old_std * old_std + (x - ds->mean) * (x - old_mean)) / n);
    }
}

void remove_record(BSTDS *ds, char *name) {
    BSTNODE *node = bst_search(ds->root, name);
    if (node == NULL)
        return;

    float x = node->data.score;

    bst_delete(&ds->root, name);

    if (ds->count <= 1) {
        ds->count = 0;
        ds->mean = 0;
        ds->stddev = 0;
        return;
    }

    int n = ds->count;
    float old_mean = ds->mean;
    float old_std = ds->stddev;

    ds->count--;
    ds->mean = (n * old_mean - x) / ds->count;

    if (ds->count > 1)
        ds->stddev = sqrt(((n - 1) * old_std * old_std - (x - ds->mean) * (x - old_mean)) / ds->count);
    else
        ds->stddev = 0;  
}

void bstds_clean(BSTDS *ds) {
  bst_clean(&ds->root);
  ds->count = 0;
  ds->mean = 0;
  ds->stddev = 0;
}
