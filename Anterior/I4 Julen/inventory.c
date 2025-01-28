/** 
 * @brief It implements the inventory module
 * 
 * @file inventory.c
 * @author Alfonso Crespo
 * @version 2.0 
 * @date 22-03-2021 
 * @copyright GNU Public License
 */

#include "inventory.h"
#include "set.h"

/**
 * @brief Inventory
 *
 * This struct stores all the information of an inventory.
 */
struct _Inventory{
    Set* set_obj; /*!< Set with all of the ids*/
    int max_obj;  /*!< Max num of objects a player can carry*/
};

Inventory* inventory_create(){
    Inventory* inv = NULL;

    inv = (Inventory*) malloc(sizeof(Inventory));
    if(!inv) return NULL;

    inv->max_obj=2;
    inv->set_obj = set_create();
    if(!(inv->set_obj)){
        free(inv);
        return NULL;
    }

    return inv;
}

STATUS inventory_destroy(Inventory* inv){
    if(!inv) return ERROR;

    if(set_destroy(inv->set_obj)==ERROR) return ERROR;

    free(inv);

    return OK;
}

BOOL inventory_is_full(Inventory *inv){
    if(!inv) return TRUE;

    if(set_get_num_of_ids(inv->set_obj)>=(inv->max_obj)||set_get_num_of_ids(inv->set_obj)<=-1) return TRUE;


    return FALSE;
}

STATUS inventory_add_object(Inventory* inv,Id obj){
    if(!inv||obj==NO_ID) return ERROR;
    if(inventory_is_full(inv)==TRUE) return ERROR;

    if(set_add_object(inv->set_obj,obj)==ERROR) return ERROR;

    return OK;
}

STATUS inventory_del_object(Inventory* inv, Id obj){
    if(!inv||obj==NO_ID) return ERROR;

    if(inventory_find_object(inv,obj)==FALSE) return OK;
    
    set_del_object(inv->set_obj,obj);

    return OK;
}

BOOL inventory_find_object(Inventory* inv,Id obj){
    BOOL bol=FALSE;
    if(!inv||obj==NO_ID) return FALSE;

    bol=set_find_object(inv->set_obj,obj);


    return bol;
}

STATUS inventory_set_MaxInv(Inventory* inv, int MaxInv){
    if(!inv||MaxInv<=0) return ERROR;

    inv->max_obj=MaxInv;
    
    return OK;
}

int inventory_get_MaxInv(Inventory *inv){
    if(!inv) return NO_ID;

    return inv->max_obj;
}

Id* inventory_get_set_pointer(Inventory* inv){
    if(!inv) return NULL;

    return set_get_pointer(inv->set_obj);
}

STATUS inventory_print(Inventory* inv){
    if(!inv) return ERROR;

    printf("capacity:%d\n",inv->max_obj);
    set_print(inv->set_obj);

    return OK;
}
