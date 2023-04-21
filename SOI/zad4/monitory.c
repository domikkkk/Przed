#include "monitory.h"
#include "definy.h"


Monitor tools;
Monitor m_orders;
Monitor m_warehouse;
Monitor m_table;

Cond full_tools;
Cond add_orders;
Cond pop_orders;
Cond add_things;
Cond pop_things;
Cond add_table;
Cond pop_table;


void init_monitors(){
    sem_init(&tools.s, 0 ,1);
    sem_init(&m_orders.s, 0, 1);
    sem_init(&m_warehouse.s, 0, 1);
    sem_init(&m_table.s, 0, 1);

    tools.buffer_size = 2;
    m_warehouse.buffer_size = 0;
    m_orders.buffer_size = 0;
    m_table.buffer_size = 0;

    tools.max_size = DEVICES;
    m_warehouse.max_size = CAPACITY;
    m_orders.max_size = CAPACITY;
    m_table.max_size = 2;

    add_orders.waiting_thread = 0;
    add_table.waiting_thread = 0;
    add_things.waiting_thread = 0;
    pop_orders.waiting_thread = 0;
    pop_table.waiting_thread = 0;
    pop_things.waiting_thread = 0;
    full_tools.waiting_thread = 0;

    sem_init(&full_tools.quard, 0, 0);
    sem_init(&add_orders.quard, 0, 0);
    sem_init(&add_table.quard, 0, 0);
    sem_init(&add_things.quard, 0, 0);
    sem_init(&pop_orders.quard, 0, 0);
    sem_init(&pop_table.quard, 0, 0);
    sem_init(&pop_things.quard, 0 ,0);
}

void enter(Monitor *m){
    sem_wait(&m->s);
}

void leave(Monitor *m){
    sem_post(&m->s);
}

void wait(Monitor *m, Cond *c){
    c->waiting_thread++;
    leave(m);
    sem_wait(&c->quard);
}

void sygnal(Monitor *m, Cond *c){
    if(c->waiting_thread){
        c->waiting_thread--;
        sem_post(&c->quard);
        enter(m);
    }
}