#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_ordered(char* mode);

void send_email(char* address, char* topic, char* content);

int main(int argc, char* argv[]) {
    if (argc != 2 && argc != 4){
        perror("There must be 2 or 4 arguments!");
        exit(1);
    }

    if(argc == 2){
        print_ordered(argv[1]);
    } else {
        send_email(argv[1], argv[2], argv[3]);
    }
}

void print_ordered(char* mode){
    printf("Printed emails ordered by: %s\n", mode);
    printf("--------------------------------\n");

    char* command;

    if(strcmp(mode, "date") == 0){
        command = "echo | mail -H";
    } else if (strcmp(mode, "sender") == 0){
        command = "echo | mail -H | sort -k 3";
    } else {
        printf("Wrong mode: %s\n", mode);
        exit(1);
    }

    FILE* file = popen(command, "r");

    if(file == NULL){
        perror("Pipe is not open!");
        exit(1);
    }

    char* line;
    size_t len = 0;

    while(getline(&line, &len, file) != -1){
        printf("%s", line);
    }
    free(line);
//    free(command);
}

void send_email(char* address, char* topic, char* content) {
    printf("SENDING EMAIL\n");

    char* command = malloc(sizeof address + sizeof topic + sizeof content + sizeof (char) * 30);

    sprintf(command, "echo %s | mail %s -s %s", content, address, topic);
    printf("%s\n", command);

    FILE* file = popen(command, "r");

    if(file == NULL){
        perror("Pipe is not open!");
        exit(1);
    }
    free(command);
}
