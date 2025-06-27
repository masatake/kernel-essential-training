#include <stdio.h>
#include <err.h>


static void f1(const char c)
{
    char *t = (char *)0x89;

    switch (c) {
    case 'r':
        fprintf(stderr, "%c\n", *t);
        break;

    case 'w':
        *t = 21;
        break;

    case 'x':
        void (* proc) (void) = (void (*)(void))t;
        proc();
        break;
    }
}

static void f0(const char c)
{
    f1(c);
}

static void trigger_segv (const char c)
{
    f0(c);
}

int
main(void)
{
    char buf[BUFSIZ] = {0};
    fputs("r/w/x: ", stderr);

    if (fgets (buf, sizeof(buf), stdin) == NULL) {
        if (feof(stdin))
            return 0;
        err(1, "failed in fgets");
    }

    switch (buf[0]) {
    case 'r':
    case 'w':
    case 'x':
        trigger_segv (buf[0]);
    default:
        fprintf(stderr, "unexpected input: %c\n", buf[0]);
        return 1;
    }

    return 0;
}
