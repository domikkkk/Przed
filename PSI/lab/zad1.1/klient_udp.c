// Tomasz Sroka
// Laboratorium PSI Zadanie 1
// 30.03.2023
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include "common.h"

int main(int argc, char *argv[])
{
	int fdSocket;
	struct sockaddr_in clientSocket;
	struct in_addr convert;
	socklen_t socklen = sizeof(clientSocket);

	memset(&clientSocket, 0, socklen);

	if (argc < 3)
	{
		fprintf(stderr, "Usage: klient_udp <adres_serwera> <port>\n");
		exit(1);
	}
	in_port_t port = GetPortFromArguments(argv[2]);

	if (inet_aton(argv[1], &convert) == 0)
	{
		fprintf(stderr, "Invalid address: %s\n", argv[1]);
		exit(1);
	};

	clientSocket.sin_family = AF_INET;
	clientSocket.sin_port = htons(port);
	clientSocket.sin_addr.s_addr = convert.s_addr;

	fdSocket = socket(AF_INET, SOCK_DGRAM, 0);

	if (fdSocket == -1)
	{
		perror("Error while creating a socket");
		exit(1);
	}

	char msgBuffer[256];
	for (unsigned i = 0; i < 10; ++i)
	{
		snprintf(msgBuffer, sizeof(msgBuffer), "Message #%d", i);
		printf("Sending \"%s\"\n", msgBuffer);
		// int err = send(fdSocket, msgBuffer, strlen(msgBuffer),0);  this could work with connect() beforehand
		int err = sendto(fdSocket, msgBuffer, strlen(msgBuffer), 0, (struct sockaddr *)&clientSocket, sizeof(clientSocket));
		if (err == -1)
		{
			perror("Send error\n");
			exit(1);
		}

		usleep(5e5);
	}

	if (close(fdSocket) == -1)
		perror("Warning, close returned -1"); // according to manual, no need to try to close again.
	return 0;
}