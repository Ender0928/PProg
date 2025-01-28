/** 
 * @brief It implements the player module
 * 
 * @file player.c
 * @author Daniel Tirado
 * @version 2.0 
 * @date 12-02-2022
 */
 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enemy.h"



/**
 * @brief Enemy
 *
 * This struct stores all the information of an enemy.
 */
struct _Enemy {
    Id id;            /* Id number of the space, it must be unique */ 
    char name[TAM_E]; /*name of the player*/
    Id location;      /*Id number of the location, it must be unique*/
    int health;       /*the helth of the enemy*/
};


/*player_create allocates memory for a new player and initializes its members*/
Enemy * enemy_create (Id id) {
    Enemy *new_enemy = NULL;

    /*Error control*/
    if (id == NO_ID)
    {
        return NULL;
    }
    
    /* Initialization of an empty player*/
    new_enemy = (Enemy*)malloc(sizeof(Enemy));
        if (new_enemy==NULL)
        {
            return NULL;
        }

    new_enemy->id= id;
    new_enemy->location=NO_ID;
    new_enemy->name[0]='\0';
    new_enemy->health = 3;


    return new_enemy;
}

/*player_destroy frees the previous memory allocation 
  *  for a player*/
STATUS enemy_destroy (Enemy *enemy) { 
    if (!enemy)
    {
        return ERROR;
    }

    free (enemy);
        return OK;
}

/*It gets the id of a player*/
Id enemy_get_id(Enemy *enemy) {
    if (!enemy)
    {
        return NO_ID;
    }
    
return enemy->id;
}

/*It gets the name of the player*/
const char * enemy_get_name(Enemy *enemy) {
    if (!enemy)
    {
        return NULL;
    }
    
return enemy->name;
}

/*It set the name of the player*/
STATUS enemy_set_name(Enemy *enemy, char *name) { 
    if (!enemy || !name)
    {
        return ERROR;
    }
    
    if (!strcpy(enemy->name, name)) {
    return ERROR;
  }
  return OK;
}

/*It gets the player location*/
Id enemy_get_location(Enemy *enemy){ 
    if (!enemy){
        return NO_ID;
    }

return enemy->location;
}

/*It set the player location*/
STATUS enemy_set_location(Enemy *enemy, Id location) {
    if (!enemy || location==NO_ID) {
        return ERROR;
    }
  enemy->location=location;

return OK;
}

int enemy_get_health(Enemy *enemy) {
    if (!enemy)
        return -1;
    
    return enemy->health;
}

STATUS enemy_set_health(Enemy *enemy, int health) {
    if (!enemy)
        return ERROR;
    
    enemy->health = health;

    return OK;
}
