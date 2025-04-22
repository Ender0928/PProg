/** 
 * @brief It implements the inventory module
 * 
 * @file inventory.c
 * @author Javier Pérez
 * @version 1.0 
 * @copyright GNU Public License
 */

#include "inventory.h"
#include "set.h"

/**
 * @brief Inventory structure
 *
 * This struct stores all the information of an inventory.
 */
struct _Inventory{
    Set* set_obj;       /*set with all of the ids*/
    int max_objs;       /*max num of objects a player can carry*/
};

Inventory* inventory_create(){
    Inventory* inv = NULL;

    inv = (Inventory*) malloc(sizeof(Inventory));
    if(!inv) return NULL;

    inv->max_objs = MAX_INVENTORY;
    inv->set_obj = set_create();
    if(!(inv->set_obj)){
        free(inv);
        return NULL;
    }

    return inv;
}

Status inventory_destroy(Inventory* inv){
    if(!inv){
        return ERROR;
    }
    
        if (inv->set_obj) { 
            if (set_destroy(inv->set_obj) == ERROR) 
                return ERROR;
        }

    free(inv);

    return OK;
}

Bool inventory_is_full(Inventory *inv){
    if(!inv) 
        return TRUE;

    if(set_size(inv->set_obj) >= (inv->max_objs) || set_size(inv->set_obj) <= -1) 
        return TRUE;

    return FALSE;
    
}

Bool inventory_is_empty(Inventory *inv){
    if(!inv) 
        return TRUE;

    if(set_size(inv->set_obj) == 0) 
        return TRUE;

    return FALSE;
}

Status inventory_add_object(Inventory* inv, Id obj){
    if(!inv || obj==NO_ID) 
        return ERROR;
    
    if(inventory_is_full(inv)) 
        return ERROR;

    return set_add_object(inv->set_obj,obj);
}

Status inventory_remove_object(Inventory* inv, Id obj){
    if(!inv || obj == NO_ID) 
        return ERROR;

    if(inventory_find_object(inv,obj)==FALSE) 
        return OK;
    
    return set_remove_object(inv->set_obj,obj);
}

Bool inventory_find_object(Inventory* inv, Id obj){
    if(!inv || obj == NO_ID) 
        return FALSE;

    return set_find_object(inv->set_obj, obj);
}

Status inventory_set_max_value(Inventory* inv, int maxValue){
    if(!inv || maxValue<=0) 
        return ERROR;

    inv->max_objs = maxValue;
    
    return OK;
}

int inventory_get_max_value(Inventory* inv){
    if(!inv) 
        return -1;

    return inv->max_objs;
}

Status inventory_print(Inventory* inv){
    if(!inv) return ERROR;

    printf("capacity:%d\n",inv->max_objs);
    set_print(inv->set_obj);

    return OK;
}
