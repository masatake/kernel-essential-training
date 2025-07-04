#include <stdio.h>
#include <err.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "prompt.h"

#define DATA "012"

int
main(void)
{

    fprintf(stderr, "PID: %d\n", getpid());
    prompt("open");

    int fd = open("./TMP", O_WRONLY, 0666);

    if (fd < 0)
        err(1, "failed in open (\"./TMP\",...)");

    prompt("stat");
    struct stat sb;
    if (fstat (fd, &sb) < 0)
        err(1, "failed in fstat");
    if (sb.st_size == 0)
        errx(1, "the file %s is still empty", "./TMP");

    char *a = mmap(NULL, sb.st_size, PROT_WRITE, MAP_SHARED,
                   fd, 0);
    if (a == MAP_FAILED)
        err(1, "failed in mmap");

    fprintf(stderr, "map: %p\n", a);

    while (1) {
        prompt("write " DATA);
        const char *const data = DATA;

        a[0] = data[0];
        a[1] = data[1];
        a[2] = data[2];
    }

    return 0;
}
