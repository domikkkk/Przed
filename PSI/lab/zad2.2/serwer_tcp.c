// Dominik Sidorczuk
// Laboratorium PSI Zadanie 2.2
// 015.04.2023

#include <netinet/in.h>
#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include "common.h"
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    int fdSocket, msgsock, rval;

    struct sockaddr_in serverSocket, clientSocket, checkPort;
    socklen_t socklen = sizeof(serverSocket), len_client = sizeof(clientSocket);
    socklen_t checkPort_size = sizeof(checkPort);
    char header[4];
    in_port_t port = argc == 1 ? 0 : GetPortFromArguments(argv[1]);

    memset(&serverSocket, 0, socklen);

    serverSocket.sin_family = AF_INET;
    serverSocket.sin_port = htons(port);
    serverSocket.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    fdSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (fdSocket == -1)
    {
        perror("Error while creating a socket");
        return 1;
    }

    if (bind(fdSocket, (struct sockaddr *)&serverSocket, socklen) == -1)
    {
        perror("Bind error");
        return 1;
    }

    if (getsockname(fdSocket, (struct sockaddr *)&checkPort, &checkPort_size) == 0)
    {
        printf("TCP server listening on port %hu\n", ntohs(checkPort.sin_port));
        listen(fdSocket, 5);
    }
    else
    {
        perror("Getsockname error");
        close(fdSocket);
        exit(1);
    }

    while (1)
    {
        msgsock = accept(fdSocket, (struct sockaddr *)0, (socklen_t *)0);
        getpeername(msgsock, (struct sockaddr *)&clientSocket, &len_client);
        printf("Accepted connection with: %s:%d\n", inet_ntoa(clientSocket.sin_addr), ntohs(clientSocket.sin_port));
        if (msgsock == -1)
        {
            printf("Accept failed here\n");
            return 3;
        }
        if ((rval = read(msgsock, header, sizeof(header))) == -1)
        {
            printf("Connection lost\n");
            continue;
        }
        long text = convert_to_int(header);
        int i = 1;
        while (text > 0)
        {
            char msgBuffer[MAX_MESSAGE + 1] = {};
            if ((rval = read(msgsock, msgBuffer, MAX_MESSAGE)) == -1)
            {
                text = 0;
                printf("Connection lost\n");
                continue;
            }
            text -= MAX_MESSAGE;
            printf("%d-->%s\n", i++, msgBuffer);
            if (text <= 0)
            {
                char rcvBuffer[15] = "Received data";
                if (write(msgsock, rcvBuffer, sizeof rcvBuffer) == -1)
                    perror("Error while writing");
            }
        }
        printf("Ending connection\n");
        close(msgsock);
    }
    close(fdSocket);
    return 0;
}