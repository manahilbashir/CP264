/*
--------------------------------------------------
Project: a6q3
File:    expression.c
Author:  Manahil Bashir
Version: 2025-10-22
--------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "queue.h"
#include "stack.h"
#include "expression.h"

/*
 * Helper function to determine operator precedence
 */
int precedence(char op) {
    int p = 0;
    if (op == '+' || op == '-') {
        p = 1;
    } else if (op == '*' || op == '/') {
        p = 2;
    }
    return p;
}

QUEUE infix_to_postfix(char *infixstr) {
    QUEUE q = {0, NULL, NULL};
    STACK s = {0, NULL};
    int i = 0;
    char token[64];
    int tlen;

    while (infixstr[i] != '\0') {
        char ch = infixstr[i];

        if (isspace((unsigned char)ch)) {
            i++;
            continue;
        }

        if (isdigit((unsigned char)ch)) {
            tlen = 0;
            while (isdigit((unsigned char)infixstr[i])) {
                if (tlen < (int)sizeof(token)-1) token[tlen++] = infixstr[i];
                i++;
            }
            token[tlen] = '\0';
            int val = atoi(token);
            NODE *np = new_node(val, 0); 
            enqueue(&q, np);
            continue; 
        } else if (ch == '(') {
            NODE *np = new_node((int)'(', 1);
            push(&s, np);
        } else if (ch == ')') {
            while (s.top != NULL && s.top->type == 1 && (char)(s.top->data) != '(') {
                NODE *np = pop(&s);
                enqueue(&q, np);
            }
            if (s.top != NULL && s.top->type == 1 && (char)(s.top->data) == '(') {
                NODE *leftpar = pop(&s);
                free(leftpar);
            }
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (s.top != NULL && s.top->type == 1 &&
                   precedence((char)(s.top->data)) >= precedence(ch)) {
                NODE *np = pop(&s);
                enqueue(&q, np);
            }
            NODE *opn = new_node((int)ch, 1);
            push(&s, opn);
        } else {
        }

        i++;
    }

    while (s.top != NULL) {
        NODE *np = pop(&s);
        enqueue(&q, np);
    }

    return q;
}

int evaluate_postfix(QUEUE queue) {
    STACK s = {0, NULL};
    NODE *np = queue.front;

    while (np != NULL) {
        if (np->type == 0) {
            NODE *numNode = new_node(np->data, 0);
            push(&s, numNode);
        } else {
            NODE *n2 = pop(&s);
            NODE *n1 = pop(&s);

            if (n1 == NULL || n2 == NULL) {
                if (n1) free(n1);
                if (n2) free(n2);
                clean_stack(&s);
                return 0;
            }

            int a = n1->data;
            int b = n2->data;
            int result = 0;
            char op = (char)(np->data);

            if (op == '+') result = a + b;
            else if (op == '-') result = a - b;
            else if (op == '*') result = a * b;
            else if (op == '/') {
                if (b == 0) {
                    result = 0;
                } else {
                    result = a / b;
                }
            }

            free(n1);
            free(n2);

            NODE *resNode = new_node(result, 0);
            push(&s, resNode);
        }

        np = np->next;
    }

    NODE *res = pop(&s);
    int final = 0;
    if (res != NULL) {
        final = res->data;
        free(res);
    }

    clean_stack(&s);

    return final;
}

int evaluate_infix(char *infixstr) {
    QUEUE q = infix_to_postfix(infixstr);
    int result = evaluate_postfix(q);
    clean_queue(&q);
    return result;
}