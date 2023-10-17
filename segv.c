#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

static void
usage(const char * prog, int status)
{
  fprintf(status == 0? stdout: stderr,
	  "Usage: %s r|w\n", prog);
  exit (status);
}

int
main(int argc, char **argv)
{
  if (argc != 2)
    usage(argv[0], 1);

  if (strcmp(argv[1], "-h") == 0
      || strcmp(argv[1], "--help") == 0)
    usage(argv[0], 0);

  if (argv[1][0] != 'w' && argv[1][0] != 'r')
    usage(argv[0], 2);

  fprintf(stderr, "(pid: %d) address in hex? ", getpid());
  char buf[BUFSIZ];
  if (!fgets(buf, sizeof(buf), stdin))
    {
      fprintf(stderr, "NO INPUT\n");
      exit (1);
    }

  union addr
  {
    unsigned long num;
    char *ptr;
  } a;

  a.num = strtoul(buf, NULL, 16);
  if (a.num == ULONG_MAX)
    {
      perror("strtoul");
      exit (1);
    }

  char r = 0; 
  char *ptr = a.ptr;
  if (argv[1][0] == 'w')
    *a.ptr = 'x';
  else
    r = *a.ptr;

  return r;
}
