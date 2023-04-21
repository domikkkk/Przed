#include "staff.h"

Orders orders[CAPACITY];
Warehouse warehouse[CAPACITY];
Devices devices[DEVICES];
Table table[2];
int Y = 10;

void _init_devices(){
    devices[0]->type = A;
    devices[0]->in_use = false;
    devices[1]->type = B;
    devices[1]->in_use = false;
}

short check_free(){
    for(short i=0;i<DEVICES;i++){
        if(!devices[i]->in_use){
            devices[i]->in_use = true;
            return i;
        }
    }
    return -1;
}

short _unlock(short i){
    devices[i]->in_use = false;
    return devices[i]->type;
}


void push_order(Order *o){
    short pri = o->pri;
    switch (pri)
    {
    case 1:
        for(int i=0;i<CAPACITY;i++){
            if(orders[i]->pri == NOT_USE){
                orders[i]->pri = pri;
                orders[i]->times = o->times;
                return;
            }
        }
        return;
    case 2:
        for(int i=0;i<CAPACITY;i++){
            if(orders[i]->pri < 2){
                Rshift_orders(i);
                orders[i]->pri = pri;
                orders[i]->times = o->times;
                return;
            }
        }
        return;
    default:
        Rshift_orders(0);
        orders[0]->pri = pri;
        orders[0]->times = o->times;
        return;
    }
}

void Rshift_orders(int i){
    for(int j=CAPACITY-1;j>i;j--){
        orders[j]->pri = orders[j-1]->pri;
        orders[j]->times = orders[j-1]->times;
    }
}

void Lshift_orders(){
    for(int i=0;i<CAPACITY-1;i++){
        orders[i]->pri = orders[i+1]->pri;
        orders[i]->times = orders[i+1]->times;
    }
    orders[9]->pri = NOT_USE;
    orders[9]->times = NOT_USE;
}

Order pop_order(){
    Order o;
    o.pri = orders[0]->pri;
    o.times = orders[0]->times;
    Lshift_orders();
    return o;
}

void push_thing(Thing *t){
    switch (t->pri)
    {
    case 1:
        for(int i=0;i<CAPACITY;i++){
               if(warehouse[i]->pri == 0){
                warehouse[i]->pri = t->pri;
                warehouse[i]->times = t->times;
                return;
            }
        }
        return;
    case 2:
        for(int i=0;i<CAPACITY;i++){
            if(warehouse[i]->pri < 2){
                Rshift_warehouse(i);
                warehouse[i]->pri = t->pri;
                warehouse[i]->times = t->times;
                return;
            }
        }
        return;
    default:
        Rshift_warehouse(0);
        warehouse[0]->pri = t->pri;
        warehouse[0]->times = t->times;
        return;
    }
}

Thing pop_thing(){
    Thing t;
    t.pri = warehouse[0]->pri;
    t.times = warehouse[0]->times;
    Lshift_warehouse();
    return t;
}

void Rshift_warehouse(int i){
    for(int j=CAPACITY-1;j>i;j--){
        warehouse[j]->pri = warehouse[j-1]->pri;
        warehouse[j]->times = warehouse[j-1]->times;
    }
}

void Lshift_warehouse(){
    for(int i=0;i<CAPACITY-1;i++){
        warehouse[i]->pri = warehouse[i+1]->pri;
        warehouse[i]->times = warehouse[i+1]->times;
    }
    warehouse[9]->pri = NOT_USE;
    warehouse[9]->times = NOT_USE;
}

void add_to_master(Thing *t){
    if(table[0]->pri != NOT_USE && table[1]->pri != NOT_USE){
        return;
    }
    else if (table[0]->pri == NOT_USE){
        table[0]->pri = t->pri;
        table[0]->times = t->times;
    }
    else if (table[1]->pri == NOT_USE){
        table[1]->pri = t->pri;
        table[1]->times = t->times;
    }
}

Thing remake(){
    short idx = table[0]->pri > table[1]->pri ? 0 : 1;
    Thing t;
    t.pri = table[idx]->pri;
    t.times = table[idx]->times;
    table[idx]->pri = NOT_USE;
    table[idx]->times = NOT_USE;
    return t;
}

short control(time_t t){
    return orders[0]->pri && t - orders[0]->times > Y? 1: 0;
}

void show_orders(){
    printf("Zamówienia: ");
    for(int i=0;i<CAPACITY;i++){
        printf("%d ", orders[i]->pri);
    }
    printf("\n");
}

void show_warehouse(){
    printf("Magazyn: ");
    for(int i=0;i<CAPACITY;i++){
        printf("%d ", warehouse[i]->pri);
    }
    printf("\n");
}

void show_table(){
    printf("Stół: %d %d\n", table[0]->pri, table[1]->pri);
}