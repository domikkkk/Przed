// Tomasz Sroka
// Laboratorium PSI Zadanie 1
// 03.04.2023

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

in_port_t GetPortFromArguments(char *portStr)
{
	long convert = strtol(portStr, 0, 0);
	if (convert > 65535)
	{
		fprintf(stderr, "Port too big: %ld>65535", convert);
		exit(1);
	}
	if (convert < 0)
	{
		fprintf(stderr, "Port must be positive");
		exit(1);
	}
	return (in_port_t)convert;
}