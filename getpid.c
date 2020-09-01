/* On RHEL7, the result of getpid is cached in glibc.
   So even if calling getpid in an infinite loop, you 
   observe getpid only once in strace output. */

#include <sys/types.h>
#include <unistd.h>

int
main(void)
{
  pid_t p;

  while(1)
    p = getpid();

  return 0;
}
