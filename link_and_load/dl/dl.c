#include <dlfcn.h>
#include <err.h>

int
main(int argc, char **argv)
{
    if (argc  > 2)
        err(1, "too many arguments");
    else if (argc < 2)
        err(1, "too few arguments");

    char *soname = argv[1];

    void *handle = dlopen(soname, RTLD_LAZY);
    if (!handle)
        errx(1, "%s: %s\n", dlerror(), soname);

    void (*greet_fn)(void) = (void (*)(void)) dlsym(handle, "greet");
    if (!greet_fn)
        errx(1, "%s: %s\n", dlerror(), "greet");

    (*greet_fn)();

    dlclose (handle);

    return 0;
}
