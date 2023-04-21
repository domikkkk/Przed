#include "definy.h"
#include <stdbool.h>
#include <time.h>
#include <stdio.h>


typedef struct{
    time_t time;
    short int prt;   //0 if not use, 1 if in use, 2 if in use and priority
} Orders[1];


typedef struct{
    time_t time;
    short int prt;  //0 if not use, 1 if in use, 2 if in use and priority
} Warehouse[1];


typedef struct{
    short int type;
    bool in_use;
} Devices[1];

long TIME, TIME2;

void _init_warehouse(Warehouse *w);
int push_to_warehouse(Warehouse *w, short premium);
int pop_from_warehouse(Warehouse *w);
void Lshift_warehouse(Warehouse *w);
void Rshift_warehouse(Warehouse *w);

void _init_orders(Orders *o);
int push_to_orders(Orders *o, short premium);
short pop_from_orders(Orders *o);
void Lshift_orders(Orders *o);
void Rshift_orders(Orders *o);

void _init_devices(Devices *d);
int check_free(Devices *d);
short unlock(Devices *d, int index);

void show_orders(Orders *o);
void show_warehouse(Warehouse *w);

void up_w(Warehouse *w);
void up_o(Orders *o);