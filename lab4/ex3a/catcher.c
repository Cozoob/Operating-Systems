#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int signal_id, siginfo_t *siginfo, void *ucontext);

int COUNTER = 0;
int SIGNAL_ID;

int main() {
    pid_t pid = getpid();
    printf("CATCHER'S PID: %d\n", pid);
    printf("----------------------------\n");

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


    if(COUNTER > 0) {
        printf("CATCHER RECEIVED %d", COUNTER);
        if (SIGNAL_ID == SIGUSR1) {
            printf(" SIGUSR1 SIGNALS.\n");
        } else {
            printf(" SIGRTMIN SIGNALS.\n");
        }
        printf("----------------------------\n");
    }


    return 0;
}

void sig_handler(int signal_id, siginfo_t *siginfo, void *ucontext){
    if (ucontext){
        // do nothing.
    }
    pid_t pid_sender = siginfo->si_pid;
    if(signal_id == SIGUSR1 || signal_id == SIGRTMIN) {
        SIGNAL_ID = signal_id;
        COUNTER++;
    } else if(signal_id == SIGUSR2){

        int i = 0;
        if(siginfo->si_code == SI_QUEUE){
            // type = sigqueue
            while(i < COUNTER){
                union sigval sigval;
                sigval.sival_int = i;
                sigqueue(pid_sender, SIGUSR1, sigval);
                i++;
            }
            union sigval sigval;
            sigval.sival_int = COUNTER;
            sigqueue(pid_sender, SIGUSR2, sigval);
        } else{
            // type = kill
            while(i < COUNTER){
                kill(pid_sender, SIGUSR1);
                i++;
            }
            kill(pid_sender, SIGUSR2);
        }


    } else {
        // type = sigrt
        printf("CATCHER RECEIVED SIGRTMAX SIGNAL!\n");
        printf("----------------------------\n");

        int i = 0;
        while(i < COUNTER){
            kill(pid_sender, SIGRTMIN);
            i++;
        }
        kill(pid_sender, SIGRTMAX);
    }

}

