/* 
 * Copyright 2019 Red Hat, Inc.
 * Copyright 2019 Masatake YAMATO
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#define _GNU_SOURCE
#define MAP_HUGETLB 0x40000 /* arch specific */
#define HPFLAGS (MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB)


#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <getopt.h>
#include <error.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#define GB (1024 * 1024 * 1024)
#define MB (1024 * 1024)

static void
usage(const char *prog, FILE *fp)
{
  fputs("Usage:\n", fp);
  fprintf(fp, "%s [--quiet] [(--length|-l) LENGTH] [(--protection|-p) PROTECTION] [(--file|-f) FILE] [(--hugepage|-H) HugePage] [(--megabyte|-m) MB] [--thread|--fork]\n", prog);
  fputs("	LENGTH: the length of mapping area in GB (default: 1)\n", fp);
  fputs("	PERSMISION: 4 charters [r|-][w|-][x|-][p|s] (default: r--s)\n", fp);
  fputs("	FILE: mapping file. /dev/zero implies ANONYMOUS mapping (default: /dev/zero)\n", fp);
}

static int
decode_protection(const char *str)
{
  int prot = 0;

  if (str[0] == '-')
    ;
  else if (str[0] == 'r')
    prot |= PROT_READ;
  else if (str[0] == '\0')
    error (1, 0,
	   "Too short (< 4) protection string: %lu\n",
	   strlen (str));
  else
    error (1, 0,
	   "Unexpected char in read field of protection string: %c\n",
	   str[0]);

  if (str[1] == '-')
    ;
  else if (str[1] == 'w')
    prot |= PROT_WRITE;
  else if (str[1] == '\0')
    error (1, 0,
	   "Too short (< 4) protection string: %lu\n",
	   strlen (str));
  else
    error (1, 0,
	   "Unexpected char in write field of protection string: %c\n",
	   str[1]);

  if (str[2] == '-')
    ;
  else if (str[2] == 'x')
    prot |= PROT_EXEC;
  else if (str[2] == '\0')
    error (1, 0,
	   "Too short (< 4) protection string: %lu\n",
	   strlen (str));
  else
    error (1, 0,
	   "Unexpected char in exec field of protection string: %c\n",
	   str[2]);

  return prot;
}

static int
decode_mflag(const char *str)
{
  int mflags = 0;
  
  if (! (str[0] != '\0' && str[1] != '\0' && str[2] != '\0'))
    error (1, 0,
	   "Too short (< 4) protection string: %lu\n",
	   strlen (str));

  if (str[3] == 's')
    mflags |= MAP_SHARED;
  else if (str[3] == 'p')
    mflags |= MAP_PRIVATE;
  else
    error (1, 0,
	   "Unexpected char in share/priviate field of protection string: %c\n",
	   str[3]);

  return mflags;
}

static int
prot2fflags (int prot)
{
  int flags = 0;

  if ((prot & PROT_READ) && (prot & PROT_WRITE))
    flags |= O_RDWR;
  else if (prot & PROT_READ)
    flags |= O_RDONLY;
  else if (prot & PROT_WRITE)
    flags |= O_WRONLY;

  return flags;
}

static int
openFor (const char *file, int flags)
{
  if (file == NULL)
    return -1;

  int fd = open (file, flags);
  if (fd == -1)
    error (1, -1,
	   "failed to open \"%s\"\n", file);

  return fd;
}

struct runData {
  char *addr;
  int prot;
  size_t length;
  int stride;
};

static char
run (char *addr, int prot, size_t length, int stride)
{
  volatile char c;
  for (int i = 0; i < (int) (length / stride); i++)
    {
      char *p = addr + (i * stride);
      if (prot & PROT_WRITE)
	*p = '1';
      else
	c += *p;
    }
  return c;
}

static void*
thread_run (void * arg)
{
  struct runData *data = arg;
  run (data->addr, data->prot, data->length, data->stride);
  return NULL;
}

int
main (int argc, char **argv)
{
  static struct option long_options[] =
    {
     {"file",       required_argument, NULL, 'f'},
     {"length",     required_argument, NULL, 'l'},
     {"protection", required_argument, NULL, 'p'},

     {"help",       no_argument,       NULL, 'h'},
     {"verbose",    no_argument,       NULL, 'v'},
     {"fork",       no_argument,       NULL, 'F'},
     {"thread",     no_argument,       NULL, 'T'},
     {"hugepage",   no_argument,       NULL, 'H'},
     {"megabyte",   no_argument,       NULL, 'm'},

     {"quiet",      no_argument,       NULL, 'q'},
    };

  size_t length = 1 * GB;
  int prot = PROT_READ;
  int mflags = MAP_SHARED;
  const char *file = NULL;
  bool verbose = false;
  bool do_fork = false;
  bool make_thread = false;
  bool quiet = false;
  bool hugepage = false;
  int unit = GB;
  
  while (1)
    {
      int option_index = 0;
      int c = getopt_long (argc, argv, "f:l:p:hvFTHqm",
			   long_options, &option_index);

      if (c == -1)
	break;

      switch (c)
	{
	case 'h':
	  usage (argv[0], stdout);
	  return 0;
	case 'l':
	  errno = 0;
	  length = strtoul (optarg, NULL, 10) * unit;
	  if (errno != 0)
	    error (1, errno,
		   "Failed to convert \"%s\" to integer\n", optarg);
	  break;
	case 'v':
	  verbose = true;
	  break;
	case 'p':
	  prot   = decode_protection (optarg);
	  mflags = decode_mflag(optarg);
	  break;
	case 'f':
	  file = optarg;
	  if (strcmp (file, "/dev/zero") == 0)
	    file = NULL;
	  break;
	case 'F':
	  do_fork = true;
	  break;
	case 'T':
	  make_thread = true;
	  break;	  
	case '?':
	  error (1, 0,
		 "Unknown option: %s\n", argv[optind]);
	  break;
	case 'q':
	  quiet = true;
          break;
        case 'H':
          hugepage = true;
          break;
        case 'm':
          unit = MB;
          length = length / 1024;
	}
    }

  int fflags  = prot2fflags(prot);
  
  int fd = openFor (file, fflags);
  if (fd == -1)
    mflags |= MAP_ANONYMOUS;

  if (hugepage)
    mflags = HPFLAGS;

  if (verbose)
    {
      printf ("Length: %lu\n", length);
      printf ("Protection: %x\n", prot);
      printf ("Flag: %x\n", mflags);
      printf ("File: %s (%d)\n", file, fd);
    }

  char *addr = mmap (NULL, length, prot, mflags, fd, 0);
  if (addr == MAP_FAILED)
    error (1, errno,
	   "Failed in mmap\n");
  
  struct runData d =
    {
     .addr = addr,
     .prot = prot,
     .length = length,
     .stride = 4096,
    };

  if (!quiet)
    {
      pid_t pid = getpid();
      printf("pid: %d\n", pid);
      printf("addr: %p\n", addr);
      fflush(stdout);
    }

  if (do_fork)
    {
      if (fork () < 0)
	error (1, errno, "Failed in fork");
    }

  if (make_thread)
    {
      pthread_t thr;
      int e = pthread_create (&thr, NULL, thread_run, &d);
      if (errno != 0)
	error (1, e, "Failed in pthread_create");
    }

  while (1)
    run (addr, prot, length, 4096);

  return 0;
}
