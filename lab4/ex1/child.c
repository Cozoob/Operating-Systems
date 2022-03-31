#include <signal.h>
#include <stdio.h>

const int SIGNAL_ID = SIGUSR1;

void check_signal_pending();

int main(int argc, char* argv[]){
    check_signal_pending();
    raise(SIGNAL_ID);
    return 0;
}

void check_signal_pending(){
    sigset_t pending_set;
    sigemptyset(&pending_set);

    if(sigismember(&pending_set, SIGNAL_ID)){
        printf("AFTER EXEC, PENDING SIGNAL OF ID: %d\n", SIGNAL_ID);
    } else {
        printf("AFTER EXEC, NOT PENDING SIGNAL OF ID: %d\n", SIGNAL_ID);
    }
}