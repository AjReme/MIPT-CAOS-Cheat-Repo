#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    double x;
    scanf("%lf", &x);
    char y[20];
    char* ptr;
    scanf("%s", y);
    printf("%.03lf\n", x + (double)strtoll(y, &ptr, 16) + (double)strtoll(argv[1], &ptr, 27));
}
