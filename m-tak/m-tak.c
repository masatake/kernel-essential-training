/* Run tak(x, y, z) in multiple threads for generating CPU loads */
#define _GNU_SOURCE

#include <err.h>
#include <errno.h>
#include <getopt.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define X 0
#define Y 1
#define Z 2

static int
tak(int x, int y, int z)
{
  if (x <= y)
    return y;
  else
    return tak(tak(x - 1, y, z),
               tak(y - 1, z, x),
               tak(z - 1, x, y));
}

static void
print_values(FILE *out, int threads, int x, int y, int z)
{
    fprintf(out, " #THREADS: %d\n", threads);
    fprintf(out, " X: %d\n", x);
    fprintf(out, " Y: %d\n", y);
    fprintf(out, " Y: %d\n", z);
}

static void __attribute__((__noreturn__))
print_usage(int status, FILE *out, const char *prog,
            int n_threads, int x, int y, int z)
{
    fputs("\nUsage: \n", out);
    fprintf(out, "  %s [options] [X Y Z]\n", prog);

    fputs("\nOptions:\n", out);

    fprintf(out, " -t, --threads <threads>  the number of threads [%d]\n", n_threads);
    fputs(       " -c, --cgroup <group>     add self to the group\n", out);
    fputs(       " -i, --interactive        print pid and wait input before launching threads\n", out);
    fputs(       " -v, --verbose            run in verbose mode\n", out);
    fputs(       " -h, --help               print this message\n", out);

    fprintf(out, "\nDefault values:\n");
    print_values(out, n_threads, x, y, z);
    exit(status);
}

struct data {
    pthread_mutex_t l;
    pthread_cond_t c;
    int *v;
};

static void*
run_tak(void *data)
{
    struct data *d = data;
    int *v = d->v;

    tak(v[X], v[Y], v[Z]);

    return NULL;
}

static void
m_tak(int n_threads, pthread_t *threads, struct data *d)
{
    for (int i = 0; i < n_threads; i++) {
        int e = pthread_create(&(threads[i]), NULL, run_tak, d);
        if (e != 0) {
            errno = e;
            err(EXIT_FAILURE, "Failed in creating a thread");
        }
    }

    for (int i = 0; i < n_threads; i++) {
        int e = pthread_join(threads[i], NULL);
        if (e != 0) {
            errno = e;
            err(EXIT_FAILURE, "Failed in joining a thread");
        }
    }
}

int
main(int argc, char *argv[])
{
    int o;
    int n_threads = 1;
    int v[] = {
        [X] = 14,
        [Y] = 8,
        [Z] = 0
    };

    bool verbose = false;
    bool interactive = false;
    char *cgroup_fname = NULL;
    FILE *cgroup_fp = NULL;

	static const struct option longopts[] = {
		{ "help", no_argument, NULL, 'h' },
        { "verbose", no_argument, NULL, 'v'},
        { "interactive", no_argument, NULL, 'i'},
        { "threads", required_argument, NULL, 't'},
        { "cgroup", required_argument, NULL, 'c'},
		{ NULL, 0, NULL, 0 },
	};

    while ((o = getopt_long(argc, argv, "hvit:c:", longopts, NULL)) != -1) {
        switch (o) {
        case 'h':
            print_usage(EXIT_SUCCESS, stdout, argv[0],
                        n_threads, v[X], v[Y], v[Z]);
            break;
        case 'v':
            verbose = true;
            break;
        case 't':
            n_threads = atoi(optarg);
            break;
        case 'i':
            interactive = true;
            break;
        case 'c':
            if (asprintf(&cgroup_fname, "/sys/fs/cgroup/%s/cgroup.procs", optarg) < 0)
                err(EXIT_FAILURE, "Memory exhausted");
            cgroup_fp = fopen(cgroup_fname, "a");
            if (!cgroup_fp)
                err(EXIT_FAILURE, "Failed in opening %s", cgroup_fname);
            break;
        default:
            errx(EXIT_FAILURE, "Unkown option: -%c", o);
        }
    }

    switch (argc - optind) {
    case 3:
        v[X] = atoi(argv[optind + X]);
        v[Y] = atoi(argv[optind + Y]);
        v[Z] = atoi(argv[optind + Z]);
        break;
    case 0:
        break;
    default:
        errx(EXIT_FAILURE, "Unexpected number of arguments: %d %d", argc, optind);
    }

    if (verbose)
        print_values(stderr, n_threads, v[X], v[Y], v[Z]);

    pthread_t *threads = malloc(sizeof(pthread_t) * n_threads);
    if (!threads)
        err(EXIT_FAILURE, "Memory exhausted");

    struct data d = {
        .v = v
    };

    if (interactive) {
        printf("%d\n", getpid());
        fflush(stdout);
        fprintf(stderr, "[press anykey] ");
        getchar();
    }

    if (cgroup_fp) {
        if (fprintf(cgroup_fp, "%d", getpid()) < 0)
            err(EXIT_FAILURE, "Failed in writing the pid to %s", cgroup_fname);
        free(cgroup_fname);
        fclose(cgroup_fp);
    }

    m_tak(n_threads, threads, &d);

    free(threads);
    return 0;
}
