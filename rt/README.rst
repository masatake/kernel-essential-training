Run cyclictest at well-controlled environments
==============================================

Requirements
----------------------------------------------

* Hardware

  CPU * 4 (only for using cpu #3)

* Commands

  - gcc
  - make
  - cyclictest (realtime-tests package)
  - tasktset   (util-linux package)
  - gnuplot    (gnuplot package (epel9))

* Assumed kernels

  RHEL9 kernel     (normal)
  RHEL9 kernel-rt  (rt)


C programs in this directory
----------------------------------------------
spin

	Hogging CPU in user mode

pollx

	Hogging CPU in kernel mode by calling poll(2) with a large fd array
	This reduces chances to call schedule().

intr

	Generating interrupts repeatedly by reading bytes from a block device
	with O_DIRECT. See DEFAULT_BDEV in intr.c to the block device.

Usage
----------------------------------------------

Normal kernel
..............................................

1. boot the normal kernel with runlevel 1.
2. login
3. adjust rt_runtime_us:

      # echo 950000 > /proc/sys/kernel/sched_rt_runtime_us

   See https://stackoverflow.com/questions/56904831/changing-thread-real-time-scheduling-policy-fails-config-rt-group-sched-y
   and https://access.redhat.com/solutions/7059424
   about the background

4. Run all-normal.sh

      # bash -x ./all-normal.sh

   This script runs the cyclictest at cpu #2 with
   different conditions

      no extra load,
      spin  process * 1,
      spin  process * 2,
      spin  process * 3,
      pollx process * 1,
      pollx process * 2,
      pollx process * 3.
      intr  process * 1,
      intr  process * 2, or
      intr  process * 3.

   spin, pollx, and intr processes are also pined at cpu #2.

5. View the histogram for the results of each condition

      $ eog normal-*.png

   You will see the spin processes have no impact on
   the latency.

   You will see the pollx processes have impact on
   the latency.

   You will see the intr processes have impact on
   the latency.

RT kernel
..............................................

1. boot the rt kernel with runlevel 1.
2. login
3. do nothing
4. Run all-rt.sh

      # bash -x ./all-rt.sh

5. View the histogram for the results of each condition

      $ eog rt-*.png
