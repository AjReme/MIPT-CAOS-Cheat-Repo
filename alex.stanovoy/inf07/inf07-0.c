#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int write_buff(int fd, void* buff, int max_write)
{
    if (max_write <= 0) {
        return 0;
    }
    int total = 0;
    while (total < max_write) {
        int current =
            write(fd, (void*)(total + (char*)buff), max_write - total);
        if (current < 0) {
            return -1;
        }
        if (current == 0) {
            return total;
        }
        total += current;
    }
    return total;
}

int read_buff(int fd, void* buff, int max_read)
{
    if (max_read <= 0) {
        return 0;
    }
    int total = 0;
    while (total < max_read) {
        int current = read(fd, (void*)(total + (char*)buff), max_read - total);
        if (current < 0) {
            return -1;
        }
        if (current == 0) {
            return total;
        }
        total += current;
    }
    return total;
}

int main(int argc, char** argv)
{
    int exit_code = 0;
    int fd_in = open(argv[1], O_RDONLY);
    int fd_out1 = open(argv[2], O_RDWR | O_CREAT, 0640);
    int fd_out2 = open(argv[3], O_RDWR | O_CREAT, 0640);

    const int nbytes = 4096;
    char in_buff[nbytes];
    char out_buff1[nbytes];
    char out_buff2[nbytes];

    if (fd_in < 0) {
        exit_code = 1;
        goto finalize;
    }

    if (fd_out1 < 0 || fd_out2 < 0) {
        exit_code = 2;
        goto finalize;
    }

    while (1) {
        int readed = read_buff(fd_in, &in_buff, nbytes);
        if (readed < 0) {
            exit_code = 3;
            goto finalize;
        }
        if (readed == 0) {
            goto finalize;
        }
        int out_ptr1 = 0;
        int out_ptr2 = 0;
        for (int i = 0; i < readed; ++i) {
            if (isdigit(in_buff[i])) {
                out_buff1[out_ptr1++] = in_buff[i];
            } else {
                out_buff2[out_ptr2++] = in_buff[i];
            }
        }
        if (write_buff(fd_out1, &out_buff1, out_ptr1) < 0) {
            exit_code = 3;
            goto finalize;
        }
        if (write_buff(fd_out2, &out_buff2, out_ptr2) < 0) {
            exit_code = 3;
            goto finalize;
        }
    }

finalize:

    close(fd_in);
    close(fd_out1);
    close(fd_out2);
    return exit_code;
}
