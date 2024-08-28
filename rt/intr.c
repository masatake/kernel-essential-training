#define _GNU_SOURCE

#define DEFAULT_BDEV "/dev/nvme0n1p1"
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <err.h>
#include <unistd.h>

#include <sys/uio.h>

struct iovec iov[1024];

int main(int argc, char **argv)
{
  const char *dev = DEFAULT_BDEV;
  if (argc > 1)
    dev = argv[1];

  int fd = open(dev, O_DIRECT|O_RDONLY|O_NOATIME);
  if (fd < 0)
    err(1, "open %s", dev);

  char buf[512];

  for (int i = 0; i < sizeof(iov)/ sizeof(iov[0]); i++)
    {
      iov[i].iov_base = buf;
      iov[i].iov_len = sizeof(buf);
    }
  
  while(1)
    {
      int n;
      while ((n = readv(fd, iov, sizeof(iov)/ sizeof(iov[0])))
	     == (sizeof(iov)/ sizeof(iov[0]) * sizeof(buf)))
	{
	  if (n < 0)
	    err(1, "reading %s", dev);
	}
      lseek(fd, 0, SEEK_SET);
    }
  return 0;
}
