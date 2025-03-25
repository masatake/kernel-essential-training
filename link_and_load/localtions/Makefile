all: locations

%.o: %.c
	gcc -O0 -g -c $< -pthread
locations: a.o main.o
	gcc -O0 -g -o $@ $^ -pthread

.PHONY: clean
clean:
	rm -f *.o locations *~


