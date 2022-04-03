#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int signal_id, siginfo_t *siginfo, void *ucontext);

int COUNTER = 0;
int SIGNAL_ID;
sigset_t SIGSET;

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


    sigemptyset(&SIGSET);
    while(!sigismember(&SIGSET, SIGUSR2) || !sigismember(&SIGSET, SIGRTMAX)){
        sigaction(SIGUSR1, &signal_action, NULL);
        sigaction(SIGRTMIN, &signal_action, NULL);
        if(sigismember(&SIGSET, SIGUSR2) || sigismember(&SIGSET, SIGRTMAX)){
            break;
        }
        sigaction(SIGUSR2, &signal_action, NULL);
        sigaction(SIGRTMAX, &signal_action, NULL);
    }

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
    if(signal_id == SIGUSR1 && siginfo->si_code != SI_QUEUE) {
        SIGNAL_ID = signal_id;
        COUNTER++;
        kill(pid_sender, SIGUSR1);
    } else if(signal_id == SIGUSR2 && siginfo->si_code != SI_QUEUE){
        sigaddset(&SIGSET, SIGUSR2);
        kill(pid_sender, SIGUSR2);
    } else if(siginfo->si_code == SI_QUEUE && signal_id == SIGUSR1){
        SIGNAL_ID = signal_id;
        COUNTER++;
        union sigval sigval;
        sigval.sival_int = COUNTER;
        sigqueue(pid_sender, SIGUSR1, sigval);
        // type = sigqueue
    } else if(siginfo->si_code == SI_QUEUE && signal_id == SIGUSR2){
        union sigval sigval;
        sigval.sival_int = COUNTER;
        sigqueue(pid_sender, SIGUSR2, sigval);
        sigaddset(&SIGSET, SIGUSR2);
    } else if (signal_id == SIGRTMIN){
        SIGNAL_ID = signal_id;
        COUNTER++;
        kill(pid_sender, SIGRTMIN);
    } else if(signal_id == SIGRTMAX){
        // type = sigrt
        printf("CATCHER RECEIVED SIGRTMAX SIGNAL!\n");
        printf("----------------------------\n");
        kill(pid_sender, SIGRTMAX);
        sigaddset(&SIGSET, SIGRTMAX);
    }

}

