CC = exec cc

all: semafory staff end link
semafory:
	${CC} -c semafory.c
staff:
	${CC} -c staff.c
end:
	${CC} -c main.c
link:
	${CC} -o main *.o
clean:
	rm *.o
	rm *.gch