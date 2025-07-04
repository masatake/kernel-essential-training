#include <stdio.h>
#include <err.h>
#include <unistd.h>
#include <fcntl.h>
#include "prompt.h"

int
main(void)
{

    fprintf(stderr, "PID: %d\n", getpid());
    prompt("open");

    int fd = open("./TMP", O_RDWR|O_CREAT|O_TRUNC, 0666);

    if (fd < 0)
        err(1, "failed in open (\"./TMP\",...)");

    prompt("write");
    const char *data = "abcdefghijklmnopqrstuvwxyz";
    for (const char *c = data; *c != '\0'; c++)
        write(fd, c, 1);

    prompt("lseek");
    lseek(fd, 0, SEEK_SET);

    prompt("read");
    char d;
    while (1) {
        if (read (fd, &d, 1) != 1)
            break;
    }

    prompt("close");
    close(fd);

    return 0;
}
