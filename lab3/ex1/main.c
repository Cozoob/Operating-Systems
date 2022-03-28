#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void write_error();

int main(int argc, char* argv[]) {

    if(argc != 2){
        write_error();
    }

    int number = atoi(argv[1]);

    pid_t pid;
    for(int i = 0; i < number; i++){
        pid = fork();
        if(pid == 0) {
            printf("%d: | CHILD PID: %d | PARENT PID: %d \n", i + 1, getpid(), getppid());
            exit(0);
        }
    }

    int status;
    while(wait(&status) > 0);

    return 0;
}

void write_error(){
    perror("There are incorrect arguments!");
    exit(-1);
}
