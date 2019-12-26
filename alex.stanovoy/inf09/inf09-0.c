#include <stdio.h>
#include <unistd.h>

int main()
{
    int cnt = 1;
    do {
        int id = fork();
        if (id < 0) {
            break;
        } else if (id > 0) {
            ++cnt;
        } else {
            return 0;
        }
    } while (1);
    printf("%d\n", cnt);
}
