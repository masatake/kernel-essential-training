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

static void do_write (int fd, int io_flags)
{
    char buffer[4096];
    struct iovec iov;

    iov.iov_base = buffer;
    iov.iov_len = sizeof(buffer);

    for (int i = 0; i < 1024 * 1024 * 1024 / sizeof(buffer); i++) {
        int r = pwritev2 (fd, &iov, 1, -1, io_flags);
        if (r < 0)
            err(1, "failed in write");
        else if (r != sizeof(buffer))
            errx(1, "failed in write");
    }
}

struct action {
    char *key;
    char *helpmsg;
    void (* run) (int, int);
    int open_flags;
    int io_flags;
} action [] = {
    {"read+cache",       "read (with cache)",
     do_read,  O_RDONLY,                         0},
    {"read+dontcache",   "read with RWF_DONTCACHE",
     do_read,  O_RDONLY,                         RWF_DONTCACHE},
    {"read+direct",      "read directly",
     do_read,  O_RDONLY|O_DIRECT,                0},
    {"create+cache",     "create a file with 1G data (to cache)",
     do_write, O_WRONLY|O_CREAT|O_EXCL,          0},
    {"create+dontcache", "create a file with 1G data (RWF_DONTCACHE)",
     do_write,  O_WRONLY|O_CREAT|O_EXCL,         RWF_DONTCACHE},
    {"create+diect",     "create a file with 1G data (directly)",
     do_write, O_WRONLY|O_CREAT|O_EXCL|O_DIRECT, 0},
    {"write+cache",      "write 1G data to the exiting file (to cache)",
     do_write, O_WRONLY,                         0},
    {"write+dontcache",  "write 1G data to the exiting file with RWF_DONTCACHE",
     do_write, O_WRONLY,                         RWF_DONTCACHE},
    {"write+direct",     "write 1G data to the exiting file directly",
     do_write, O_WRONLY|O_DIRECT,                0},
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

    mode_t mode = (a->open_flags & O_CREAT) ? (S_IRUSR|S_IWUSR) : 0;
    int fd = open (argv[2], a->open_flags, mode);
    if (fd < 0)
        err(1, "failed in open %s", argv[2]);

    a->run (fd, a->io_flags);

    return 0;
}
