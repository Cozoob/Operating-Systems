// Created by Marcin Kozub.

#ifndef COUNTER_LIBRARY_H
#define COUNTER_LIBRARY_H

#include <stdio.h>

char* TMP_FILE_NAME;

struct Block{
    int rows_number;
    char* value;
    char** rows;
};

struct Array{
    int size;
    int last_added_index;
    struct Block** blocks;
};

struct Array* create_array(int size);

void add_to_array(struct Array* array, char* file_name);

void count(struct Array* array);

int add_result(struct Array* array);

void remove_block(struct Array* array, int index);

void print_block_value(int i, struct Block* block);

void print_block_rows(struct Block* block);

void print_array_values(struct Array* array);

void print_array_rows(struct Array* array);

#endif //COUNTER_LIBRARY_H
