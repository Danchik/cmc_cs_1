FINAL = all
COMPILER = gcc
ASSEMBLER = nasm
CFLAGS = -std=c99 -c -m32
SFLAGS = -f elf32
OFLAGS = -no-pie -z  noexecstack -m32

$(FINAL) : main2.o functions2.o
	$(COMPILER) main2.o functions2.o $(OFLAGS) -o $(FINAL) -lm
main1.o : main2.c
	$(COMPILER) $(CFLAGS) -o main2.o main2.c
functions2.o : functions2.asm
	$(ASSEMBLER) $(SFLAGS) -o functions2.o functions2.asm
clean :
	rm $(FINAL) *.o
