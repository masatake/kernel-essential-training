init: main.o f.o
	gcc -O0 -g -o $@ $^
%.o: %.cxx f.hxx
	gcc -O0 -g -c $<

