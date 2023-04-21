#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include "staff.h"
#include "semafory.h"
#include <time.h>

enum {SEGMENT_SIZE = 200};
enum {FULL_MAG, EMPTY_MAG, MUTEX_MAG, FULL_ZAM, EMPTY_ZAM, MUTEX_ZAM, FULL_URZ, EMPTY_URZ, MUTEX_URZ};

int semid;

void prod(Warehouse *w, Orders *o, Devices *d){
    pid_t pid = fork();
    if(pid != 0) return;
    while(1){
        P(semid, EMPTY_URZ, 1); // opuszczam empty dla urządzeń
        P(semid, MUTEX_URZ, 1); // blokuje mutex dla urządeń
        printf("Sprawdzam co jest wolne\n");
        int index = check_free(d); // sprawdzam wolne urządzenie
        V(semid, MUTEX_URZ, 1); // podnoszę mutex dla urządzeń
        V(semid, FULL_URZ, 1); // podnoszę fulla dla urządzeń
        P(semid, FULL_ZAM, 1); // opuszam fula dla zamówień
        P(semid, MUTEX_ZAM, 1); // opuszczam mutex zamówień
        short order = pop_from_orders(o); // biore zamówienie i usuwam z bufora
        printf("Usunięto zamówienie %d\n", order);
        V(semid, MUTEX_ZAM, 1); // podnoszę mutex zamówień
        V(semid, EMPTY_ZAM, 1); // podnoszę empty zamówień
        sleep(1); //zasypiam a tak naprawdę tworze rzecz
        P(semid, FULL_URZ, 1); // opuszczam fulla dla urządzeń
        P(semid, MUTEX_URZ, 1); // opuszczam mutex dla urządzeń
        int time = unlock(d, index);
        V(semid, MUTEX_URZ, 1); // podnoszę mutex dla urządzeń
        V(semid, EMPTY_URZ, 1); // podnoszę empty dla urządzeń
        P(semid, EMPTY_MAG, 1); // opuszczam empty dla magazynu
        P(semid, MUTEX_MAG, 1); //opuszczam mutex dla magazynu
        int x = push_to_warehouse(w, order);
        printf("Dodano do magazynu %d\n", order);
        V(semid, MUTEX_MAG, 1); // podnoszę mutex dla magazynu
        V(semid, FULL_MAG, 1); // podnoszę fulla dla magazynu
        sleep(time);
    };
    exit(0);
}

void take_staff(Warehouse *w){
    pid_t pid = fork();
    if(pid != 0) return;
    while(1){
        P(semid, FULL_MAG, 1); // opuszczam fulla magazynu
        P(semid, MUTEX_MAG, 1); // opuszczam mutex
        up_w(w);
        int x = pop_from_warehouse(w);
        printf("Zabrano z magazynu %ld\n", TIME);
        V(semid, MUTEX_MAG, 1); // podnoszę mutex
        V(semid, EMPTY_MAG, 1); // podnoszę empty dla magazynu
        sleep(0.5);
    };
    exit(0);
}

void client(Orders *o, bool is_premium, float X){
    pid_t pid = fork();
    if (pid != 0) return;
    short priority = is_premium? PRT : NPRT;
    while(1){
        P(semid, EMPTY_ZAM, 1); // opuszczam empty dla zamówień
        P(semid, MUTEX_ZAM, 1); // blokuje zamówienia
        int x = push_to_orders(o, priority);
        up_o(o);
        printf("Dodano zamówienie %d\n", priority);
        V(semid, MUTEX_ZAM, 1); // podnoszę mutex zamówień
        V(semid, FULL_ZAM, 1); // podnoszę full zamówień
        sleep(X); // ide spać
    };
    exit(0);
}

int main(int argc, char *argv[]) {
    int segment_id1, segment_id2, segment_id3;
    segment_id1 = shmget(IPC_PRIVATE, SEGMENT_SIZE,
                        IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

    Warehouse *warehouse = (Warehouse *) shmat(segment_id1, NULL, 0);
    _init_warehouse(warehouse);

    segment_id2 = shmget(IPC_PRIVATE, SEGMENT_SIZE,
                        IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

    Orders *orders = (Orders *) shmat(segment_id2, NULL, 0);
    _init_orders(orders);

    segment_id3 = shmget(IPC_PRIVATE, SEGMENT_SIZE,
                        IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    printf("%d %d %d\n", segment_id1, segment_id2, segment_id3);

    Devices *devices = (Devices *) shmat(segment_id3, NULL, 0);
    _init_devices(devices);

    srand(0);

    key_t semkey = 0;
    semid = sem_init(semkey);
    printf("%d\n", semid);
    V(semid, MUTEX_MAG, 1); // mutex dla magazynu
    V(semid, EMPTY_MAG, CAPACITY); // empty dla magazynu
    V(semid, MUTEX_ZAM, 1); // mutex dla zamówień
    V(semid, EMPTY_ZAM, CAPACITY); // empty dla zamówień
    V(semid, MUTEX_URZ, 1); // mutex dla urządzeń
    V(semid, EMPTY_URZ, DEVICES); // // empty dla urządzeń

    for(int i=0;i<1;i++){
        take_staff(warehouse);
    }
    for(int i=0;i<3;i++){
        prod(warehouse, orders, devices);
    }
    float X = 1;
    for(int i=0;i<2;i++){
        X = ((float)rand() / (float)RAND_MAX + 0.5) * X;
        client(orders, 0, X);
    }
    for(int i=0;i<1;i++){
        X = ((float)rand() / (float)RAND_MAX + 0.5) * X;
        client(orders, 1, X);
    }
    shmdt(warehouse);
    shmdt(orders);
    shmdt(devices);
    // semctl(semid, 0, IPC_RMID);
    exit(EXIT_SUCCESS);
}
