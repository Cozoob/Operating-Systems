#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <wait.h>
#include <string.h>



void print_error();

void print_instructions();


int main(int argc, char* argv[]) {

    if(argc != 3){
        printf("There is invalid number of arguments!\n");
        print_instructions();
        exit(1);
    }

    pid_t pid_catcher = vfork();

    if(pid_catcher == 0) {
        int catcher = execl("./catcher", "catcher", NULL);

        if (catcher == -1) {
            print_error();
        }

        exit(0);
    }

    pid_t pid_sender = vfork();

    if(pid_sender == 0) {
        char** new_argv = calloc(4, sizeof (char*));
        new_argv[0] = "./sender";

        char pid_catcher_str[50];
        sprintf(pid_catcher_str, "%d", pid_catcher);
        new_argv[1] = pid_catcher_str;

        new_argv[2] = argv[1];
        new_argv[3] = argv[2];

        int sender = execv("./sender", new_argv);

        if (sender == -1) {
            print_error();
        }
        free(new_argv);
        exit(0);
    }


    int status;
    while(wait(&status) > 0);

    return 0;
}

void print_instructions(){
    printf("Use command: ./main <number of signals> <KILL/SIGSQUEUE/SIGRT>\n");
}

void print_error(){
    printf("Error: %d", errno);
    exit(1);
}
