#include "staff.h"
#include "monitory.h"
#include <pthread.h>

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define CYAN "\x1B[36m"
#define RESET "\x1B[0m"

float X = 4;


void *client_worse(){
    short prt = COMMON;
    float x;
    x = ((float)rand() / (float)RAND_MAX + 0.5) * X;
    while(1){
        enter(&m_orders);
        if(m_orders.buffer_size == CAPACITY){
            wait(&m_orders, &add_orders);
        }
        Order o;
        o.pri = prt;
        o.times = time(0);
        push_order(&o);
        m_orders.buffer_size++;
        printf(BLUE "Dodałem zamówienie %d\n" RESET, o.pri);
        show_orders();
        sygnal(&m_orders, &pop_orders);
        leave(&m_orders);
        sleep(x);
    };
    exit(0);
}

void *client_better(){
    short prt = PRT;
    float x;
    x = ((float)rand() / (float)RAND_MAX + 0.5) * X;
    while(1){
        enter(&m_orders);
        if(m_orders.buffer_size == CAPACITY){
            wait(&m_orders, &add_orders);
        }
        Order o;
        o.pri = prt;
        o.times = time(0);
        push_order(&o);
        m_orders.buffer_size++;
        printf(CYAN "Dodałem zamówienie %d\n" RESET, o.pri);
        show_orders();
        sygnal(&m_orders, &pop_orders);
        leave(&m_orders);
        sleep(x);
    };
    exit(0);
}

void *kurier(){
    while(1){
        enter(&m_warehouse);
        if(!m_warehouse.buffer_size){
            wait(&m_warehouse, &pop_things);
        }
        Thing t = pop_thing();
        m_warehouse.buffer_size--;
        printf("Kurier: Zabrano z magazynu ");
        switch (t.pri)
        {
        case 1:
            printf("%ld\n", time(0) - t.times);
            break;
        case 3:
            printf("%ld\n", time(0) - t.times);
            break;
        default:
            printf(RED "%ld\n" RESET, time(0) - t.times);
            break;
        }
        show_warehouse();
        sygnal(&m_warehouse, &add_things);
        leave(&m_warehouse);
        sleep(0.5);
    };
    exit(0);
}

void *prod(){
    while(1){
        enter(&tools);
        if(!tools.buffer_size){
            wait(&tools, &full_tools);
        }
        printf("Robol: Sprawdzam co wolne\n");
        short idx = check_free();
        tools.buffer_size--;
        leave(&tools);
        enter(&m_orders);
        if(!m_orders.buffer_size){
            wait(&m_orders, &pop_orders);
        }
        Order o = pop_order();
        m_orders.buffer_size--;
        switch(o.pri)
        {
        case COMMON:
            printf("Usunięto zamówienie %d\n", o.pri);
            break;
        case COMMON_PREMIUM:
            printf("Usunięto zamówienie %d\n", o.pri);
            break;
        default:
            printf(RED "Usunięto zamówienie %d\n" RESET, o.pri);
            break;
        }
        show_orders();
        sygnal(&m_orders, &add_orders);
        leave(&m_orders);
        sleep(1);
        enter(&tools);
        short timee = _unlock(idx);
        tools.buffer_size++;
        sygnal(&tools, &full_tools);
        leave(&tools);
        Thing t;
        t.pri = o.pri;
        t.times = o.times;
        enter(&m_table);
        if(m_table.buffer_size == 2){
            wait(&m_table, &add_table);
        }
        add_to_master(&t);
        m_table.buffer_size++;
        printf("Robol: Przekazano mistrzowi %d\n", t.pri);
        show_table();
        sygnal(&m_table, &pop_table);
        leave(&m_table);
        sleep(timee);
    };
    exit(0);
}

