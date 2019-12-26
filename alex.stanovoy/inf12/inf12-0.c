#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char expr[4096] = {};
    fgets(expr, sizeof(expr), stdin);
    char* end_pos = strchr(expr, '\n');
    if (end_pos) {
        *end_pos = '\0';
    }
    if (strlen(expr) == 0) {
        return 0;
    }
    char code[4096] = {};
    snprintf(code, sizeof(code), "val=%s;print(val)", expr);
    execlp("python3", "python3", "-c", code, NULL);
}
