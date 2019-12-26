#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    for (int i = 1; i < argc; ++i) {
        int leading_byte = 2;
        int len = strlen(argv[i]);
        while (leading_byte < len && argv[i][leading_byte] == '0') {
            ++leading_byte;
        }
        if (leading_byte == len) {
            printf("1 ");
        } else {
            printf("%d ", (len - leading_byte) / 2 + (len - leading_byte) % 2);
        }
    }
}
