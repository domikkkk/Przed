// Tomasz Sroka
// Laboratorium PSI Zadanie 1
// 30.03.2023

#ifndef COMMON_H
#define COMMON_H
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_MESSAGE 32

in_port_t GetPortFromArguments(char *portStr);

#endif