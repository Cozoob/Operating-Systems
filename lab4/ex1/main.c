#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include "parser.h"

const int SIGNAL_ID = SIGUSR1;

void handle_signal(int signal_type){
    printf("Received signal %d \n", signal_type);
}

void check_signal_pending();

void mask_signal();

int main(int argc, char* argv[]) {

    if(argc != 2){
        perror("Use one of them: ignore/handler/mask/pending\n");
        exit(1);
    }

    const enum Option option = parse_option(argv[1]);

    switch (option) {
        case IGNORE:
            signal(SIGNAL_ID, SIG_IGN);
            break;
        case HANDLER:
            signal(SIGNAL_ID, handle_signal);
            break;
        case PENDING:
        case MASK:
            mask_signal();
            break;
        default:
            // NOTHING
            break;
    }

    printf("Raising signal in main process.\n");
    raise(SIGNAL_ID);

    printf("Main process: \n");
    check_signal_pending();

    int pid = fork();
    if(pid == -1){
        perror("FAILED FORK!\n");
        exit(1);
    }

    if(pid == 0){
        if(option != PENDING){
            printf("Raising in child process. \n");
            raise(SIGNAL_ID);
        }

        printf("Child process: \n");
        check_signal_pending();

        if(execl("./child", "child", NULL) == -1){
            perror("Cannot run child.c!\n");
            exit(1);
        }
    }

    int status;
    while (wait(&status) > 0);

    return 0;
}

void check_signal_pending(){
    sigset_t pending_set;
    sigemptyset(&pending_set);

    if(sigismember(&pending_set, SIGNAL_ID)){
        printf("PENDING SIGNAL OF ID: %d\n", SIGNAL_ID);
    } else {
        printf("NOT PENDING SIGNAL OF ID: %d\n", SIGNAL_ID);
    }
}

void mask_signal(){
    sigset_t blocked_set;
    sigemptyset(&blocked_set);
    sigaddset(&blocked_set, SIGNAL_ID);
    sigprocmask(SIG_BLOCK, &blocked_set, NULL);
}