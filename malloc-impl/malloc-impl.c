#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <stdbool.h>

static bool
y_or_n(const char *msg)
{
    char buf[BUFSIZ];
    while (true) {
        fprintf(stderr, "%s", msg);

        buf[0] = '\0';
        if (fgets (buf, sizeof(buf), stdin) == NULL) {
            if (feof(stdin))
                return 0;
            err(1, "failed in fgets");
        }

        switch (buf[0]) {
        case 'y':
            return true;
        case 'n':
            return false;
        default:
            break;
        }
    }
}

int
main(void)
{
    pid_t pid = getpid();

    fprintf(stderr, "PID: %d\n", pid);

    while (true) {
        fprintf(stderr, "size(KiB): ");
        char buf[BUFSIZ];
        if (fgets (buf, sizeof(buf), stdin) == NULL) {
            if (feof(stdin))
                return 0;
            err(1, "failed in fgets");
        }

        errno = 0;
        size_t size = strtoul (buf, NULL, 0);
        if (errno)
            err(1, "failed in strtoul");

        fprintf(stderr, "malloc(%lu) => ", size);
        void *p = malloc (size * 1024);
        fprintf(stderr, "%p\n", p);
        if (!p)
            err(1, "failed in malloc");

        if (y_or_n("free [y/n]: ")) {
            fprintf(stderr, "free(%p\n", p);
            free (p);
        }
    }
    return 0;
}
