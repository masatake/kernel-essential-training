#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>

extern int func_global_a (int);
extern int var_global_a;
extern int var_global_init_a;
extern const int const_global_init_a;

extern void report_fun_a(void);
extern void report_var_a(void);
extern void report_const_a(void);

__thread int thr_thrglobal;
__thread int thr_thrglobal_init = 0xfff4;

static void* thr_func (void *data)
{
    int thr_funlocal;
    static __thread int thr_thrlocal;
    static __thread int thr_thrlocal_init = 0xfff3;

    printf("thr_funlocal[%u]: %p\n", pthread_self(), &thr_funlocal);
    printf("thr_thrlocal[%u]: %p\n", pthread_self(), &thr_thrlocal);
    printf("thr_thrlocal_init[%u]: %p\n", pthread_self(), &thr_thrlocal_init);
    printf("thr_thrglobal[%u]: %p\n", pthread_self(), &thr_thrglobal);
    printf("thr_thrglobal_init[%u]: %p\n", pthread_self(), &thr_thrglobal_init);
}

static void* print_map (void * data)
{
    pid_t *pid = data;
    pid_t pid_;

    if (pid == NULL) {
        /* Not in a thread */
        pid_ = getpid();
        pid = &pid_;
    } else
        thr_func(NULL);

    puts("");
    fflush(stdout);

    char buffer[256];
    /* snprintf(buffer, sizeof (buffer), "cat /proc/%d/maps", *pid); */
    snprintf(buffer, sizeof (buffer), "pmap %d", *pid);
    system (buffer);

    char c;
    read(0, &c , 1);
    return NULL;
}

static void usage(const char *prog)
{
    printf("Usage: \n");
    printf("	%s --help\n", prog);
    printf("	%s [--thread]\n", prog);
    exit (0);
}


int main(int argc, char **argv)
{
    static int var_funstatic_main;
    static int var_funstatic_init_main = 0xfff1;
    const static int const_funstatic_init_main = 0xfff5;
    int var_funlocal_main;
    int var_funlocal_init_main = 0xfff2;
    const  int const_funlocal_init_main = 0xfff6;

    void *ptr_malloc_small;
    void *ptr_malloc_large;

    bool use_thread = false;
    if (argc > 2) {
        fprintf(stderr, "too many arguments\n");
        exit (0);
    } else if (argc == 2) {
        if (strcmp (argv[1], "--help") == 0
            || strcmp (argv[1], "-help") == 0
            || strcmp (argv[1], "-h") == 0
            || strcmp (argv[1], "-?") == 0)
            usage(argv[0]);
        else if (strcmp(argv[1], "--thread") == 0)
            use_thread = true;
    }

    pid_t pid = getpid();
    printf("pid: %d\n", pid);
    printf("main: %p\n", &main);
    printf("argc: %p\n", &argc);
    printf("env(HOME): %p\n", getenv("HOME"));

    ptr_malloc_small = malloc (1);
    printf("ptr_malloc_small: %p\n", ptr_malloc_small);
    ptr_malloc_large = malloc (1024 * 1024 * 4);
    printf("ptr_malloc_large: %p\n", ptr_malloc_large);

    printf("var_funstatic_main: %p\n",      &var_funstatic_main);
    printf("var_funstatic_init_main: %p\n", &var_funstatic_init_main);
    printf("var_funlocal_main: %p\n",     &var_funlocal_main);
    printf("var_funlocal_init_main: %p\n",     &var_funlocal_init_main);

    printf("const_funstatic_init_main: %p\n", &const_funstatic_init_main);
    printf("const_funlocal_init_main: %p\n", &const_funlocal_init_main);

    printf("func_global_a: %p\n", &func_global_a);
    report_fun_a();
    printf("var_global_a: %p\n", &var_global_a);
    printf("var_global_init_a: %p\n", &var_global_init_a);
    report_var_a();
    printf("const_global_init_a: %p\n", &const_global_init_a);
    report_const_a();

    if (use_thread) {
        thr_func (NULL);
        pthread_t thr;
        pthread_create(&thr, NULL, print_map, &pid);
        pthread_join (thr, NULL);
    } else
        print_map (NULL);

    return 0;
}
