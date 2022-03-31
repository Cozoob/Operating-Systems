#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

#define MAX_CALLS 3
int CALL_IDX = 0;
int CALL_DEPTH = 0;

void signal_info_handler(int sig, siginfo_t* info, void* ucontext);

void signal_data_info_handler(int sig, siginfo_t* info, void* ucontext);

void signal_child_info_handler(int sig, siginfo_t* info, void* ucontext);

void signal_handler(int sig, siginfo_t* info, void* ucontext);

void setup_sigaction(int signalidx, int flags, void (*action)(int, siginfo_t*, void*));

int main() {
    printf("\n-- Testing SA_SIGINFO --\n");
    setup_sigaction(SIGUSR1, SA_SIGINFO, signal_info_handler);
    setup_sigaction(SIGUSR2, SA_SIGINFO, signal_data_info_handler);
    setup_sigaction(SIGCHLD, SA_SIGINFO, signal_child_info_handler);

    raise(SIGUSR1);

    sigval_t signal_value = { 15 };
    sigqueue(getpid(), SIGUSR2, signal_value);

    pid_t pid = fork();
    if (pid == 0){
        printf("(Hello from child process.)\n");
        exit(1);
    }
    else
    {
        printf("(Created child process with pid: %d)\n", pid);
    }

    int status = 0;
    while (wait(&status) > 0);

    printf("\n-- Testing SA_NODEFER --\n");
    setup_sigaction(SIGUSR1, SA_NODEFER, signal_handler);

    raise(SIGUSR1);

    printf("\n-- Testing SA_RESETHAND --\n");
    setup_sigaction(SIGUSR1, SA_RESETHAND, signal_handler);

    raise(SIGUSR1);

    raise(SIGUSR1);
    return 0;
}

void signal_info_handler(int sig, siginfo_t* info, void* ucontext){
    printf("Signal info: \n");
    printf("- Signal number: %d\n", info->si_signo);
    printf("- The signal has been sent by process %d\n", info->si_pid);
    printf("- Real user ID of sending process %d\n", info->si_uid);
}

void signal_data_info_handler(int sig, siginfo_t* info, void* ucontext){
    printf("Signal info: \n");
    printf("- Signal number: %d\n", info->si_signo);
    printf("- Custom integer data sent %d\n", info->si_value.sival_int);
}

void signal_child_info_handler(int sig, siginfo_t* info, void* ucontext){
    printf("Signal info: \n");
    printf("- Signal number: %d\n", info->si_signo);
    printf("- Child pid: %d\n", info->si_pid);
    printf("- Child exit status: %d\n", info->si_status);
}

void signal_handler(int sig, siginfo_t* info, void* ucontext){
    int current_idx = CALL_IDX;
    printf("start IDX=%d, DEPTH=%d\n", current_idx, CALL_DEPTH);
    CALL_IDX++;

    CALL_DEPTH++;
    if (CALL_IDX < MAX_CALLS)
    {
        raise(SIGUSR1);
    }
    CALL_DEPTH--;

    printf("end  IDX=%d, DEPTH=%d\n", current_idx, CALL_DEPTH);
}

void setup_sigaction(int signalidx, int flags, void (*action)(int, siginfo_t*, void*)){
    static struct sigaction act;
    act.sa_sigaction = action;
    act.sa_flags = flags;
    sigemptyset(&act.sa_mask);

    CALL_IDX = 0;
    sigaction(signalidx, &act, NULL);
}
