all: dl hello.so bonjour.so

dl: dl.o
%.o: %.c
	gcc -Wall -g -O0 -c $<
%.so: %.c
	gcc -Wall -g -shared -fPIC -o $@ $<

.PHONY: clean
clean:
	rm -f dl *.o *.so *~
