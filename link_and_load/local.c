#include <stdio.h>

int main(void)
{
  int i;
  printf("main -> %p\n", &main);
  printf("i    -> %p\n", &i);
  return 0;
}
