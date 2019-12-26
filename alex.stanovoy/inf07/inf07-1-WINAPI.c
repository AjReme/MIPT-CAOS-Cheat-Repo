#include <stdint.h>
#include <stdio.h>
#include <windows.h>

struct Item {
    int value;
    uint32_t next_pointer;
};

int main(int argc, char** argv)
{
    HANDLE fl = CreateFile(argv[1],
                           GENERIC_READ,
                           0,
                           NULL,
                           OPEN_ALWAYS,
                           FILE_ATTRIBUTE_NORMAL,
                           NULL);
    while (1) {
        struct Item readed;
        DWORD cnt;
        BOOL succ = ReadFile(fl, &readed, sizeof(readed), &cnt, NULL);
        if (!succ || cnt != sizeof(readed)) {
            break;
        }
        printf("%d ", readed.value);
        if (readed.next_pointer == 0) {
            break;
        }
        LARGE_INTEGER ptr;
        ptr.QuadPart = readed.next_pointer;
        SetFilePointerEx(fl, ptr, NULL, FILE_BEGIN);
    }
    CloseHandle(fl);
}
