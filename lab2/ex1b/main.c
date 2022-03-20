// Created by Marcin Kozub using fread() and fwrite()
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/times.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

struct tms tmsStart, tmsEnd;
clock_t clockStart, clockEnd;

void scanf_error();

void write_error();

void save_times(int file);

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

    char* filename1 = calloc(256, sizeof (char));
    char* filename2 = calloc(256, sizeof (char));

    unsigned int i;

    if(argc == 3) {
        filename1 = argv[1];
        filename2 = argv[2];
    }  else {
        // direct input from the user
        printf("File name 1:\n");
        i = scanf("%s", filename1);
        if(i != 1){
            scanf_error();
        }
        printf("File name 2:\n");
        i = scanf("%s", filename2);
        if( i != 1){
            scanf_error();
        }
    }

    if(strcmp(filename1, filename2) == 0){
        perror("File names cannot be named the same!");
        exit(-1);
    }

    int file1 = open(filename1, O_RDONLY);
    int file2 = open(filename2, O_WRONLY|O_CREAT, S_IRUSR | S_IWUSR);

    char character = 'a';
    long int num;
    unsigned int counter = 0;

    // search first characters other than new line
    while(read(file1, &character, 1) == 1) {
        if(character == '\n') {
            continue;
        } else {
            break;
        }
    }

    do {
        if(character == '\n'){
            counter++;
            // check if the next line is also only \n
            if(counter == 1) {
                num = write(file2, &character, 1);
            }
            if(num == -1){
                write_error();
            }

        } else {
            counter = 0;
            num = write(file2, &character, 1);
            if (num == -1) {
                write_error();
            }
        }
    } while(read(file1, &character, 1) == 1);


    close(file1);
    close(file2);
    if(argc != 3) {
        free(filename1);
        free(filename2);
    }

    clockEnd = times(&tmsEnd);
    int file_results = open("pomiar_zad_1b", O_WRONLY|O_CREAT, S_IRUSR | S_IWUSR);

    save_times(file_results);

    close(file_results);
    return 0;
}

void scanf_error(){
    perror("Scanf error!");
    exit(-1);
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