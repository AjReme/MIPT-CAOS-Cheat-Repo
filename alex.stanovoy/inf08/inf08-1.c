#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

struct Item {
    int value;
    uint32_t next_pointer;
};

int get_size(int fd)
{
    struct stat fl;
    fstat(fd, &fl);
    return (int)fl.st_size;
}

struct Item get_next(int fd, off_t pos)
{
    off_t page = getpagesize();
    void* readed = mmap(
        NULL,
        sizeof(struct Item),
        PROT_READ,
        MAP_PRIVATE,
        fd,
        pos / page * page);
    struct Item ret = *(struct Item*)((char*)readed + pos % page);
    munmap(readed, sizeof(struct Item));
    return ret;
}

int main(int argc, char** argv)
{
    int fd = open(argv[1], O_RDONLY);
    if (get_size(fd) == 0) {
        return 0;
    }
    off_t pos = 0;
    while (1) {
        struct Item readed = get_next(fd, pos);
        printf("%d ", readed.value);
        if (readed.next_pointer == 0) {
            break;
        }
        pos = readed.next_pointer;
    }
    close(fd);
}
