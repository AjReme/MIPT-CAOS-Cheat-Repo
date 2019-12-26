#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t signo;

void handler(int signum)
{
    signo = signum;
}

int main(int argc, char** argv)
{
    sigset_t mask;
    sigfillset(&mask);

    struct sigaction act;
    act.sa_handler = handler;
    for (int sig = SIGRTMIN; sig <= SIGRTMAX; ++sig) {
        sigaction(sig, &act, NULL);
        sigdelset(&mask, sig);
    }
    sigprocmask(SIG_SETMASK, &mask, NULL);

    FILE* files[SIGRTMAX - SIGRTMIN];
    for (int i = 1; i < argc; ++i) {
        files[i - 1] = fopen(argv[i], "r");
    }

    while (1) {
        pause();
        if (signo == SIGRTMIN) {
            break;
        } else {
            char buff[4096] = {};
            fgets(buff, sizeof(buff), files[signo - SIGRTMIN - 1]);
            fputs(buff, stdout);
            fputs("", stdout);
            fflush(stdout);
        }
    }

    for (int i = 0; i + 1 < argc; ++i) {
        fclose(files[i]);
    }
}
