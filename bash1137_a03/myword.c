/*
--------------------------------------------------
Project: a3q2
File:    myword.c
Author:  Manahil Bashir
Version: 2025-10-01
--------------------------------------------------
*/
#include <stdio.h>
#include <string.h>
#include "mystring.h"
#include "myword.h"

#define MAX_LINE_LEN 1000
#define MAX_DICT_LEN 50000   

/**
 * Read stop-words from file and build a dictionary.
 * Dictionary is stored as a single string with each word followed by a space.
 */
int create_dictionary(FILE *fp, char *dictionary) {
    char line[MAX_LINE_LEN];
    int count = 0;
    dictionary[0] = '\0'; 

    while (fgets(line, MAX_LINE_LEN, fp)) {
        str_trim(line);
        str_lower(line);

        char *token = strtok(line, " ,.\t\n\r");
        while (token != NULL) {
            strcat(dictionary, token);
            strcat(dictionary, " ");
            count++;
            token = strtok(NULL, " ,.\t\n\r");
        }
    }
    return count;
}

/**
 * Check if word is in dictionary.
 */
BOOLEAN contain_word(char *dictionary, char *word) {
    char temp[25];
    strcpy(temp, word);
    str_lower(temp);

    char pattern[30];
    sprintf(pattern, "%s ", temp);

    return (strstr(dictionary, pattern) != NULL) ? TRUE : FALSE;
}

/**
 * Process words from text file and collect statistics.
 */
WORDSTATS process_words(FILE *fp, WORD *words, char *dictionary) {
    WORDSTATS stats = {0, 0, 0};
    char line[MAX_LINE_LEN];
    int word_index = 0;

    while (fgets(line, MAX_LINE_LEN, fp)) {
        stats.line_count++;
        str_trim(line);
        str_lower(line);

        char *token = strtok(line, " ,.\t\n\r");
        while (token != NULL) {
            stats.word_count++;

            if (!contain_word(dictionary, token)) {
                int found = 0;
                for (int i = 0; i < word_index; i++) {
                    if (strcmp(words[i].word, token) == 0) {
                        words[i].count++;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(words[word_index].word, token);
                    words[word_index].count = 1;
                    word_index++;
                }
            }
            token = strtok(NULL, " ,.\t\n\r");
        }
    }
    stats.keyword_count = word_index;
    return stats;
}
