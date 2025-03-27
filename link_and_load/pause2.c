#include <unistd.h>
int
main(void)
{
  char c;
  read (0, NULL, 0);
  read (0, &c, 1);  
  return 0;
}
