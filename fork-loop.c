#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int
main (void)
{
  pid_t pid = fork ();
  if (pid < 0)
    {
      perror ("fork");
      return 1;
    }
  fprintf(stderr, "%s: %lu\n",
	  (pid == 0)? "child": "parent", getpid());
  while (1);
  return 0;
}
