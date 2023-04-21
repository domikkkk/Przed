#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "definy.h"


typedef struct {
    short pri;
    time_t times;
} Orders[1];

typedef struct {
    short pri;
    time_t times;
} Order;

typedef struct {
    short pri;
    time_t times;
} Warehouse[1];

typedef struct {
    short pri;
    time_t times;
} Thing;

typedef struct {
    short type;
    bool in_use;
} Devices[1];

typedef struct {
    short pri;
    time_t times;
} Table[1];


extern Orders orders[CAPACITY];
extern Warehouse warehouse[CAPACITY];
extern Devices devices[DEVICES];
extern Table table[2];

void _init_devices();
short check_free();
short _unlock(short i);

void push_order(Order *o);
Order pop_order();
void Rshift_orders(int i);
void Lshift_orders();

void push_thing(Thing *t);
Thing pop_thing();
void Rshift_warehouse(int i);
void Lshift_warehouse();

void add_to_master(Thing *t);
Thing remake();

short control(time_t t);
Order take_order();

void show_orders();
void show_warehouse();
void show_table();