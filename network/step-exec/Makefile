COMMANDS=step-server-unix step-client-unix step-server-tcp step-client-tcp 
BUILD=gcc -g -O0 -o $@ $^
all: $(COMMANDS)

step-server-unix: step-server-unix.c common.h
	$(BUILD)
step-client-unix: step-client-unix.c common.h
	$(BUILD)

step-server-tcp: step-server-tcp.c common.h
	$(BUILD)
step-client-tcp: step-client-tcp.c common.h
	$(BUILD)

clean:
	rm -f $(COMMANDS) *.o *~

.PHONY: clean all
