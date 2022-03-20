// Created by Marcin Kozub using read() and write()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/times.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

struct tms tmsStart, tmsEnd;
clock_t clockStart, clockEnd;

void save_times(int file);

void scanf_error();

void write_error();

double time_in_seconds(clock_t start, clock_t end) {
    return (double)(end - start) / (double)sysconf(_SC_CLK_TCK);
}

int main(int argc, char* argv[]) {
    clockStart = times(&tmsStart);

    if(argc == 2){
        printf("%d\n", argc);
        perror("There are not enough arguments!");
        exit(-1);
    }

    if(argc > 3){
        perror("There are too many arguments!");
        exit(-1);
    }

    char* filename = calloc(256, sizeof (char));
    char* inp = calloc(256, sizeof (char));
    char character;

    unsigned int i;

    if(argc == 3) {
        filename = argv[2];
        if(strlen(argv[1]) > 1){
            perror("This is not a character!");
            exit(-1);
        }
        character = argv[1][0];
    }  else {
        // direct input from the user
        printf("File name:\n");
        i = scanf("%s", filename);
        if(i != 1){
            scanf_error();
        }
        printf("Character:\n");
        i = scanf("%s", inp);
        if( i != 1){
            scanf_error();
        }
        if(strlen(inp) > 1){
            perror("This is not a character!");
            exit(-1);
        } else {
            character = inp[0];
        }
    }

    int file = open(filename, O_RDONLY);

    unsigned int counter = 0;
    unsigned int prev_counter = 0;
    unsigned int rows = 0;
    char file_character = 'a';


    while(read(file, &file_character, 1) == 1){

        if(file_character == character){
            counter++;
        }

        if(file_character == '\n' && counter - prev_counter > 0){
            prev_counter = counter;
            rows++;
        }
    }

    if(counter - prev_counter > 0){
        rows++;
    }

    close(file);
    clockEnd = times(&tmsEnd);
    printf("Counter of character %c: %d\n", character, counter);
    printf("Counter of rows with this character %c: %d\n", character, rows);

    int file_results = open("pomiar_zad_2b", O_WRONLY|O_CREAT, S_IRUSR | S_IWUSR);

    save_times(file_results);

    close(file_results);


    free(inp);
    if(argc != 3) {
        free(filename);
    }
    return 0;
}

void write_error(){
    perror("Write error!");
    exit(-1);
}

void save_times(int file){
    long int num;
    num = write(file, "Time results\n--------------------\n", 34);
    if(num == -1){
        write_error();
    }

    num = write(file, "real time: ", 11);
    if(num == -1){
        write_error();
    }
    char str1[100];
    snprintf(str1, 100, "%f", time_in_seconds(clockStart,clockEnd));
    num = write(file, str1, strlen(str1));
    if(num == -1){
        write_error();
    }
    num = write(file, "\n", 1);
    if(num == -1){
        write_error();
    }

    num = write(file, "sys time: ", 10);
    if(num == -1){
        write_error();
    }
    char str2[100];
    snprintf(str2, 100, "%f", time_in_seconds(tmsStart.tms_stime,tmsEnd.tms_stime));
    num = write(file, str2, strlen(str2));
    if(num == -1){
        write_error();
    }
    num = write(file, "\n", 1);
    if(num == -1){
        write_error();
    }

    num = write(file, "user time: ", 11);
    if(num == -1){
        write_error();
    }
    char str3[100];
    snprintf(str3, 100, "%f", time_in_seconds(tmsStart.tms_utime,tmsEnd.tms_utime));
    num = write(file, str3, strlen(str3));
    if(num == -1){
        write_error();
    }
    num = write(file, "\n\n", 2);
    if(num == -1){
        write_error();
    }
}

void scanf_error(){
    perror("Scanf error!");
    exit(-1);
}