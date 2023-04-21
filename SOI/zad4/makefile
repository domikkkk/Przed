CC = exec cc

all: definy staff semafory main link clean
definy:
	$(CC) -c definy.h
staff:
	$(CC) -c staff.h staff.c
semafory:
	$(CC) -c monitory.c monitory.h
main:
	${CC} -c -lpthread main.c
link:
	$(CC) -o zad4 main.o staff.o monitory.o -lpthread
clean:
	rm *.o
	rm *.gch
