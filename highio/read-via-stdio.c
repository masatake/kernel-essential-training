#include <stdio.h>
#include <err.h>
#include <unistd.h>
#include "prompt.h"

int
main(void)
{

    fprintf(stderr, "PID: %d\n", getpid());
    prompt("fopen");

    FILE *fp = fopen ("./TMP", "r");
    if (!fp)
        err(1, "failed in fopen (\"./TMP\",...)");

    while (1) {
        prompt("fgetc");
        char d[3];

        d[0] = fgetc (fp);
        if (EOF == d[0])
            errx(1, "EOF");
        d[1] = fgetc (fp);
        if (EOF == d[1])
            errx(1, "EOF");
        d[2] = fgetc (fp);
        if (EOF == d[2])
            errx(1, "EOF");
        fprintf(stderr, "%c%c%c\n", d[0], d[1], d[2]);

        prompt("rewind");
        rewind(fp);
    }

    return 0;
}
