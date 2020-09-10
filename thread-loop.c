/* gcc thread-loop.c -pthread */

#include <pthread.h>
#include <stdio.h>

void*
thrfn (void * unused)
{
  while (1);
  return 0;
}

int
main(void)
{
  pthread_t thr;

  int e = pthread_create (&thr, NULL, thrfn, NULL);
  if (e == 0)
    while (1);

  perror ("pthread_crete");
  return 1;
}
