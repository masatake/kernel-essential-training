#include <stdio.h>
#include <string.h>

int
main(void)
{
  int unknown_count = 0;
  for (int i = 0; i >=0; i++)
    {
      char * str = strerror (i);
      if (str == NULL)
	continue;

      if (unknown_count > 16)
	break;
      if (strstr (str, "Unknown error"))
	{
	  unknown_count++;
	  continue;
	}

      printf ("%d: %s\n", i, str);
    }
  return 0;
}
