#ifndef INVENTORY_H
#define INVENTORY_H


#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"


typedef struct _Inventory Inventory;

Inventory* inventory_create();

STATUS inventory_destroy();

BOOL inventory_is_full(Inventory *inv);

STATUS inventory_add_object(Inventory* inv,Id obj);
STATUS inventory_del_object(Inventory* inv,Id obj);

#endif