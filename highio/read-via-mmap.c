#include <stdio.h>
#include <err.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "prompt.h"

int
main(void)
{

    fprintf(stderr, "PID: %d\n", getpid());
    prompt("fopen");

    int fd = open("./TMP", O_RDONLY, 0666);

    if (fd < 0)
        err(1, "failed in open (\"./TMP\",...)");

    prompt("stat");
    struct stat sb;
    if (fstat (fd, &sb) < 0)
        err(1, "failed in fstat");
    if (sb.st_size == 0)
        errx(1, "the file %s is still empty", "./TMP");

    char *a = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED,
                   fd, 0);
    if (a == MAP_FAILED)
        err(1, "failed in mmap");

    fprintf(stderr, "map: %p\n", a);

    while (1) {
        prompt("read");
        fprintf(stderr, "%c%c%c\n", a[0], a[1], a[2]);
    }

    return 0;
}
