/** 
 * @brief It implements the player module
 * 
 * @file player.c
 * @author Daniel Tirado and Alfonso Crespo
 * @version 2.0 
 * @date 12-02-2022
 */
#include "player.h"
#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief Player
 *
 * This struct stores all the information of a player.
 */
struct _Player{
    Id id;                /*!< Id number of the player, it must be unique */ 
    char name[WORD_SIZE]; /*!< Name of the player*/
    Id location;          /*!< Id number of the location */
    Inventory* inv;       /*!< Inventory pointer */ 
    int health;           /*!< The health of the player */
};


/*player_create allocates memory for a new player and initializes its members*/
Player * player_create (Id id){ 
    Player *new_player = NULL;

    /*Error control*/
    if (id == NO_ID)
    {
        return NULL;
    }
    
    /* Initialization of an empty player*/
    new_player = (Player*)malloc(sizeof(Player));
        if (new_player==NULL)
        {
            return NULL;
        }

    new_player->id= id;
    new_player->location=NO_ID;
    new_player->inv=inventory_create();
    if(!(new_player->inv)) return NULL;

    new_player->name[0]='\0';
    new_player->health = 5;

    return new_player;
}

/*player_destroy frees the previous memory allocation 
  *  for a player*/
STATUS player_destroy (Player *player){ 
    if (!player)
    {
        return ERROR;
    }
    inventory_destroy(player->inv);

    free (player);
        return OK;
}

/*It gets the id of a player*/
Id player_get_id(Player *player){
    if (!player)
    {
        return NO_ID;
    }
    
return player->id;
}

/*It gets the name of the player*/
const char * player_get_name(Player *player){
    if (!player)
    {
        return NULL;
    }
    
return player->name;
}

/*It set the name of the player*/
STATUS player_set_name(Player *player, char *name){ 
    if (!player || !name)
    {
        return ERROR;
    }
    
    if (!strcpy(player->name, name)) {
    return ERROR;
  }
  return OK;
}

/*It get the player location*/
Id player_get_location(Player *player){ 
    if (!player){
        return NO_ID;
    }

return player->location;
}

/*It set the player location*/
STATUS player_set_location(Player *player, Id location){
    if (!player || location==NO_ID) {
        return ERROR;
    }
  player->location=location;

return OK;
}


BOOL player_find_object(Player* player,Id object){
    if(!player||object==NO_ID) return FALSE;

    return inventory_find_object(player->inv,object);
}


STATUS player_inv_add_object(Player *player,Id object){
    if(!player||object==NO_ID) return ERROR;


    return inventory_add_object(player->inv,object);
}

STATUS player_inv_del_object(Player *player,Id object){
    if(!player||object==NO_ID) return ERROR;


    return inventory_del_object(player->inv,object);
}


BOOL player_inv_isFull(Player* player){
    if(!player) return TRUE;

    return inventory_is_full(player->inv);
}

int player_get_health(Player *player) {
    if (!player)
        return -1;
    
    return player->health;
}

STATUS player_set_health(Player *player, int health) {
    if (!player||health<0)
        return ERROR;
    
    player->health = health;

    return OK;
}

STATUS player_set_MaxInv(Player* player,int MaxInv){
    if(!player||MaxInv<=0) return ERROR;

    return inventory_set_MaxInv(player->inv,MaxInv);
}

STATUS player_print(Player* player){
  if (!player)
    return ERROR;

  fprintf(stdout, "-->player (id: %ld; name: %s; location: %ld;)\n", player->id, player->name,player->location);
  inventory_print(player->inv);

  return OK;
}