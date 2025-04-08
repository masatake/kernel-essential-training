PROGS = pause pause2 vdso local getenv nop nop_with_fat_txt exit-asm exit-c
all: $(PROGS)

pause: pause.o
pause2: pause2.o
vdso: vdso.o
local: local.o
getenv: getenv.o
nop: nop.o
nop_with_fat_txt: nop_with_fat_txt.o

exit-asm.o: exit-asm.S
	gcc -O3 -c $< -nostdlib
exit-asm: exit-asm.o
	gcc -O3 -o $@ $< -nostdlib
exit-c.o: exit-c.c
	gcc -O3 -c $<
exit-c: exit-c.o
	gcc -O3 -o $@ $<

%.o: %.c
	gcc -g -O0 -c $<

.PHONY: clean
clean:
	rm -f *~ *.o $(PROGS)
