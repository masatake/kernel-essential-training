#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int
main (void)
{
  const int n = 10;
  fprintf(stderr, "making %d zombies...", n);
  for (int i = 0; i < n; i++)
    {
      pid_t pid = fork ();
      if (pid < 0)
    	{
	  perror ("fork");
	  return 1;
    	}
      else if (pid == 0)
	exit (i);
    }
  fprintf(stderr, "done\n");
  fprintf(stderr, "press [enter] for sending them to haven");
  getchar ();

  for (int i = 0; i < 10; i++)
    wait (NULL);	

  while (1);
  return 0;
}
