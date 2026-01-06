/*
--------------------------------------------------
Project: a3q1
File:    mystring.c
Author:  Manahil Bashir
Version: 2025-10-01
--------------------------------------------------
*/
#include "mystring.h"

/**
 * Count number of words in a string.
 * A word starts with an English character and ends before a space, tab, comma, or period.
 */
int str_words(char *s) {
    int count = 0;
    int in_word = 0;

    while (*s != '\0') {
        if ((*s >= 'A' && *s <= 'Z') || (*s >= 'a' && *s <= 'z')) {
            if (!in_word) {
                in_word = 1;
                count++;
            }
        } else if (*s == ' ' || *s == '\t' || *s == ',' || *s == '.') {
            in_word = 0;
        } else {
            in_word = 0;
        }
        s++;
    }
    return count;
}

/**
 * Convert uppercase letters to lowercase.
 * Return number of flips made.
 */
int str_lower(char *s) {
    int flips = 0;
    while (*s != '\0') {
        if (*s >= 'A' && *s <= 'Z') {
            *s = *s - 'A' + 'a';
            flips++;
        }
        s++;
    }
    return flips;
}

/**
 *  Trim unnecessary spaces in string.
 *  Remove leading spaces
 *  Replace multiple spaces with a single space
 *  Remove trailing spaces
 */
void str_trim(char *s) {
    char *src = s;
    char *dst = s;
    int space_seen = 1;  

    while (*src == ' ') {
        src++;
    }

    while (*src != '\0') {
        if (*src == ' ') {
            if (!space_seen) {
                *dst++ = ' ';
                space_seen = 1;
            }
        } else {
            *dst++ = *src;
            space_seen = 0;
        }
        src++;
    }

    if (dst > s && *(dst - 1) == ' ') {
        dst--;
    }

    *dst = '\0';
}