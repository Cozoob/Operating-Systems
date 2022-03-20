// Created by Marcin Kozub using fread() and fwrite()
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/times.h>
#include <unistd.h>

struct tms tmsStart, tmsEnd;
clock_t clockStart, clockEnd;

void scanf_error();

void save_times(FILE* file);

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

    FILE* file1 = fopen(filename1, "r");
    FILE* file2 = fopen(filename2, "w+");

    char* character = calloc(2, sizeof (char));

    unsigned int num;
    // firstly, find the first line!
    while(!feof(file1)) { // better than using while true...
        num = fread(character, 1, 1, file1);

        if(feof(file1)){ // It is already the end of the file!
            break;
        }

        if(!num){ // fread failed
            perror("Fread error!");
            exit(-1);
        }

        if(character[0] == '\n') {
            continue;
        } else{
            fwrite(character, 1, 1, file2);
            break;
        }
    }

    unsigned int counter = 0;
    while(!feof(file1)) { // better than using while true...
        num = fread(character, 1, 1, file1);

        if(feof(file1)){ // It is already the end of the file!
            break;
        }

        if(!num){ // fread failed
            perror("Fread error!");
            exit(-1);
        }

        if(character[0] == '\n') {
            counter++;
            if(counter == 1){
                fwrite(character, 1, 1, file2);
            }
        } else {
            counter = 0;
            fwrite(character, 1, 1, file2);
        }
    }



    fclose(file1);
    fclose(file2);
    if(argc != 3) {
        free(filename1);
        free(filename2);
    }

    clockEnd = times(&tmsEnd);
    FILE* file_results = fopen("pomiar_zad_1a", "w+");

    save_times(file_results);

    fclose(file_results);
    return 0;
}

void scanf_error(){
    perror("Scanf error!");
    exit(-1);
}

void save_times(FILE* file){
    fprintf(file, "Time results\n--------------------\n");
    fprintf(file, "real time: %f\n", time_in_seconds(clockStart,clockEnd));
    fprintf(file, "sys time: %f\n", time_in_seconds(tmsStart.tms_stime,tmsEnd.tms_stime));
    fprintf(file, "user time: %f\n\n", time_in_seconds(tmsStart.tms_utime,tmsEnd.tms_utime));
}
