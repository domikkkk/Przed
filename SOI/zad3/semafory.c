#include "semafory.h"


int sem_init(key_t key){
    int sem_id;
    if((sem_id = semget(key, 9, 0666 | IPC_CREAT)) == -1) perror("sem_init");
    return sem_id;
}

void sem_call(int sem_id, int op, short id){
    /*jedna operacja op na semaforze o numerze id w zestawie*/
    struct sembuf sb;

    sb.sem_num = id;
    sb.sem_op = op;
    sb.sem_flg = 0;
    if(semop(sem_id, &sb, 1) == -1) perror("semop w sem_call");
}

void P(int sem_id, short id, int n){
    sem_call(sem_id, -n, id);
}

void V(int sem_id, short id, int n){
    sem_call(sem_id, n, id);
}