// Fedir Tsupin
// Laboratorium PSI Zadanie 2.1
// 02.04.2023
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <unistd.h>
#include <time.h>
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
		return 1;
	}
    if (connect(fdSocket, (struct sockaddr *) &clientSocket, sizeof clientSocket) == -1)
    {
        perror("connecting stream socket");
        exit(1);
     }
	char msgBuffer[15] = "Hello, Server!";
    if (write(fdSocket, msgBuffer, sizeof msgBuffer) == -1) perror("Error while writing");

	char rcvBuffer[MAX_MESSAGE+1]; //for null terminator
	memset(rcvBuffer, 0, sizeof rcvBuffer);
	if (read(fdSocket,rcvBuffer, MAX_MESSAGE+1) == -1)
	{
		perror("reading stream message");
		return 1;
	}
	printf("Server: %s\n", rcvBuffer);

	close(fdSocket);
    exit(0);
}