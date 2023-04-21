#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "definy.h"
#include <stdlib.h>
#include <stdio.h>


int sem_init(key_t key);
void sem_call(int sem_id, int op, short id);
void P(int sem_id, short id, int n);
void V(int sem_id, short id, int n);
