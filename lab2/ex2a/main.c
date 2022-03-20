// Created by Marcin Kozub using fread() and fwrite()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/times.h>
#include <unistd.h>

struct tms tmsStart, tmsEnd;
clock_t clockStart, clockEnd;

void save_times(FILE* file);

void scanf_error();

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

    FILE* file = fopen(filename, "r");


    unsigned int num;
    unsigned int counter = 0;
    unsigned int prev_counter = 0;
    unsigned int rows = 0;
    char* file_character = calloc(2, sizeof (char));


    while(!feof(file)){
        num = fread(file_character, 1, 1, file);

        if(feof(file)){
            if(counter - prev_counter > 0){
                rows++;
            }
            break;
        }

        if(!num){ // fread failed
            perror("Fread error!");
            exit(-1);
        }

        if(file_character[0] == character){
            counter++;
        }

        if(file_character[0] == '\n' && counter - prev_counter > 0){
            prev_counter = counter;
            rows++;
        }
    }

    fclose(file);
    clockEnd = times(&tmsEnd);
    printf("Counter of character %c: %d\n", character, counter);
    printf("Counter of rows with this character %c: %d\n", character, rows);

    FILE* file_results = fopen("pomiar_zad_2a", "w+");

    save_times(file_results);

    fclose(file_results);


    free(inp);
    free(filename);
    return 0;
}

void save_times(FILE* file){
    fprintf(file, "Time results\n--------------------\n");
    fprintf(file, "real time: %f\n", time_in_seconds(clockStart,clockEnd));
    fprintf(file, "sys time: %f\n", time_in_seconds(tmsStart.tms_stime,tmsEnd.tms_stime));
    fprintf(file, "user time: %f\n\n", time_in_seconds(tmsStart.tms_utime,tmsEnd.tms_utime));
}

void scanf_error(){
    perror("Scanf error!");
    exit(-1);
}