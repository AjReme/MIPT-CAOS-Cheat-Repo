#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signum, siginfo_t* info, void* ucontext)
{
    siginfo_t tmp = *info;
    if (tmp.si_value.sival_int == 0) {
        exit(0);
    }
    --tmp.si_value.sival_int;
    sigqueue(tmp.si_pid, tmp.si_signo, tmp.si_value);
}

int main(int argc, char** argv)
{
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGRTMIN);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    struct sigaction act = {};
    act.sa_sigaction = handler;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGRTMIN, &act, NULL);

    while (1) {
        pause();
    }
}
