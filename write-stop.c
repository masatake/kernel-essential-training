/* 1. save this file as write-stop.c
 * 2. gcc -o write-stop -Wall -std=c99 write-stop.c 
 *
 * NOTE: /proc/sys/fs/xfs/speculative_prealloc_lifetime is a knob 
 *       for tuning the lifespan of prealloc'ed block.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void
write1M (void)
{
#define M (1024*1024)
  static char buf[M];
  if (write (1, buf, M) != M)
    {
      perror("write");
      exit (1);
    } 
  fputc('.', stderr);
}

int
main(int argc, char **argv)
{
  if (argc != 2)
    {
      fprintf(stderr, "unexpected number of arguments\n");
      return 1;
    }

  int m100 = atoi(argv[1]);
  if (m100 < 0)
    {
      fprintf(stderr, "specify an integer greater than 0  as the first arguement\n");
      return 1;
    }

  fprintf(stderr, "[BEFORE]\n");
  system ("df -h 1>&2");

  fprintf(stderr, "writing %d MB", m100 * 100);
  for (int i = 0; i < m100; i++)
    for (int j = 0; j < 100; j++)
      write1M ();
  sleep (1);
  fprintf(stderr, "done\n");

  for (int i = 0; i < 6; i++)
    {
      fprintf(stderr, "[AFTER %dm]\n", i);
      system ("df -h 1>&2");
      sleep (60);
    }
  fprintf(stderr, "[PRESS ANY KEY]");
   getchar();
   return 0;
 }

/* 
[root@localhost ~]# xfs_info  /dev/vdc
meta-data=/dev/vdc               isize=512    agcount=4, agsize=524288 blks
         =                       sectsz=512   attr=2, projid32bit=1
         =                       crc=1        finobt=0 spinodes=0
data     =                       bsize=4096   blocks=2097152, imaxpct=25
         =                       sunit=0      swidth=0 blks
naming   =version 2              bsize=4096   ascii-ci=0 ftype=1
log      =internal               bsize=4096   blocks=2560, version=2
         =                       sectsz=512   sunit=0 blks, lazy-count=1
realtime =none                   extsz=4096   blocks=0, rtextents=0
[root@localhost ~]# uname -a
Linux localhost.localdomain 3.10.0-514.el7.x86_64 #1 SMP Wed Oct 19 11:24:13 EDT 2016 x86_64 x86_64 x86_64 GNU/Linux
[root@localhost ~]# cat /etc/redhat-release 
Red Hat Enterprise Linux Server release 7.3 (Maipo)
[root@localhost ~]# df -h
Filesystem             Size  Used Avail Use% Mounted on
/dev/mapper/rhel-root  9.4G  4.3G  5.1G  46% /
devtmpfs               1.9G     0  1.9G   0% /dev
tmpfs                  1.9G     0  1.9G   0% /dev/shm
tmpfs                  1.9G  8.6M  1.9G   1% /run
tmpfs                  1.9G     0  1.9G   0% /sys/fs/cgroup
/dev/vda1             1014M  139M  876M  14% /boot
tmpfs                  380M     0  380M   0% /run/user/0
/dev/vdc               8.0G   33M  8.0G   1% /mnt
[root@localhost mnt]# ~/write-stop 11 > ./data
[BEFORE]
Filesystem             Size  Used Avail Use% Mounted on
/dev/mapper/rhel-root  9.4G  4.3G  5.1G  46% /
devtmpfs               1.9G     0  1.9G   0% /dev
tmpfs                  1.9G     0  1.9G   0% /dev/shm
tmpfs                  1.9G  8.6M  1.9G   1% /run
tmpfs                  1.9G     0  1.9G   0% /sys/fs/cgroup
/dev/vda1             1014M  139M  876M  14% /boot
tmpfs                  380M     0  380M   0% /run/user/0
/dev/vdc               8.0G   33M  8.0G   1% /mnt
writing 1100 MB................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................done
[AFTER 0m]
Filesystem             Size  Used Avail Use% Mounted on
/dev/mapper/rhel-root  9.4G  4.3G  5.1G  46% /
devtmpfs               1.9G     0  1.9G   0% /dev
tmpfs                  1.9G     0  1.9G   0% /dev/shm
tmpfs                  1.9G  8.6M  1.9G   1% /run
tmpfs                  1.9G     0  1.9G   0% /sys/fs/cgroup
/dev/vda1             1014M  139M  876M  14% /boot
tmpfs                  380M     0  380M   0% /run/user/0
/dev/vdc               8.0G  2.1G  6.0G  26% /mnt
[AFTER 1m]
Filesystem             Size  Used Avail Use% Mounted on
/dev/mapper/rhel-root  9.4G  4.3G  5.1G  46% /
devtmpfs               1.9G     0  1.9G   0% /dev
tmpfs                  1.9G     0  1.9G   0% /dev/shm
tmpfs                  1.9G  8.6M  1.9G   1% /run
tmpfs                  1.9G     0  1.9G   0% /sys/fs/cgroup
/dev/vda1             1014M  139M  876M  14% /boot
tmpfs                  380M     0  380M   0% /run/user/0
/dev/vdc               8.0G  2.1G  6.0G  26% /mnt
[AFTER 2m]
Filesystem             Size  Used Avail Use% Mounted on
/dev/mapper/rhel-root  9.4G  4.3G  5.1G  46% /
devtmpfs               1.9G     0  1.9G   0% /dev
tmpfs                  1.9G     0  1.9G   0% /dev/shm
tmpfs                  1.9G  8.6M  1.9G   1% /run
tmpfs                  1.9G     0  1.9G   0% /sys/fs/cgroup
/dev/vda1             1014M  139M  876M  14% /boot
tmpfs                  380M     0  380M   0% /run/user/0
/dev/vdc               8.0G  2.1G  6.0G  26% /mnt
[AFTER 3m]
Filesystem             Size  Used Avail Use% Mounted on
/dev/mapper/rhel-root  9.4G  4.3G  5.1G  46% /
devtmpfs               1.9G     0  1.9G   0% /dev
tmpfs                  1.9G     0  1.9G   0% /dev/shm
tmpfs                  1.9G  8.6M  1.9G   1% /run
tmpfs                  1.9G     0  1.9G   0% /sys/fs/cgroup
/dev/vda1             1014M  139M  876M  14% /boot
tmpfs                  380M     0  380M   0% /run/user/0
/dev/vdc               8.0G  2.1G  6.0G  26% /mnt
[AFTER 4m]
Filesystem             Size  Used Avail Use% Mounted on
/dev/mapper/rhel-root  9.4G  4.3G  5.1G  46% /
devtmpfs               1.9G     0  1.9G   0% /dev
tmpfs                  1.9G     0  1.9G   0% /dev/shm
tmpfs                  1.9G  8.6M  1.9G   1% /run
tmpfs                  1.9G     0  1.9G   0% /sys/fs/cgroup
/dev/vda1             1014M  139M  876M  14% /boot
tmpfs                  380M     0  380M   0% /run/user/0
/dev/vdc               8.0G  2.1G  6.0G  26% /mnt
[AFTER 5m]
Filesystem             Size  Used Avail Use% Mounted on
/dev/mapper/rhel-root  9.4G  4.3G  5.1G  46% /
devtmpfs               1.9G     0  1.9G   0% /dev
tmpfs                  1.9G     0  1.9G   0% /dev/shm
tmpfs                  1.9G  8.6M  1.9G   1% /run
tmpfs                  1.9G     0  1.9G   0% /sys/fs/cgroup
/dev/vda1             1014M  139M  876M  14% /boot
tmpfs                  380M     0  380M   0% /run/user/0
/dev/vdc               8.0G  1.2G  6.9G  14% /mnt
[PRESS ANY KEY]
 */
