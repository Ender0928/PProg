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



struct _Player{
    Id id; /* Id number of the space, it must be unique */ 
    char name[WORD_SIZE]; /*name of the player*/
    Id location; /*Id number of the location, it must be unique*/
    Id object; /*Id number of the object, it must be unique*/    
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
    new_player->object=NO_ID;
    new_player->name[0]='\0';


    return new_player;
}

/*player_destroy frees the previous memory allocation 
    for a player*/
Status player_destroy (Player *player){ 
    if (!player)
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

/*It get the id of the object*/
Id player_get_object(Player *player){
    if (!player){
        return NO_ID;
    }

return player->object;
}

/*It set the object of the player*/
Status player_set_object (Player *player, Id object){
    if (!player || object==NO_ID) {
        return ERROR;
    }

    player->object = object;
return OK;
}

Status player_print(Player* player){
  if (!player)
    return ERROR;

  fprintf(stdout, "-->player (id: %ld; name: %s; location: %ld; object: %ld)\n", player->id, player->name,player->location,player->object);
  return OK;
}



