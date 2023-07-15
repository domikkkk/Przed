all: serwer_tcp

serwer_tcp : serwer_tcp.c common.c
	exec cc -g -Wall $^ -o $@

clean:
	rm -f klient_tcp serwer_tcp *.o
