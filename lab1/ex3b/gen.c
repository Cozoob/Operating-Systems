// Created by Marcin Kozub.
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* create_command(char* string, char* new_i);

int main(){

    int lines_amount = 50;
    char* string = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Etiam aliquet elit eget nulla cursus.";
    char new_i[1] = "0";

    for(int i = 1; i < 10; i++){
        new_i[0]++;

        char* command = create_command(string, &new_i[0]);
        for(int j = 0 ; j < lines_amount; j++){
            int s = system(command);
            if(s == -1){
                perror("Error occured!");
                exit(1);
            }
        }

        lines_amount *= 2;
    }
    return 0;
}

char* create_command(char* string, char* new_i){ // 0 < i < 10 to work properly...

    char* command = calloc(strlen(string) + 20, sizeof (char));
    char* str1 = "echo ";
    strcpy(command, str1);
    strcat(command, string);
    strcat(command,"  >>  file");
    strcat(command,  new_i);
    return command;
}