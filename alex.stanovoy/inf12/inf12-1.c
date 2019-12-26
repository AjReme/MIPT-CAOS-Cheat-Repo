#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
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
    snprintf(
        code,
        sizeof(code),
        "#include <stdio.h>\n"
        "int main() {\n"
        "    int res=(%s);\n"
        "    printf(\"%%d\\n\",res);\n"
        "}\n",
        expr);
    pid_t pid = fork();
    if (pid == 0) {
        int fd = open("a.c", O_RDWR | O_CREAT | O_CLOEXEC, 0640);
        ftruncate(fd, strlen(code));
        char* contents =
            mmap(NULL, strlen(code), PROT_WRITE, MAP_SHARED, fd, 0);
        strcpy(contents, code);
        munmap(contents, strlen(code));
        execlp("gcc", "gcc", "a.c", NULL);
    } else {
        int status;
        waitpid(pid, &status, 0);
        pid = fork();
        if (pid == 0) {
            execlp("./a.out", "a", NULL);
        }
        waitpid(pid, &status, 0);
        remove("a");
        remove("a.c");
    }
}
