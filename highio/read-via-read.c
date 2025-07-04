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

    int fd = open("./TMP", O_RDONLY, 0666);

    if (fd < 0)
        err(1, "failed in open (\"./TMP\",...)");

    while (1) {
        prompt("read");
        char d[3];

        if (read (fd, &(d[0]), 1) != 1)
            break;
        if (read (fd, &(d[1]), 1) != 1)
            break;
        if (read (fd, &(d[2]), 1) != 1)
            break;
        fprintf(stderr, "%c%c%c\n", d[0], d[1], d[2]);

        prompt("lseek");
        lseek(fd, 0, SEEK_SET);
    }


    return 0;
}
