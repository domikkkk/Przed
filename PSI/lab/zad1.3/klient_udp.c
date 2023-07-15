// Fedir Tsupin
// Laboratorium PSI Zadanie 1
// 30.03.2023
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include "common.h"

#define htonll(x) ((((uint64_t)htonl(x)) << 32) + htonl((x) >> 32))

#pragma pack(1)
struct Data
{
	char name[10];
	long long id;
	int time;
	short position[3];
};

typedef struct Data Message;

#define structString "struct { char name[10]; long long id; int time; short position[3];}"

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
	// zadanie 1.3

	Message testMessage;
	strncpy(testMessage.name, "Klient1", sizeof(testMessage.name) - 1);
	testMessage.name[sizeof(testMessage.name) - 1] = '\0';
	testMessage.id = htonll(123);
	testMessage.time = htonl(time(0));
	testMessage.position[0] = htons(1);
	testMessage.position[1] = htons(2);
	testMessage.position[2] = htons(3);

	// send data
	int res = sendto(fdSocket, &testMessage, sizeof(testMessage), 0, (struct sockaddr *)&clientSocket, socklen);
	printf("res: %d\n", res);

	// send the format
	int res2 = sendto(fdSocket, structString, sizeof(structString), 0, (struct sockaddr *)&clientSocket, socklen);
	printf("res2: %d\n", res2);
	if (close(fdSocket) == -1)
		perror("Warning, close returned -1"); // according to manual, no need to try to close again.
	return 0;
}
