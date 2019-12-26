#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int get_size(int fd)
{
    struct stat fl;
    fstat(fd, &fl);
    return (int)fl.st_size;
}

int main(int argc, char** argv)
{
    int fd = open(argv[1], O_RDONLY);
    int fl_size = get_size(fd);
    int str_size = strlen(argv[2]);
    char* fl = (char*)mmap(NULL, fl_size, PROT_READ, MAP_PRIVATE, fd, 0);

    for (int i = 0, lim = fl_size + 1 - str_size; i < lim; ++i) {
        if (memcmp(fl + i, argv[2], str_size) == 0) {
            printf("%d ", i);
        }
    }

    munmap(fl, fl_size);
    close(fd);
}
