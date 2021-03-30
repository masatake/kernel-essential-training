#define _GNU_SOURCE
#include <sched.h>
#include <error.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/limits.h>
#include <sys/mount.h>
#include <stdint.h>
#include <sys/eventfd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

static void
print_pids (const char *header)
{
  fprintf(stderr, "%s: (pid = %u, ppid = %u)\n",
	  header, getpid(), getppid());
}

static void
prompt (const char *str)
{
  fputs(str? str: "[press key] ", stderr);
  getchar ();
}

static void
print_pidns (const char *header, const char *ns)
{
  if (ns == NULL)
    {
      fprintf(stderr, "%s: (", header);
      print_pidns (NULL, "pid");
      fputs(", ", stderr);
      print_pidns (NULL, "pid_for_children");
      fputs(")\n", stderr);
    }
  else
    {
      char path [PATH_MAX];
      sprintf(path, "/proc/%d/ns/%s", getpid(), ns);
      struct stat st;

      if (stat(path, &st) < 0)
	{
	  if (errno != ENOENT)
	    error (1, errno, "failed in stat(%s)", path);
	  else
	    fprintf(stderr, "ns:%s = <NOENT>", ns);
	}
      else
	fprintf(stderr, "ns:%s = %lu", ns, st.st_ino);
    }
}

static void
remount(void)
{
  if (unshare (CLONE_NEWNS) < 0)
    error (1, errno, "unshare(NEWNS)");

  /* Mysterious technique found in the output of strace when
   * targeting unshare --pid --fork --mount-proc /bin/true */
  
  /* Make all morunt points */
  if (mount("none", "/", NULL, MS_REC|MS_PRIVATE, NULL) < 0)
    error (1, errno, "remount /");

  /* umount /proc */
  if (mount("none", "/proc", NULL, MS_REC|MS_PRIVATE, NULL) < 0)
    error (1, errno, "/proc");

  /* mount /proc */
  if (mount("proc", "/proc", "proc", MS_NOSUID|MS_NODEV|MS_NOEXEC, NULL) <0)
    error (1, errno, "/proc");
}

int
main(void)
{
  print_pids  ("initial state");
  print_pidns ("initial state", NULL);
  
  fprintf(stderr, "### unshare(CLONE_NEWPID) ###\n");
  if (unshare (CLONE_NEWPID) < 0)
    error (1, errno, "failed in unshare(CLONE_NEWPID)");

  print_pids ("after unshare(CLONE_NEWPID)");
  print_pidns ("after unshare(CLONE_NEWPID)", NULL);
  prompt (NULL);

  int efd = eventfd (0, 0);
  if (efd < 0)
    error (1, errno, "eventfd");

  fprintf(stderr, "### fork() ###\n");
  pid_t pid = fork ();
  uint64_t d;
  if (pid == 0)
    {
      if (read (efd, &d, sizeof(d)) != sizeof(d))
	error (1, errno, "read(eventfd)");

      print_pids ("<child>after fork");
      print_pidns ("<child>after fork", NULL);

      if (read (efd, &d, sizeof(d)) != sizeof(d))
	error (1, errno, "read(eventfd)");

      fprintf(stderr, "### remount /proc ###\n");
      remount ();

      print_pids ("<child+remounted proc>after fork");
      print_pidns ("<child+remounted proc>after fork", NULL);

      if (read (efd, &d, sizeof(d)) != sizeof(d))
	error (1, errno, "read(eventfd)");

      _exit(0);
    }
  else if (pid > 0)
    {
      print_pids ("<parent>after fork");
      print_pidns ("<parent>after fork", NULL);
      d = 1;
      if (write (efd, &d, sizeof(d)) != sizeof(d))
	error (1, errno, "write(eventfd)");

      prompt(NULL);
      d = 1;
      if (write (efd, &d, sizeof(d)) != sizeof(d))
	error (1, errno, "write(eventfd)");

      prompt(NULL);

      fprintf(stderr, "### wait for death of child###\n");
      if (write (efd, &d, sizeof(d)) != sizeof(d))
	error (1, errno, "write(eventfd)");
      wait(NULL);

      print_pids ("<parent>after wait");
      print_pidns ("<parent>after wait", NULL);
      prompt(NULL);

      fprintf(stderr, "### make another child###\n");
      fork ();
      fprintf(stderr, "### %s ###\n", strerror(errno));
      print_pids ("<parent>after the 2nd fork");
      print_pidns ("<parent>after the 2nd fork", NULL);

      prompt(NULL);
    }
  else
    error (1, errno, "fork");

  return 0;
}
