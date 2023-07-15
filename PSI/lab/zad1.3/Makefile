all: klient_udp


klient_udp : klient_udp.c common.c
	gcc -g -Wall $^ -o $@ 

clean:
	rm -f klient_udp *.o