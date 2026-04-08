#define _GNU_SOURCE 1

#include <err.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/uio.h>

static void do_read (int fd, int io_flags)
{
    char buffer[4096];
    struct iovec iov;

    iov.iov_base = buffer;
    iov.iov_len = sizeof(buffer);

    while (1) {
        int r = preadv2 (fd, &iov, 1, -1, io_flags);
        if (r < 0)
            err(1, "failed in read");
        else if (r == 0)
            break;
    }
}

struct action {
    char *key;
    char *helpmsg;
    void (* run) (int, int);
    int open_flags;
    int io_flags;
} action [] = {
    {"read+cache",      "read (with cache)",       do_read,  O_RDONLY,          0},
    {"read+dontcache",  "read with RWF_DONTCACHE", do_read,  O_RDONLY,          RWF_DONTCACHE},
    {"read+direct",     "read directly",           do_read,  O_RDONLY|O_DIRECT, 0},
    {NULL}
};

static void print_usage(char *prog, int status, FILE *fp)
{
    fprintf(fp, "Usage:\n");
    fprintf(fp, "  %s ACTION FILENAME\n", prog);
    fprintf(fp, "  %s -|--help\n", prog);
    fprintf(fp, "\n");
    fprintf(fp, "Actions:\n");
    for (size_t i = 0; action[i].key; i++)
        fprintf(fp, "  %s: %s\n", action[i].key, action[i], action[i].helpmsg);

    exit (status);
}

int main(int argc, char ** argv)
{
    void (* run) (int) = NULL;

    if (argc == 2
        && (strcmp(argv[1], "--help") == 0
            || strcmp(argv[1], "-h") == 0))
        print_usage (argv[0], 0, stdout);

    if (argc != 3)
        print_usage (argv[0], 1, stderr);

    struct action *a = NULL;
    for (size_t i = 0; action[i].key; i++) {
        if (strcmp(argv[1], action[i].key) == 0) {
            a = action + i;
            break;
        }
    }
    if (a == NULL)
        print_usage (argv[0], 1, stderr);

    int fd = open (argv[2], a->open_flags);
    if (fd < 0)
        err(1, "failed in open %s", argv[2]);

    a->run (fd, a->io_flags);

    return 0;
}
