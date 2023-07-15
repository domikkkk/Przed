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


long convert_to_int(char *header){
	int len = 4;
	long out=0;
	for(int i=0;i<len;i++){
		out  *= 10;
		out += header[i];
	}
	return out;
}