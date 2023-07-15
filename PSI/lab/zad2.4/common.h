#ifndef COMMON_H
#define COMMON_H
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_MESSAGE 1000

in_port_t GetPortFromArguments(char *portStr);

long convert_to_int(char *header);

#endif
