#include <unistd.h>
#include <sys/random.h>

int
main(void)
{
  int c;
  read (0, NULL, 0);
  read (0, &c, 1);
  int r = getrandom (&c, sizeof(c), 0);
  read (0, &c, 1);
  return 0;
}
