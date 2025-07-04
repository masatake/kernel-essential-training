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
        if (write(fd, c, 1) != 1)
            err(1, "failed in write");

    close(fd);

    return 0;
}
