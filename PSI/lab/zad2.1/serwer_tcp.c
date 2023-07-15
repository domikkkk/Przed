#include <netinet/in.h>
#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include "common.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
    int fdSocket, msgsock, rval;
    struct sockaddr_in serverSocket, checkPort;
    socklen_t socklen = sizeof(serverSocket);
    socklen_t checkPort_size = sizeof(checkPort);
    char msgBuffer[MAX_MESSAGE+1]; //for null terminator
    int readFlag = 1;
    in_port_t port = argc == 1 ? 0 : GetPortFromArguments(argv[1]);
    memset(&serverSocket, 0, socklen);
    serverSocket.sin_family = AF_INET;
    serverSocket.sin_port = htons(port);
    serverSocket.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    fdSocket = socket(AF_INET,SOCK_STREAM,0);

    if (fdSocket == -1)
    {
        perror("Error while creating a socket");
        return 1;
    }


    if (bind(fdSocket, (struct sockaddr*) &serverSocket,socklen) == -1)
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
        msgsock = accept(fdSocket,(struct sockaddr *) 0, (socklen_t *) 0);
        printf("accepted");
        if (msgsock == -1)
        {
            printf("Accept failed here");
            return 3;
        }
        memset(msgBuffer, 0, sizeof msgBuffer);
        while (readFlag)
        {
            if ((rval = read(msgsock,msgBuffer, MAX_MESSAGE+1)) == -1)
            {
                perror("reading stream message");
                return 4;
            }
            if (rval == 0)
                printf("Ending connection\n");
            else
            {
                printf("-->%s\n", msgBuffer);
                char rcvBuffer[15] = "Received data";
                if (write(msgsock, rcvBuffer, sizeof rcvBuffer) == -1) perror("Error while writing");
            }
            readFlag = rval;
        }
        close(msgsock);
        readFlag = 1;
    }
    close(fdSocket);
    return 0;
}