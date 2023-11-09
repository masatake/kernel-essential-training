#include <poll.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
#define N 1000
  struct pollfd pfds[N];

  for (int i = 0; i < N; i++) {
    pfds[i].fd = open("/dev/null", O_RDONLY);
    if (pfds[i].fd < 0) {
      perror("open");
      return 1;
    }
    pfds[i].events = POLLIN;
  }

  while (1) {
    if (poll(pfds, N, -1) < 0) {
      perror("poll");
      return 1;
    }
  }

  return 0;
}
