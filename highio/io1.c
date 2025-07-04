#include <stdio.h>
#include <err.h>
#include <unistd.h>
#include "prompt.h"

int
main(void)
{

    fprintf(stderr, "PID: %d\n", getpid());
    prompt("fopen");

    FILE *fp = fopen ("./TMP", "w+");
    if (!fp)
        err(1, "failed in fopen (\"./TMP\",...)");

    prompt("fputc");
    const char *data = "abcdefghijklmnopqrstuvwxyz";
    for (const char *c = data; *c != '\0'; c++)
        fputc (*c, fp);

    prompt("rewind");
    rewind(fp);

    prompt("fgetc");
    volatile char d;
    while (EOF != (d = fgetc (fp)))
        ;

    prompt("fclose");
    fclose (fp);

    return 0;
}
