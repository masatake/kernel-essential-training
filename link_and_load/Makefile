PROGS = pause pause2 vdso local getenv nop nop_with_fat_txt
all: $(PROGS)

pause: pause.o
pause2: pause2.o
vdso: vdso.o
local: local.o
getenv: getenv.o
nop: nop.o
nop_with_fat_txt: nop_with_fat_txt.o

%.o: %.c
	gcc -g -O0 -c $<

.PHONY: clean
clean:
	rm -f *.o $(PROGS)
