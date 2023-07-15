all: serwer_tcp klient_tcp

serwer_tcp : serwer_tcp.c common.c
	gcc -g -Wall $^ -o $@

klient_tcp : klient_tcp.c common.c
	gcc -g -Wall $^ -o $@

clean:
	rm -f klient_tcp serwer_tcp *.o
