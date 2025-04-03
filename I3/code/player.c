/** 
 * @brief It implements the player module
 * 
 * @file player.c
 * @author Javier and Rubén
 * @version 1.0 
 * @date 28-01-2025
 */


#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "space.h"


struct _Player{
    Id id;                  /* Id number of the space, it must be unique */ 
    char name[WORD_SIZE];   /*name of the player*/
    Id location;            /*Id number of the location, it must be unique*/
    int health;             /*Health points of the player*/
    Inventory *backpack;    /*Inventory of the player*/
    char gdesc[7];          /*Graphic description of the player*/
    Bool turn;              /*Turn of the player*/
    Space *Discorvered; /*Discovered spaces of the player*/
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
    new_player->name[0]='\0';
    new_player->health=3;
    new_player->gdesc[0] = '\0';
    new_player->backpack = inventory_create();
    new_player->turn = FALSE;
    if (new_player->backpack == NULL)
    {
        free(new_player);
        return NULL;
    }
    return new_player;
}

/*player_destroy frees the previous memory allocation 
    for a player*/
Status player_destroy (Player *player){ 
    if (!player)
    {
        return ERROR;
    }

    if (inventory_destroy(player->backpack) == ERROR)
    {
        return ERROR;
    }
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
Status player_set_name(Player *player, char *name){ 
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
Status player_set_location(Player *player, Id location){
    if (!player || location==NO_ID) {
        return ERROR;
    }
  player->location = location;

return OK;
}

/*It set the object of the player*/
Status player_add_object (Player *player, Id object){
    if (!player) {
        return ERROR;
    }

    inventory_add_object(player->backpack, object);
return OK;
}

Status player_remove_object(Player *player, Id object){
    if (!player || object == NO_ID)
    {
        return ERROR;
    }
    return inventory_remove_object(player->backpack, object);
}

/*It get the health of the player*/
int player_get_health(Player *player){
    if (!player){
        return ERROR;
    }

return player->health;
}

/*It set the health of the player*/
Status player_set_health(Player *player, int health){
    if (!player || health<0) {
        return ERROR;
    }
    player->health = health;
return OK;
}

Status player_set_backpack(Player *player, Inventory *backpack){
    if (!player || !backpack)
    {
        return ERROR;
    }
    player->backpack = backpack;
    return OK;
}

Inventory *player_get_backpack(Player *player){
    if (!player)
    {
        return NULL;
    }
    return player->backpack;
}

Status player_set_turn(Player *player, Bool turn){
    if (!player)
    {
        return ERROR;
    }
    player->turn = turn;
    return OK;
}

Bool player_get_turn(Player *player){
    if (!player)
    {
        return FALSE;
    }
    return player->turn;
}

Status player_set_max_objects(Player *player, int max_objects){
    if (!player || max_objects < 0)
    {
        return ERROR;
    }
    return inventory_set_max_value(player->backpack, max_objects);
}

Bool player_inventory_is_empty(Player *player){
    if (!player)
    {
        return TRUE;
    }
    return inventory_is_empty(player->backpack);
}

Bool player_inventory_is_full(Player *player){
    if (!player)
    {
        return TRUE;
    }
    return inventory_is_full(player->backpack);
}

Status player_has_object(Player *player, Id object){
    if (!player || object == NO_ID)
    {
        return ERROR;
    }
    return inventory_find_object(player->backpack, object);
}

Status player_set_graphic_desc(Player *player, char *gdesc) {
    if (!player || !gdesc)
        return ERROR;

    if (strlen(gdesc) >= 6)
        return ERROR;

    strcpy(player->gdesc, gdesc);
    return OK;
}

Status player_print(Player* player){
  if (!player)
    return ERROR;

  fprintf(stdout, "-->player (id: %ld; name: %s; location: %ld; health:%d;)\n", player->id, player->name,player->location, player->health);
  return OK;
}



