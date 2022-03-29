#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <stdbool.h>


void write_error();

struct tms tmsStart, tmsEnd;
clock_t clockStart, clockEnd;

void start_timer();

void end_timer(const char* action);

void write_line_to_report(FILE* fs, const char* action, const char* system, const char* user, const char* real);

char* report_filename = "report.txt";
FILE* report_file;

void count(double in_start, double in_end, double step, char* number);

double fun(double x){
    return 4 / (1 + x * x);
}

double min(double x, double y);

int main(int argc, char* argv[]) {

    if(argc < 3){
        write_error();
    }

    int add_header = 0;

    if(access(report_filename, F_OK) != 0){
        add_header = 1;
    }

    report_file = fopen(report_filename, "a+");

    if(report_file == NULL){
        write_error();
    }

    if(add_header){
        write_line_to_report(report_file, "OPTIONS", "SYSTEM [s]", "USER [s]", "REAL [s]");
    }

    char* action = calloc(strlen(argv[1]) + strlen(argv[2]) + 3, sizeof (char));
    if (action == NULL){
        write_error();
    }

    snprintf(action, strlen(argv[1]) + strlen(argv[2]) + 2, "%s %s", argv[1], argv[2]);

    start_timer();

    unsigned int amount = strtol(argv[2], NULL, 10);


    double start = 0, in_start = 0;
    double end, in_end = 1;

    double step = (in_end - in_start) / (double) amount;
    end = step;

    pid_t pid;
    for(int i = 1; i <= amount; i++){
        pid = vfork();
        if(pid == 0){
            char* number = calloc(10000, sizeof (char));
            sprintf(number, "%d", i);
            count(start, end, step,number);
        }
        start += step;
        end += step;
    }

    int status;
    while(wait(&status) > 0);

    char* file_name = calloc(strlen(argv[2]) + 7, sizeof (char));
    char* value = calloc(51, sizeof(char));
    double sum = 0;

    FILE* file;
    for(int i = 0; i < amount; i++){
        snprintf(file_name, strlen(argv[2]) + 6, "w%d.txt", i + 1);

        file = fopen(file_name, "r");

        if(file == NULL){
            write_error();
        }

        fread(value, sizeof (char), 50, file);

        sum += strtod(value, NULL);
        fclose(file);
    }

    printf("%f\n", sum);
    end_timer(action);
    return 0;
}

double min(double x, double y){
    if (x > y){
        return y;
    }
    return x;
}

void count(double in_start, double in_end, double step, char* number){

    double start = in_start;
    double end;

    double sum = 0;
    double mid;

    while(start < in_end){

        end = min(start + step, in_end);
        mid = (start + end)/2;
        sum += fun(mid) * (end - start);

        start += step;
    }

    char* filename = calloc(strlen(number)+6,sizeof(char));
    strcpy(filename, "w");
    strcat(filename, number);
    strcat(filename, ".txt");


    char value[51];
    snprintf(value, 50, "%f", sum);

    FILE* file = fopen(filename, "w");
    fwrite(value, sizeof(char), strlen(value), file);

    free(filename);
    fclose(file);

    exit(0);
}

void write_error(){
    perror("There is an error!");
    exit(-1);
}

void write_line_to_report(FILE* fs, const char* action, const char* system, const char* user, const char* real){
    fprintf(fs, "%-30s   %10s   %10s   %10s\n", action, system, user, real);
    fprintf(stdout, "%-30s   %10s   %10s   %10s\n", action, system, user, real);
}

void start_timer(){
    clockStart = times(&tmsStart);
}

void end_timer(const char* action){
    clockEnd = times(&tmsEnd);

    long clkTics = sysconf(_SC_CLK_TCK);
    long double systemTime = (long double)(tmsEnd.tms_stime - tmsStart.tms_stime)/clkTics;
    long double userTime = (long double)(tmsEnd.tms_utime - tmsStart.tms_utime)/clkTics;
    long double realTime = (long double)(clockEnd - clockStart)/clkTics;

    char* sys = calloc(16, sizeof(char));
    char* usr = calloc(16, sizeof(char));
    char* rel = calloc(16, sizeof(char));

    snprintf(sys, 15, "%Lf", systemTime);
    snprintf(usr, 15, "%Lf", userTime);
    snprintf(rel, 15, "%Lf", realTime);

    write_line_to_report(report_file, action, sys, usr, rel);

    free(sys);
    free(usr);
    free(rel);
}