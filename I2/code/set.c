/** 
 * @brief It implements the set module
 * 
 * @file set.c
 * @author Javier Pérez
 * @version 2.0 
 * @date 23-02-2025
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

struct _Set
{
    Id ids[MAX_ID]; /*array with the id of the objects in the set*/
    int n_ids;      /*number of the objects of the set*/
};

Set* set_create(){
    Set *set;
    int i=0;

    set=(Set *)malloc(sizeof(Set));
    if (!set) return NULL;

    set->n_ids=0;
    for(i=0;i<MAX_ID;i++){
        set->ids[i]=NO_ID;
    }

    return set;
}

Status set_destroy(Set* set){
    if(!set) return ERROR;

    free(set);
    return OK;
}

Status set_add_object(Set* set,Id id){

    if(!set||id==NO_ID) return ERROR;

    set->ids[set->n_ids] = id;
    set->n_ids++;
    
    return OK;
}

int set_size(Set *set) {
    if (!set) {
        return -1;
    }
    return set->n_ids;
}

Status set_remove_object(Set* set, Id id) {
    int i, j;

    if (!set || id == NO_ID) return ERROR;

    for (i = 0; i < set->n_ids; i++) {
        if (set->ids[i] == id) {
            /* Move all elements one position to the left */
            for (j = i; j < set->n_ids - 1; j++) {
                set->ids[j] = set->ids[j + 1];
            }
            set->ids[set->n_ids - 1] = NO_ID;
            set->n_ids--;
            return OK;
        }
    }
    return ERROR;
}

Status set_print(Set* set) {
    int i;
    if (!set) return ERROR;

    fprintf(stdout, "Number of objects in the Set: %d\n", set->n_ids);

    for (i = 0; i < set->n_ids; i++) {
        fprintf(stdout, "Id: %ld\n", set->ids[i]);
    }
    return OK;
}


Bool set_find_object(Set* set,Id id){
    int i=0;
    if(!set||id==NO_ID) return FALSE;
    
    for(i=0; i < set->n_ids; i++){
        if(set->ids[i]==id){
            return TRUE;
        }    
    }
    return FALSE;
}

Id* set_get_ids(Set* set){
    if(!set) return NULL;

    return set->ids;
}