/* A process can overwrites the command name printed by 
   ps command.

  $ gcc rename-self.c
  $ ./a.out &
  $ watch 'ps -aef | grep out'
*/

#include <string.h>
#include <stdlib.h>

int
main(int argc, char** argv)
{
  char * name = argv[0];

  while(1) 
    {
      char *tmp = strstr(name, ".out");
      *(tmp - 1) = 'a' + (rand() % 26);
      sleep (1);
    }
  return 0;
}
