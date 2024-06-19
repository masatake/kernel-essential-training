#include <stdio.h>

static void
foo(int *x)
{
  *x = 1;
}

int
main(void)
{
  int *x = NULL;
  foo (x);
  return *x;
}
