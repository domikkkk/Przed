
all: cc asm link
cc:
	cc -m32 -std=c99 -c main.c image.h image.c

asm:
	nasm -f elf32 sepia.s

link:
	cc -m32 -o main main.o image.o sepia.o

