#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/ipc.h>


int main(int argc, char *argv[]){
    int segmentid1 = atoi(argv[1]);
    int segmentid2 = atoi(argv[2]);
    int segmentid3 = atoi(argv[3]);
    int semid = atoi(argv[4]);
    semctl(semid, 0, IPC_RMID);
    shmctl(segmentid1, 0, IPC_RMID);
    shmctl(segmentid2, 0, IPC_RMID);
    shmctl(segmentid3, 0, IPC_RMID);
}