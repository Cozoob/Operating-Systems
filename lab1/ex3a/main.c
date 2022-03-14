// Created by Marcin Kozub.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"
#include <unistd.h>
#include <sys/times.h>
#include <ctype.h>

/*
 * INPUT:
 * SIZE OF THE MAIN ARRAY, COMMANDS TO DO ...
 *
 *  AVAILABLE COMMANDS:
 *  create_table size:int
 *  wc_files file1.txt file2.txt ...:chars
 *  remove_block index:int
 */

struct tms tmsStart, tmsEnd;
clock_t clockStart, clockEnd;

struct Array* array;
struct Array* files_array;

double time_in_seconds(clock_t start, clock_t end) {
    return (double)(end - start) / (double)sysconf(_SC_CLK_TCK);
}

void print_times(char* operation, FILE* file);

void print_error_message();

void print_integer_error_message();

int check_is_number(char* arg);

int check_command(char* command);

void create_table(int size, FILE* file);

void remove_table_block(int index, FILE* file);

int main(int argc, char* argv[]){ // Testing programme.

    FILE* file = fopen("results3a.txt", "a");

    if(argc < 2){
        print_error_message();
        exit(1);
    }

    if(check_is_number(argv[1]) == 0){
        print_error_message();
        exit(1);
    }

    long int size = strtol(argv[1], NULL, 10);

    if(size <= 0){
        print_error_message();
        print_integer_error_message();
        exit(1);
    }

    clockStart = times(&tmsStart);
    create_table((int)size, file);
    clockEnd = times(&tmsEnd);
    print_times("CREATING ARRAY", file);

    int index = 2;
    while(index < argc){
        int i = check_command(argv[index]);


        if(i==1){
            // option i=1 - create table
            // check if the next argument is the integer greater than 0
            index++;
            if(check_is_number(argv[index])){
                long int table_size = strtol(argv[index], NULL, 10);
                if(table_size <= 0){
                    print_integer_error_message();
                    exit(1);
                }
                create_table((int)table_size, file);
            } else{
                print_integer_error_message();
                exit(1);
            }
        } else if(i==2){
            // option i=2 - remove block
            // check if the next argument is the integer greater than -1
            index++;

            if(array == NULL){
                perror("Create table first!\n");
                exit(1);
            } else if(check_is_number(argv[index])){
                long int table_index = strtol(argv[index], NULL, 10);
                if(table_index < 0){
                    perror("\n"
                           "THE INDEX OF THE MAIN ARRAY MUST BE INTEGER GREATER THAN -1!"
                           "\n");
                    exit(1);
                } else if(table_index >= array->size){
                    perror("\n"
                           "THE INDEX OF THE MAIN ARRAY MUST BE INTEGER LOWER THAN THE SIZE OF ARRAY!"
                           "\n");
                    exit(1);
                }
                remove_table_block((int)table_index, file);
            } else{
                perror("\n"
                       "THE INDEX OF THE MAIN ARRAY MUST BE INTEGER!"
                       "\n");
                exit(1);
            }
        } else if(i==3){
            // option i=3 - wc files
            // load the next arguments as file names...
            // check if they are any other commands

            index++;
            int start = index;

            while(index < argc && check_command(argv[index]) == -1){
                // increment index
                index++;
            }

            if(start == index){
                perror("\n"
                       "There are no files to wc!"
                       "\n");
                exit(1);
            }

            int file_array_size = index - start;
            files_array = create_array(file_array_size);

            for(int k = start; k < start + file_array_size; k++){
                add_to_array(files_array,argv[k]);
            }

            clockStart = times(&tmsStart);

            count(files_array);
            add_result(array);
            print_array_rows(array);
            index--;

            clockEnd = times(&tmsEnd);
            print_times("COUNTING THE FILES", file);

        } else {
            printf("%s\n", argv[index]);
            print_error_message();
            exit(1);
        }


        index++;
    }

    fclose(file);
    return 0;
}

int check_is_number(char* arg){
    unsigned long int size = strlen(arg);
    unsigned long int i = 0;

    while(i < size){
        if(isdigit(arg[i])){
            i++;
        } else{
            return 0;
        }
    }

    return 1;
}

int check_command(char* command){
    if(strcmp("create_table", command) == 0){
        return 1;
    }
    if(strcmp("remove_block", command) == 0){
        return 2;
    }
    if(strcmp("wc_files", command) == 0){
        return 3;
    }
    return -1;
}

void print_integer_error_message(){
    perror("\n"
           "THE SIZE OF THE MAIN ARRAY MUST BE INTEGER GREATER THAN 0!"
           "\n");
}

void print_error_message(){
    perror("Incorrect usage.\n"
           "INPUT:\n"
           "SIZE OF THE MAIN ARRAY, COMMANDS TO DO ...\n"
           "\n"
           "AVAILABLE COMMANDS:\n"
           "create_table size:int\n"
           "wc_files file1.txt file2.txt ...:chars\n"
           "remove_block index:int\n"
    );
}

void print_times(char* operation, FILE* file){ // and save them to the file...
    printf("%s\n--------------------\n", operation);
    printf("real time: %f\n", time_in_seconds(clockStart,clockEnd));
    printf("sys time: %f\n", time_in_seconds(tmsStart.tms_stime,tmsEnd.tms_stime));
    printf("user time: %f\n\n", time_in_seconds(tmsStart.tms_utime,tmsEnd.tms_utime));


    fprintf(file, "%s\n--------------------\n", operation);
    fprintf(file, "real time: %f\n", time_in_seconds(clockStart,clockEnd));
    fprintf(file, "sys time: %f\n", time_in_seconds(tmsStart.tms_stime,tmsEnd.tms_stime));
    fprintf(file, "user time: %f\n\n", time_in_seconds(tmsStart.tms_utime,tmsEnd.tms_utime));

}

void create_table(int size, FILE* file){
    clockStart = times(&tmsStart);
    array = create_array(size);
    clockEnd = times(&tmsEnd);
    print_times("CREATING ARRAY", file);
}

void remove_table_block(int index, FILE* file){
    clockStart = times(&tmsStart);
    remove_block(array, index);
    clockEnd = times(&tmsEnd);
    print_times("REMOVING THE BLOCK", file);
}
