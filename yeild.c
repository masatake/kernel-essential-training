/* Try to release the CPU */
#include <sched.h>

int
main(void)
{
  while (1)
    sched_yield();
}
