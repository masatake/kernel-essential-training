#define _POSIX_C_SOURCE 200112L
#include <fcntl.h>
#include <stdio.h>

int
main(int argc, char **argv)
{
	int fd;

	if (argc < 1) {
		fprintf (stderr, "missing file\n");
		return 1;
	}

	fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		perror ("open");
		return 1;
	}

	if (posix_fadvise(fd, 0, 0, POSIX_FADV_DONTNEED) < 0) {
		perror ("fadvise");
		return 1;
	}

	return 0;
}
