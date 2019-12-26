#include <stdio.h>
#include <sys/stat.h>

int main()
{
    off_t ans = 0;
    char name[5000];
    while (fgets(name, 5000, stdin)) {
        struct stat fl;
        for (int i = 0; name[i] != 0; ++i) {
            if (name[i] == '\n') {
                name[i] = '\0';
                break;
            }
        }
        if (lstat(name, &fl) == 0 && S_ISREG(fl.st_mode)) {
            ans += fl.st_size;
        }
    }
    printf("%llu\n", ans);
}
