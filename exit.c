/* The value passed to exit becomes the exit status of the process
 * thought main() returns 0.
 * 
 * Usage:
 *  ./a.out; echo $? */

#include <stdlib.h>

int
main(void)
{
  exit(31);
  return 0;
}
