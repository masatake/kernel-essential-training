CFLAGS = -g -O0 -Wall -Wno-unused-function
.PHONY: all clean

# EXTRA= io0 io1 io2
PROGS = genfile \
	write-via-write read-via-read \
	write-via-stdio read-via-stdio \
	write-via-mmap read-via-mmap \
	$(EXTRA) \
	\
	$(NULL)

all: $(PROGS)

genfile: genfile.o

# io0: io0.o
# io1: io1.o
# io2: io2.o

write-via-mmap: write-via-mmap.o
read-via-mmap: read-via-mmap.o
write-via-write: write-via-write.o
read-via-read: read-via-read.o
read-via-stdio: read-via-stdio.o
write-via-stdio: write-via-stdio.o

clean:
	rm -f $(PROGS) $(addsuffix .o, $(PROGS))
	rm -f *~

