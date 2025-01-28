#include "inventory.h"


struct _Inventory{
    Set* set_obj;
    int max_obj;
};

Inventory* inventory_create(){
    Inventory* inv = NULL;
    int i;

    inv = (Inventory*) malloc(sizeof(Inventory));
    if(!inv) return NULL;

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
    int i,num=0;

    for(i=0;i<MAX_OBJ;i++){
        if(inv->set_obj)
    }


}

STATUS inventory_add_object(Inventory* inv,Id obj){
    if(!inv||obj==NO_ID) return ERROR;


}

