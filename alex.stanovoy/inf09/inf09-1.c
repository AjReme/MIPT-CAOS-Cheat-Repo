#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int cnt = 0;
    int N = atoi(argv[1]);
    for (int i = 1; i <= N; ++i) {
        if (i == N) {
            printf("%d\n", i);
            fflush(stdout);
            return 0;
        } else {
            printf("%d ", i);
            fflush(stdout);
            int id = fork();
            if (id > 0) {
                int status;
                waitpid(id, &status, 0);
                return 0;
            }
        }
    }
}
