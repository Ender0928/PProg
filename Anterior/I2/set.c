/** 
 * @brief It implements the set module
 * 
 * @file player.c
 * @author Alfonso Crespo
 * @version 2.0 
 * @date 26-02-2022
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

struct _Set
{
    Id ids[MAX_ID]; /*array with the id of the objects in the set*/
    int n_ids; /*number of the objects of the set*/
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

STATUS set_destroy(Set* set){
    if(!set) return ERROR;

    free(set);
    return OK;
}

STATUS set_add_object(Set* set,Id id){
    int i=0;

    if(!set||id==NO_ID) return ERROR;

    for(i = 0;i<MAX_ID; i++){
        if(set->ids[i]==NO_ID){
            set->ids[i]=id;
            set->n_ids++;
            return OK;
        }
    }
    return ERROR;
}

STATUS set_del_object(Set* set,Id id){
    int i=0;

    if(!set||id==NO_ID) return ERROR;

    for(i=0;i<MAX_ID;i++){
        if(set->ids[i]==id){
            set->ids[i]=NO_ID;
            set->n_ids--;
            return OK;
        }
    }
    return ERROR;
}

STATUS set_print(Set* set){
    int i=0;
    if(!set) return ERROR;

    fprintf(stdout, "Number of objects of the Set: %d \n",set->n_ids);

    for(i=0;i<MAX_ID;i++){
        if(set->ids[i]!=NO_ID){
            fprintf(stdout, "Id: %ld\n",set->ids[i]);
        }
    }
    return OK;
}

BOOL set_find_object(Set* set,Id id){
    int i=0;
    if(!set||id==NO_ID) return FALSE;
    
    for(i=0;i<MAX_ID;i++){
        if(set->ids[i]==id){
            return TRUE;
        }    
    }
    return FALSE;
}

Id* set_get_pointer(Set* set){
    if(!set) return NULL;

    return set->ids;
}
