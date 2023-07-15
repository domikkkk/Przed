// Tomasz Sroka
// Laboratorium PSI Zadanie 1
// 23.03.2023

// na podstawie manuali bind(2), ip(7), udp(7) i innych powiązanych

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <memory.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include "common.h"

int main(int argc, char *argv[])
{
	int fdSocket;
	struct sockaddr_in serverAddr, clientAddr, checkPort;
	in_port_t port;
	char msgBuffer[MAX_MESSAGE + 1]; // for null terminator

	socklen_t server_size = sizeof(serverAddr);
	socklen_t client_size = sizeof(clientAddr);
	socklen_t checkPort_size = sizeof(checkPort);

	memset(&serverAddr, 0, server_size);
	memset(&clientAddr, 0, client_size);

	// if no port specified, let system choose ephemeric
	port = argc == 1 ? 0 : GetPortFromArguments(argv[1]);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	fdSocket = socket(AF_INET, SOCK_DGRAM, 0);

	if (fdSocket == -1)
	{
		// program can't do much in this case
		perror("Error while creating a socket");
		exit(1);
	}

	if (bind(fdSocket, (struct sockaddr *)&serverAddr, server_size) == -1)
	{
		if (errno == EACCES)
			fprintf(stderr, "Restricted port number %hu<1024, run with sudo or use different port", port);
		else
			perror("Bind error");

		close(fdSocket);
		exit(1);
	}

	if (getsockname(fdSocket, (struct sockaddr *)&checkPort, &checkPort_size) == 0)
	{
		printf("UDP server listening on port %hu\n", ntohs(checkPort.sin_port));
	}
	else
	{
		perror("Getsockname error");
		close(fdSocket);
		exit(1);
	}

	int recvSize = 0;
	while (1)
	{
		recvSize = recvfrom(fdSocket, msgBuffer, MAX_MESSAGE, 0, (struct sockaddr *)&clientAddr, &client_size);
		if (recvSize == -1)
		{
			perror("Socket read error");
			close(fdSocket);
			exit(1);
		}
		msgBuffer[recvSize] = 0;
		printf("received %d bytes from %s: ", recvSize, inet_ntoa(clientAddr.sin_addr));
		printf("'%s'\n", msgBuffer);
	}

	// this is never reached
	close(fdSocket);
	return 0;
}
