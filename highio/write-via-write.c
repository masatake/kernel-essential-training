#include <stdio.h>
#include <err.h>
#include <unistd.h>
#include <fcntl.h>
#include "prompt.h"

#define DATA "ABC"
int
main(void)
{

    fprintf(stderr, "PID: %d\n", getpid());
    prompt("open");

    int fd = open("./TMP", O_WRONLY, 0666);

    if (fd < 0)
        err(1, "failed in open (\"./TMP\",...)");

    while (1) {
        prompt("write " DATA);
        const char *data = DATA;
        for (const char *c = data; *c != '\0'; c++)
            if (write(fd, c, 1) != 1)
                err(1, "failed in write");

        prompt("lseek");
        if (lseek(fd, 0, SEEK_SET) < 0)
            err(1, "failed in lseek");
    }

    return 0;
}
