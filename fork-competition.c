/* Just after froking, the parent or its child, 
 * which process gets a cpu first? */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

/* 
 * taskset -p 1 $$
 * echo 1 > /proc/sys/kernel/sched_child_runs_first 
 */

int
main (void)
{
  pid_t pid = fork ();
  fprintf(stderr, "%lu\n", pid);
  return 0;
}
