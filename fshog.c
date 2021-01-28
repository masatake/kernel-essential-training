#include <errno.h>
#include <error.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define buf_size_in_MB 32
#define buf_size (1024 * 1024 * buf_size_in_MB)
const static char buf [buf_size];

static void
print_usage(const char *prog, int status)
{
  fprintf(stderr, "Usage:\n\t%s file sizeInGB\n", prog);
  exit (status);
}

int
main (int argc, char **argv)
{
  if (argc != 3)
    {
      fprintf(stderr, "wrong number of arguments: %d\n", argc);
      print_usage(argv[0], 1);
    }

  const char *fname = argv[1];
  char *p;
  errno = 0;
  unsigned long int sizeInGB = strtoul(argv[2], &p, 10);
  if (sizeInGB == 0 || sizeInGB == ULONG_MAX)
    {
      if (errno)
	{
	  perror(argv[2]);
	  print_usage (argv[0], 1);
	}
      else if (p == argv[2])
	{
	  fprintf (stderr, "an integer expected: %s\n", argv[2]);
	  print_usage (argv[0], 1);
	}
    }

  int fd = open(fname, O_WRONLY|O_CREAT);
  if (fd < 0)
    error(1, errno, "failed to open: %s\n", fname);

  if (unlink(fname) < 0)
    error(1, errno, "failed to unlink: %s\n", fname);

  {
    if (open(fname, O_WRONLY|O_CREAT) < 0)
      error(1, errno, "failed to create: %s\n", fname);
  }

  
  fprintf(stderr, "start hogging");

  int sizeInXMB = sizeInGB * (1024 / buf_size_in_MB);
  int i;
  for (i = 0; i < sizeInXMB; i++)
    {
      int r = write(fd, buf, buf_size);
      if (r == buf_size)
	fputc('.', stderr);
      else if (r < 0)
	error(1, errno, "failed to write\n");
      else
	{
	  fprintf(stderr, "write buffer %d MB it too large: %d\n",
		  buf_size_in_MB,  r);
	  exit (1);
	}
    }
  fprintf(stderr, "done. entring sleep.\npress [return] for exiting: ");

  getchar ();

  return 0;
}
