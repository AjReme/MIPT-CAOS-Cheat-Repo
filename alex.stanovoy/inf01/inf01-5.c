#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x, ans1 = 0, ans2 = 0;
    const unsigned int ascii = 0b0;
    const unsigned int utf1 = 0b110;
    const unsigned int utf2 = 0b1110;
    const unsigned int utf3 = 0b11110;
    const unsigned int next_utf = 0b10;
    while ((x = getchar()) != EOF) {
        unsigned int ch = x;
        if ((ch >> 7) == ascii) {
            ++ans1;
        }
        else {
            unsigned int to_skip = 0;
            if ((ch >> 3) == utf3) {
                to_skip = 3;
            }
            else if ((ch >> 4) == utf2) {
                to_skip = 2;
            }
            else if ((ch >> 5) == utf1) {
                to_skip = 1;
            }
            else {
                printf("%d %d\n", ans1, ans2);
                fflush(stdout);
                exit(1);   
            }
            for (unsigned int i = 0; i < to_skip; ++i) {
                x = getchar();
                ch = x;
                if ((x == EOF) || ((ch >> 6) != next_utf)) {
                    printf("%d %d\n", ans1, ans2);
                    fflush(stdout);
                    exit(1);
                }
            }
            ++ans2;
        }
    }
    printf("%d %d\n", ans1, ans2);
    fflush(stdout);
}
