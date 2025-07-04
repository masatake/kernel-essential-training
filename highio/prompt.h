#ifndef PROMPT_H
#define PROMPT_H
extern void exit(int);
extern int getpid(void);

static void
prompt(const char *msg)
{
    fprintf(stderr, "(pid: %d) press return for next step \"%s\": ", getpid(), msg);
    int c = getchar();
    if (c == 'q')
        exit(0);
}


static int
y_or_n(const char *msg)
{
 retry:
    fprintf(stderr, "%s (y or n): ", msg);
    int c = getchar();

    if (c == 'y') {
        getchar();
        return 1;
    }

    if (c == 'n') {
        getchar();
        return 0;
    }

    if (c != '\n')
        getchar();

    goto retry;
}


#endif
