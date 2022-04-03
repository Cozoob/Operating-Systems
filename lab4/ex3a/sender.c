#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "typesig.h"
#include <ctype.h>
#include <signal.h>

enum TYPESIG parser(char* command);

void sig_handler(int signal_id, siginfo_t *siginfo, void *ucontext);

void print_error();

int COUNTER = 0;
unsigned int AMOUNT = 0;

int main(int argc, char* argv[]) {

    if (argc){
        // do nothing
    }

    enum TYPESIG signal_type = parser(argv[3]);

    unsigned int amount = strtol(argv[2], NULL, 10);
    AMOUNT = amount;

    pid_t pid_catcher = strtol(argv[1], NULL, 10);

    unsigned int i = 0;
    switch (signal_type) {
        case KILL:
            while(i < amount){
                kill(pid_catcher, SIGUSR1);
                i++;
            }
            kill(pid_catcher, SIGUSR2);
            break;
        case SIGRT:
            while(i < amount){
                kill(pid_catcher, SIGRTMIN);
                i++;
            }
            kill(pid_catcher, SIGRTMAX);
            break;
        case SIGQUEUE:
            while(i < amount){
                union sigval sigval;
                sigval.sival_int = i;
                sigqueue(pid_catcher, SIGUSR1, sigval);
                i++;
            }
            union sigval sigval;
            sigval.sival_int = amount;
            sigqueue(pid_catcher, SIGUSR2, sigval);
            break;
    }

    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGUSR1);
    sigdelset(&mask, SIGUSR2);
    sigdelset(&mask, SIGRTMAX);
    sigdelset(&mask, SIGRTMIN);
    sigprocmask(SIG_BLOCK, &mask, NULL);


    struct sigaction signal_action;

    signal_action.sa_sigaction = sig_handler;
    sigemptyset (&signal_action.sa_mask);
    signal_action.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &signal_action, NULL);
    sigaction(SIGUSR2, &signal_action, NULL);
    sigaction(SIGRTMIN, &signal_action, NULL);
    sigaction(SIGRTMAX, &signal_action, NULL);

    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR2);
    sigaddset(&sigset, SIGRTMAX);

    sigsuspend(&sigset);

    return 0;
}

void sig_handler(int signal_id, siginfo_t *siginfo, void *ucontext){
    if(ucontext){
        //do nothing
    }

    if(signal_id == SIGUSR1 || signal_id == SIGRTMIN) {
        COUNTER++;
    } else {
        printf("SENDER RECEIVED %d", COUNTER);
        if (signal_id == SIGUSR2) {
            printf(" SIGUSR1 SIGNALS.\n");
        } else {
            printf(" SIGRTMIN SIGNALS.\n");
        }
        printf("----------------------------\n");
        printf("SHOULD BE %d\n", AMOUNT);
        printf("----------------------------\n");
    }

    if(signal_id == SIGUSR2 && siginfo->si_code == SI_QUEUE){
        union sigval sigval = siginfo->si_value;
        printf("SENT SIGNALS FROM CATCHER %d\n", sigval.sival_int);
        printf("----------------------------\n");
    }

    if(signal_id == SIGUSR2 || signal_id == SIGRTMAX){
        exit(0);
    }
}

enum TYPESIG parser(char* command){
    char* new_command = calloc(strlen(command) + 1, sizeof (char));

    for(size_t i = 0; i < strlen(command); i++){
        new_command[i] = tolower(command[i]);
    }

    if(strcmp(new_command, "kill") == 0){
        free(new_command);
        return KILL;
    } else if(strcmp(new_command, "sigqueue") == 0){
        free(new_command);
        return SIGQUEUE;
    } else if (strcmp(new_command, "sigrt") == 0){
        free(new_command);
        return SIGRT;
    } else {
        free(new_command);
        print_error();
    }
    return SIGRT;
}

void print_error(){
    printf("Error: %d", errno);
    exit(1);
}