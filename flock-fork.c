#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void
usage(const char* name, FILE *fp, int status)
{
  fprintf(fp, "Usage: %s filname\n", name);
  exit(status);
}

int
main(int argc, char **argv)
{
  if (argc != 2)
    {
      fprintf(stderr, "Unexpected number of arguments\n");
      return 1;
    }
  if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    usage(argv[0], stdout, 0);

  int fd = open(argv[1], O_RDWR);
  if (fd < 0)
    {
      perror("open");
      return 1;
    }

  if (flock(fd, LOCK_EX) < 0)
    {
      perror("flock");
      return 1;
    }

  fprintf(stderr, "A lock is held. press [enter] for forking: ");
  getchar();
  pid_t pid = fork();
  if (pid < 0)
    {
      perror("fork");
      return 1;
    }

  if (pid == 0)
    sleep(300);			/* child */
  else
    exit(0);			/* parent */

  return 0;
}
