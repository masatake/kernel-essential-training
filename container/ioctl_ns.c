/*
 * Inspect owner ns and parent ns for given ns fd
 */
#include <stdio.h>
#include <errno.h>
#include <error.h>
#include <sys/sysmacros.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <err.h>
#include <sys/ioctl.h>

#ifndef NS_GET_USERNS
#define NSIO    0xb7
#define NS_GET_USERNS   _IO(NSIO, 0x1)
#define NS_GET_PARENT   _IO(NSIO, 0x2)
#endif

void
usage (char *prog, FILE *fp, int status)
{
  fprintf(fp, "Usage: %s namespace-file\n", prog);
  exit(status);
}

int
main(int argc, char **argv)
{
  if (argc != 2)
    usage (argv[0], stderr, 1);

  if (strcmp(argv[1], "-h") == 0
      || strcmp(argv[1], "--help") == 0)
    usage (argv[0], stdout, 0);

  char *f = argv[1];
  int fd = open(f, O_RDONLY);
  if (fd < 0)
    error (1, errno, "failed to open %s", f);

  struct stat st;
  if (fstat (fd, &st) < 0)
    error (1, errno, "failed to fstat %s", f);

  printf("%s -> %llu\n", f, (unsigned long long)st.st_ino);

  fputs("owner -> ", stdout);
  int owner = ioctl(fd, NS_GET_USERNS);
  if (owner < 0)
    {
      fputs("0 # ", stdout);
      error(0, errno, "%s", f);
    }
  else
    {
      if (fstat (owner, &st) < 0)
	error (1, errno, "failed to fstat owner ns fd of %s", f);
      printf("%llu\n", (unsigned long long)st.st_ino);
    }

  fputs("parent -> ", stdout);
  int parent = ioctl(fd, NS_GET_PARENT);
  if (parent < 0)
    {
      fputs("0 # ", stdout);
      error(0, errno, "%s", f);
    }
  else
    {
      if (fstat (parent, &st) < 0)
	error (1, errno, "failed to fstat parent ns fd of %s", f);
      printf("%llu\n", (unsigned long long)st.st_ino);
    }

  return 0;
}
