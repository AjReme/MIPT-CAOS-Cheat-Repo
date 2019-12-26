#include <stdio.h>
#include <inttypes.h>

int char_to_num(char x)
{
    if ('0' <= x && x <= '9') {
        return x - '0';
    } else if ('A' <= x && x <= 'Z') {
        return x - 'A' + 10;
    } else {
        return x - 'a' + 36;
    }
}

char num_to_char(int x)
{
    if (0 <= x && x <= 9) {
        return x + '0';
    } else if (10 <= x && x <= 35) {
        return x + 'A' - 10;
    } else {
        return x + 'a' - 36;
    }
}

int main()
{
    uint64_t res = 0, read = 0;
    char ch;
    while (scanf("%c", &ch) != EOF) {
        switch (ch) {
            case '&': {
                res &= read;
                read = 0;
                break;
            }
            case '|': {
                res |= read;
                read = 0;
                break;
            }
            case '^': {
                res ^= read;
                read = 0;
                break;
            }
            case '~': {
                res = ~res;
                break;
            }
            default: {
                read |= 1ull << char_to_num(ch);
                break;
            }
        }
    }
    for (int i = 0; i < 62; ++i) {
        if (((res >> i) & 1) == 1) {
            printf("%c", num_to_char(i));
        }
    }
}
