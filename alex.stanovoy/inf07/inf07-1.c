#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

struct Item {
    int value;
    uint32_t next_pointer;
};

int main(int argc, char** argv)
{
    int fd_in = open(argv[1], O_RDONLY);
    while (1) {
        struct Item readed;
        int cnt = read(fd_in, &readed, sizeof(readed));
        if (cnt <= 0) {
            break;
        }
        printf("%d ", readed.value);
        if (readed.next_pointer == 0) {
            break;
        }
        lseek(fd_in, readed.next_pointer, SEEK_SET);
    }
    close(fd_in);
}
