#include "staff.h"


void _init_warehouse(Warehouse *w){
    for(int i=0;i<CAPACITY;i++){
        (*w+i)->prt = NOT_USE;
        (*w+i)->time = 0;
    }
}

int push_to_warehouse(Warehouse *w, short premium){
    if((*w+9)->prt != NOT_USE) return 9;
    if(premium == PRT){
        Rshift_warehouse(w);
        (*w)->prt = premium;
        (*w)->time = TIME2;
        return 0;
    }
    for(int i=0;i<CAPACITY;i++){
        if((*w+i)->prt == NOT_USE){
            (*w+i)->prt = premium;
            (*w+i)->time = TIME2;
            return i;
        }
    }
    return 9;
}

int pop_from_warehouse(Warehouse *w){
    if((*w)->prt == NOT_USE) return -1;
    short prt = (*w)->prt;
    TIME = (*w)->time;
    (*w)->time = 0;
    show_warehouse(w);
    Lshift_warehouse(w);
    return prt;
}

void Lshift_warehouse(Warehouse *w){
    for(int i=0; i<CAPACITY-1;i++){
        (*w+i)->prt = (*w+i+1)->prt;
    }
    (*w+9)->prt = NOT_USE;
}

void Rshift_warehouse(Warehouse *w){
    for(int i=CAPACITY - 1; i>0;i--){
        (*w+i)->prt = (*w+i-1)->prt;
    }
    (*w)->prt = NOT_USE;
}


void _init_orders(Orders *o){
    for(int i=0;i<CAPACITY;i++){
        (*o+i)->prt = 0;
        (*o+i)->time = 0;
    }
}

int push_to_orders(Orders *o, short premium){
    if((*o+9)->prt != NOT_USE) return 9;
    if(premium == PRT){
        Rshift_orders(o);
        (*o)->prt = premium;
        return 0;
    }
    for(int i=0;i<CAPACITY;i++){
        if((*o+i)->prt == NOT_USE){
            (*o+i)->prt = premium;
            return i;
        }
    }
    return 9;
}

short pop_from_orders(Orders *o){
    if((*o)->prt == NOT_USE) return -1;
    short x = (*o)->prt;
    TIME2 = (*o)->time;
    (*o)->time = 0;
    show_orders(o);
    Lshift_orders(o);
    return x;
}

void Lshift_orders(Orders *o){
    for(int i=0; i<CAPACITY-1;i++){
        (*o+i)->prt = (*o+i+1)->prt;
    }
    (*o+9)->prt = NOT_USE;
}

void Rshift_orders(Orders *o){
    for(int i=CAPACITY - 1; i>0;i--){
        (*o+i)->prt = (*o+i-1)->prt;
    }
    (*o)->prt = NOT_USE;
}

void _init_devices(Devices *d){
    (*d)->in_use = false;
    (*d)->type = A;
    (*d+1)->in_use = false;
    (*d+1)->type = B;
}

int check_free(Devices *d){
    for(int i=0;i<DEVICES;i++){
        if((*d+i)->in_use == 0){
            (*d+i)->in_use = true;
            return i;
        }
    }
    return -1;
}

short unlock(Devices *d, int index){
    (*d+index)->in_use  = false;
    return (*d+index)->type;
}

void show_orders(Orders *o){
    printf("Stan zamówień: ");
    for(int i=0;i<CAPACITY;i++){
        printf("%d ", (*o+i)->prt);
    }
    printf("\n");
}

void show_warehouse(Warehouse *w){
    printf("Stan magazynu: ");
    for(int i=0;i<CAPACITY;i++){
        printf("%d ", (*w+i)->prt);
    }
    printf("\n");
}

void up_w(Warehouse *w){
    for(int i=0;i<CAPACITY;i++){
        if((*w+i)->prt == NOT_USE) return;
        (*w+i)->time+=10;
    }
}

void up_o(Orders *o){
    for(int i=0;i<CAPACITY;i++){
        if((*o+i)->prt == NOT_USE) return;
        (*o+i)->time+=10;
    }
}