// Created by Marcin Kozub.
#include "library.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* TMP_FILE_NAME;
int LINES;

struct Array* create_array(int size){
    struct Array* array = calloc(1, sizeof(struct Array));

    array->size = size;
    array->last_added_index = -1;
    array->blocks = calloc(size, sizeof(struct Block*));

    printf("Created array of the size %d\n\n", size);

    return array;
}

void add_to_array(struct Array* array, char* file_name){

    if(file_name == NULL){
        perror("File not found.");
        exit(1);
    }

    if(array->last_added_index == array->size - 1){
        perror("Array is too small.");
        exit(1);
    }



    int current_index = array->last_added_index + 1;

    array->blocks[current_index] = calloc(1, sizeof (struct Block));
    array->blocks[current_index]->value = calloc(strlen(file_name) + 1, sizeof (char));
    strcpy(array->blocks[current_index]->value, file_name);
    array->last_added_index++;

    printf("%s has been added.\n\n", file_name);
}

// Input: array of file names.
void count(struct Array* array){
    int last_index = array->last_added_index;

    if(TMP_FILE_NAME == NULL) {
        char tmp[] = "/tmp/tmp.XXXXXX";
        mkstemp(tmp);
        TMP_FILE_NAME = calloc(strlen(tmp) + 1, sizeof(char));
        strcpy(TMP_FILE_NAME, tmp);
        LINES = 0;
    }

    for(int i = 0; i <= last_index; i++){

        char* command = calloc(strlen(TMP_FILE_NAME) + strlen(array->blocks[i]->value) + 8, sizeof (char));
        strcpy(command, "wc ");
        strcat(command, array->blocks[i]->value);
        strcat(command, " >> ");
        strcat(command, TMP_FILE_NAME);

        system(command);

        LINES++;
    }
}

int add_result(struct Array* array){
    int index = array->last_added_index + 1;
    array->last_added_index++;

    //array->blocks[index] = calloc(1, sizeof (struct Block)); // To delete
    struct Block* block = calloc(1, sizeof (struct Block));

    if(array->last_added_index == array->size){
        perror("Array is too small.");
        exit(1);
    }

    if(TMP_FILE_NAME == NULL){
        perror("Temporary file does not exist!");
        exit(1);
    }

    block->rows = calloc(LINES, sizeof (char*));

    FILE* tmp = fopen(TMP_FILE_NAME, "r");


    int i = 0;
    char* line = (char*) calloc(256, sizeof (char));
    while(fgets(line, 256*sizeof (char), tmp)){
        char* row = (char*) calloc(256, sizeof (char));
        strcpy(row, line);
        block->rows[i++] = row;
    }

    block->rows_number = i;
    array->blocks[index] = block;


    fclose(tmp);
    remove(TMP_FILE_NAME);
    TMP_FILE_NAME = NULL;
    LINES = 0;
    return index;
}

void remove_block(struct Array* array, int index){
    if(array->blocks[index] == NULL) return;

    free(array->blocks[index]);
    array->blocks[index] = NULL;
    array->last_added_index--;

    printf("Removed block at index %d\n\n", index);
}

void print_block_value(int i, struct Block* block){
    printf("%d: %s\n", i, block->value);
}

void print_block_rows(struct Block* block){
    for(int i=0; i<block->rows_number; i++){
        if(block->rows[i] != NULL){
            printf("%d: %s\n", i, block->rows[i]);
        }
    }
    printf("\n\n");
}

void print_array_values(struct Array* array){
    for(int i=0; i<array->last_added_index + 1;i++){
        print_block_value(i, array->blocks[i]);
    }
    printf("\n\n");
}

void print_array_rows(struct Array* array){
    struct Block* block;
    for(int i=0; i<array->size; i++){
        block = array->blocks[i];
        if(block == NULL) continue;
        printf("NUMBER OF THE BLOCK %d\n", i);
        print_block_rows(block);
    }
}