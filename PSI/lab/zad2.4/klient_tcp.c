// Fedir Tsupin, Krzysztof Stawarski
// Laboratorium PSI Zadanie 2.4
// 18.04.2023
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char **argv)
{
	int fdSocket;
	in_port_t port;
	struct sockaddr_in clientSocket;
	struct in_addr convert;
	socklen_t socklen = sizeof(clientSocket);

	memset(&clientSocket, 0, socklen);

	if (argc < 3)
	{
		fprintf(stderr, "Usage: klient_tcp <adres_serwera> <port>\n");
		exit(1);
	}
	port = GetPortFromArguments(argv[2]);

	if (inet_aton(argv[1], &convert) == 0)
	{
		fprintf(stderr, "Invalid address: %s\n", argv[1]);
		exit(1);
	};

	clientSocket.sin_family = AF_INET;
	clientSocket.sin_port = htons(port);
	clientSocket.sin_addr.s_addr = convert.s_addr;

	fdSocket = socket(AF_INET,SOCK_STREAM,0);

	if (fdSocket == -1)
	{
		perror("Error while creating a socket");
		exit(1);
	}
    if (connect(fdSocket, (struct sockaddr *) &clientSocket, sizeof clientSocket) == -1)
    {
        perror("connecting stream socket");
        exit(1);
    }

    char msgBuffer [1000];
    for (int i = 0; i < 1000; i++) msgBuffer[i] = 'X'; // 'Y';

    int msgCnt = 0;
    int batchCnt = 0;

	while(1)
	{
        struct timeval start;
        gettimeofday(&start, NULL);
		if (write(fdSocket, msgBuffer, sizeof msgBuffer) == -1) perror("Error while writing");
        msgCnt++; // count the messages sent
        if (batchCnt == 0) printf("Sent message batch no. %d that starts with %c\n", ++batchCnt, msgBuffer[0]);

        struct timeval end;
        gettimeofday(&end, NULL);
        unsigned long diff = end.tv_sec - start.tv_sec;
        if (diff > 0) printf("Sent message batch no. %d with first message no. %d after hanging for %lu seconds\n", ++batchCnt, msgCnt, diff);

	}
	close(fdSocket);
    exit(0);
}
