CFLAGS=-g -Wall -Wextra -std=c99
LDFLAGS=-pthread

PROGRAMS=					\
	div-by-0				\
	exit					\
	fdrop					\
	fork-competition			\
	fork-loop				\
	fshog					\
	getpid					\
	lserrno					\
	rename-self				\
	return					\
	sleep-loop				\
	spin					\
	thread-loop				\
	write-stop				\
	yeild					\
	zombie-maker				\
	\
	$(NULL)

all: $(PROGRAMS)
	$(MAKE) -C mmap
	$(MAKE) -C kvm
	$(MAKE) -C container
	(cd build-strace; bash rhel8.sh)
	(cd build-lsof; bash rhel8.sh)