void *master(){
    while(1){
        enter(&m_table);
        if(!m_table.buffer_size){
            wait(&m_table, &pop_table);
        }
        Thing t = remake();
        m_table.buffer_size--;
        sygnal(&m_table, &add_table);
        leave(&m_table);
        float chance = (float)rand() / (float)RAND_MAX;
        sleep(0.5);
        if(chance > 0.1){
            enter(&tools);
            if(!tools.buffer_size){
                wait(&tools, &full_tools);
            }
            printf(GREEN "Mistrz: Sprawdzam co wolne\n" RESET);
            short idx = check_free();
            tools.buffer_size--;
            leave(&tools);
            sleep(1);
            enter(&tools);
            _unlock(idx);
            tools.buffer_size++;
            sygnal(&tools, &full_tools);
            leave(&tools);
            enter(&m_warehouse);
            if(m_warehouse.buffer_size == CAPACITY){
                wait(&m_warehouse, &add_things);
            }
            push_thing(&t);
            m_warehouse.buffer_size++;
            sygnal(&m_warehouse, &pop_things);
            leave(&m_warehouse);
            printf(GREEN "Mistrz: Przekazano do magazynu %d\n" RESET, t.pri);
        }
        else{
            Order o;
            if(o.pri < 3)
                o.pri = t.pri + 2;
            else{
                o.pri = t.pri;
            }
            o.times = time(0);
            enter(&m_orders);
            if(m_orders.buffer_size == CAPACITY){
                wait(&m_orders, &add_orders);
            }
            push_order(&o);
            m_orders.buffer_size++;
            sygnal(&m_orders, &pop_orders);
            leave(&m_orders);
            printf(GREEN "Mistrz: Wadliwe oddano\n" RESET);
        }
    }
    exit(0);
}

void *owner(){
    while(1){
        sleep(5);
        printf(YELLOW "Właściciel: Sprawdzam\n" RESET);
        enter(&m_orders);
        short bol = control(time(0));
        leave(&m_orders);
        if(bol){
            printf(YELLOW "Właściciel: Się odpalam\n" RESET);
        }
        while(bol){
            enter(&tools);
            if(!tools.buffer_size){
                wait(&tools, &full_tools);
            }
            short idx = check_free();
            tools.buffer_size--;
            leave(&tools);
            enter(&m_orders);
            if(!m_orders.buffer_size){
                wait(&m_orders, &pop_orders);
            }
            Order o = pop_order();
            m_orders.buffer_size--;
            sygnal(&m_orders, &add_orders);
            leave(&m_orders);
            sleep(2);
            enter(&tools);
            _unlock(idx);
            tools.buffer_size++;
            sygnal(&tools, &full_tools);
            leave(&tools);
            Thing t;
            t.pri = o.pri;
            t.times = o.times;
            enter(&m_warehouse);
            if(m_warehouse.buffer_size == CAPACITY){
                wait(&m_warehouse, &add_things);
            }
            push_thing(&t);
            m_warehouse.buffer_size++;
            printf(YELLOW "Właściciel: Dodałem do magazynu\n" RESET);
            sygnal(&m_warehouse, &pop_things);
            leave(&m_warehouse);
            if(time(0) - o.times < 20){
                bol = 0;
                printf(YELLOW "Właściciel: Kończę pracę\n" RESET);
            }
            else{
                sleep(1);
            }
        }
    };
    exit(0);
}

int main(){
    init_monitors();
    srand(0);
    pthread_t watki[8];
    pthread_create(&watki[0], NULL, owner, NULL);
    pthread_create(&watki[1], NULL, master, NULL);
    pthread_create(&watki[2], NULL, kurier, NULL);
    pthread_create(&watki[3], NULL, prod, NULL);
    pthread_create(&watki[4], NULL, prod, NULL);
    pthread_create(&watki[5], NULL, client_worse, NULL);
    pthread_create(&watki[6], NULL, client_worse, NULL);
    pthread_create(&watki[7], NULL, client_better, NULL);
    for(int i=0;i<8;i++){
        pthread_join(watki[i], (void**)NULL);
    }
    return 0;
}
