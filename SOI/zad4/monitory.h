#include <semaphore.h>


typedef struct{
    sem_t s;
    int buffer_size;
    int max_size;
    char *n;
} Monitor;

typedef struct{
    sem_t quard;
    int waiting_thread;
} Cond;


extern Monitor tools;
extern Monitor m_warehouse;
extern Monitor m_orders;
extern Monitor m_table;

extern Cond add_orders;
extern Cond pop_orders;
extern Cond add_things;
extern Cond pop_things;
extern Cond add_table;
extern Cond pop_table;
extern Cond full_tools;

void init_monitors();

void enter(Monitor *m);
void leave(Monitor *m);
void wait(Monitor *m, Cond *c);
void sygnal(Monitor *m, Cond *c);


