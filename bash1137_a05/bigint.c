/*
--------------------------------------------------
Project: a5q3
File:    bigint.c
Author:  Manahil Bashir
Version: 2025-10-22
--------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"

BIGINT bigint(char *p) {
  BIGINT bn = {0};
  if (p == NULL) 
    return bn;
  else if (!(*p >= '0' && *p <= '9')) {// not begin with digits 
    return bn;
  }
  else if (*p == '0' && *(p+1) == '\0') {// just "0"
    dll_insert_end(&bn, dll_node(*p -'0'));
    return bn;
  }  
  else { 
    while (*p) {
      if (*p >= '0' && *p <= '9' ){
        dll_insert_end(&bn, dll_node(*p -'0'));
      } else {
        dll_clean(&bn);
        break;
      }
      p++;
    }
    return bn;
  }
}

BIGINT bigint_add(BIGINT op1, BIGINT op2) {
    BIGINT sum = {0};
  NODE *p1 = op1.end;
  NODE *p2 = op2.end;
  int carry = 0;

  while (p1 != NULL || p2 != NULL || carry != 0) {
    int d1 = (p1 != NULL) ? p1->data : 0;
    int d2 = (p2 != NULL) ? p2->data : 0;
    int total = d1 + d2 + carry;

    carry = total / 10;
    int digit = total % 10;

    dll_insert_start(&sum, dll_node((char)digit));

    if (p1 != NULL)
      p1 = p1->prev;
    if (p2 != NULL)
      p2 = p2->prev;
  }

  return sum;
}

BIGINT bigint_fibonacci(int n) {
  BIGINT f1 = bigint("1");
  BIGINT f2 = bigint("1");
  BIGINT temp;
  int i = 3;

  if (n <= 1)
    return bigint("1");
  if (n == 2)
    return bigint("1");

  while (i <= n) {
    temp = bigint_add(f1, f2);
    dll_clean(&f1);
    f1 = f2;
    f2 = temp;
    i++;
  }

  dll_clean(&f1);
  return f2;
}
