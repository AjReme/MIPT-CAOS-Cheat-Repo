#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

volatile sig_atomic_t cnt = 0;

int itoa(int val, char* buff)
{
    memset(buff, '\0', strlen(buff));
    if (val == 0) {
        buff[0] = '0';
        return 1;
    }
    int sign = 0;
    if (val < 0) {
        sign = 1;
        val *= -1;
    }
    int i = 0;
    for (; val != 0; ++i, val /= 10) {
        buff[i] = val % 10 + '0';
    }
    if (sign) {
        buff[i++] = '-';
    }
    int n = i;
    for (i = 0; i < n - i - 1; ++i) {
        char tmp = buff[i];
        buff[i] = buff[n - i - 1];
        buff[n - i - 1] = tmp;
    }
    return n;
}

void write_cnt()
{
    char str[12];
    int i = 0;
    int n = itoa(cnt, str);
    str[n++] = '\n';
    while (i < n) {
        i += write(STDOUT_FILENO, str + i, n);
    }
}

void handler_sigusr1(int signum)
{
    ++cnt;
    write_cnt();
    fflush(stdout);
}

void handler_sigusr2(int signum)
{
    cnt *= -1;
    write_cnt();
    fflush(stdout);
}

void handler_sigterm(int signum)
{
    exit(0);
}

int main()
{
    struct sigaction act;
    act.sa_handler = handler_sigusr1;
    sigaction(SIGUSR1, &act, NULL);
    act.sa_handler = handler_sigusr2;
    sigaction(SIGUSR2, &act, NULL);
    act.sa_handler = handler_sigterm;
    sigaction(SIGTERM, &act, NULL);

    printf("%d\n", getpid());
    fflush(stdout);
    scanf("%d", &cnt);

    while (1) {
        pause();
    }
}
