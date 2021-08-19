#include <poll.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define NTARGETS 1000000
int
main(void)
{
  struct pollfd * fds = malloc (sizeof (struct pollfd) * NTARGETS);
  if (!fds)
    {
      fprintf(stderr, "failed to alloc pollfds\n");
      return 1;
    }

  int devzero = open ("/dev/zero", O_RDONLY);
  if (devzero < 0)
    {
      perror("opening /dev/zero");
      return 1;
    }

  for (int i = 0; i < NTARGETS; i++)
    {
      fds[i].fd = (i == (NTARGETS -1))? devzero: STDIN_FILENO;
      fds[i].events = POLLIN;
    }


  while (1)
    {
      if (poll(fds, NTARGETS, 0) < 0)
	{
	  perror("poll");
	  return 1;
	}
    }
  return 0;
}
