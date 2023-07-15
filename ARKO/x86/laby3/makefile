
all: asm cc link
cc:
	cc -m32 -std=c99 -c main.c

asm:
	nasm -f elf32 remove.s

link:
	cc -m32 -o main main.o remove.o

