// Tomasz Sroka
// Laboratorium PSI Zadanie 1
// 30.03.2023

#ifndef COMMON_H
#define COMMON_H

#include <netinet/in.h>

#define MAX_MESSAGE 32
#define UDP_PORT 10022

in_port_t GetPortFromArguments(char *portStr);

#endif