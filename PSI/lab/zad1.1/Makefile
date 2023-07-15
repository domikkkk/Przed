all: serwer_udp klient_udp

serwer_udp : serwer_udp.c common.c
	gcc -g -Wall $^ -o $@ 

klient_udp : klient_udp.c common.c
	gcc -g -Wall $^ -o $@ 

clean:
	rm -f klient_udp serwer_udp *.o