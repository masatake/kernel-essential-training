#include <stdio.h>
#include <err.h>
#include <unistd.h>
#include "prompt.h"

#define DATA "XYZ"

int
main(void)
{

    fprintf(stderr, "PID: %d\n", getpid());
    prompt("fopen");

    FILE *fp = fopen ("./TMP", "r+");
    if (!fp)
        err(1, "failed in fopen (\"./TMP\",...)");

    while (1) {
        prompt("fputc " DATA);
        const char *data = DATA;
        for (const char *c = data; *c != '\0'; c++)
            fputc (*c, fp);

        prompt("rewind");
        rewind(fp);
    }

    return 0;
}
