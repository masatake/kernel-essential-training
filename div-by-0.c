/* Trigger exceptions with decide-by 0.
   This program prints the pid of self.
   Monitor the value of nonvoluntary_ctxt_switches in
   $ watch -n 1 'cat /proc/$pid/status' */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void
handler(int num)
{
  getppid ();
}

int
main(int argc, char** argv)
{
  volatile int i;

  fprintf(stderr, "pid: %lu\n", getpid());
  signal(SIGFPE, handler);

  while (1)
    i = argc/(argc-1);

  return 0;
}
