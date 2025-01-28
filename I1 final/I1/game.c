/** 
 * @brief It implements the game interface and all the associated calls
 * for each command
 * 
 * @file game.c
 * @author Profesores PPROG
 * @version 2.0 
 * @date 29-11-2021 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_reader.h"
/**
   Private functions
*/

/**
  * @brief It adds a new space
  * @author Profesores PPROG
  *
  * gameReader_add_space counts the existing spaces until it detects 
  * that one does not exist and adds it
  * 
  * @param  game a pointer to the game
  * @param  space a pointer to the space
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS game_add_space(Game *game, Space *space);

/**
  * @brief It gets the id of a space
  * @author Profesores PPROG
  * 
  * @param game a pointer to the game  
  * @param position an integrer with the position
  * @return the id of space
  */
Id game_get_space_id_at(Game *game, int position);

/**
  * @brief It sets the player location
  * @author Profesores PPROG
  * 
  * @param space a pointer to the game
  * @param id an id with the player location
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS game_set_player_location(Game *game, Id id);

/**
  * @brief It sets the object location
  * @author Profesores PPROG
  * @param space a pointer to the game
  * @param id an id with the object location
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS game_set_object_location(Game *game, Id id);

/**
  * @brief functions with the instructions for each command entered by the user
  * @author Profesores PPROG
  * @param space a pointer to the game
  * @return nothing 
  */
void game_command_unknown(Game *game);
void game_command_exit(Game *game);
void game_command_next(Game *game);
void game_command_back(Game *game);
void game_command_take(Game *game);
void game_command_drop(Game *game);

/**
   Game interface implementation
*/

/*initializes its members*/
STATUS game_create(Game *game)
{
  int i;

  for (i = 0; i < MAX_SPACES; i++)
  {
    game->spaces[i] = NULL;
  }

  game->player = player_create(P);
  game->object = object_create(O);
  game->last_cmd = NO_CMD;

  return OK;
}

/*sets the position of the player and the object*/
STATUS game_create_from_file(Game *game, char *filename)
{
  /*error handling*/
  if (game_create(game) == ERROR)
    return ERROR;

  if (game_reader_load_spaces(game, filename) == ERROR)
    return ERROR;

  /* The player and the object are located in the first space */
  game_set_player_location(game, game_get_space_id_at(game, 0));
  game_set_object_location(game, game_get_space_id_at(game, 0));

  return OK;
}

/*frees the memory of all spaces*/
STATUS game_destroy(Game *game)
{
  int i = 0;

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    space_destroy(game->spaces[i]);
  }

  return OK;
}

/** gameReader_add_space counts the existing spaces until it detects 
  * that one does not exist and adds it
  */
STATUS game_add_space(Game *game, Space *space)
{
  int i = 0;

  if (space == NULL)
  {
    return ERROR;
  }

  while (i < MAX_SPACES && game->spaces[i] != NULL)
  {
    i++;
  }

  if (i >= MAX_SPACES)
  {
    return ERROR;
  }

  game->spaces[i] = space;

  return OK;
}


/*It gets the id of a space*/
Id game_get_space_id_at(Game *game, int position)
{

  if (position < 0 || position >= MAX_SPACES)
  {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

/*gets the space according to the Id*/
Space *game_get_space(Game *game, Id id)
{
  int i = 0;

  if (id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    if (id == space_get_id(game->spaces[i]))
    {
      return game->spaces[i];
    }
  }

  return NULL;
}

/*sets the player location*/
STATUS game_set_player_location(Game *game, Id id) {

  if (id == NO_ID) 
    return ERROR;
  
  player_set_location(game->player, id);

  return OK;
}

/*gets the object location*/
STATUS game_set_object_location(Game *game, Id id) {
  int i;

  if (!game||id==NO_ID)
    return ERROR;

  for (i=0; game->spaces[i]; i++) {
    if (space_get_id(game->spaces[i]) == id){

      if (space_get_object(game->spaces[i]) != NO_ID) {
        player_set_object(game->player,object_get_id(game->object));
        space_set_object(game->spaces[i], NO_ID);
        return OK;   
      }

      else if (space_get_object(game->spaces[i]) == NO_ID) {
        space_set_object(game->spaces[i],object_get_id(game->object));
        player_set_object(game->player,NO_ID);
        return OK;
      }
    }
  }

  return ERROR;
}


/*gets the player location*/
Id game_get_player_location(Game *game) {
  return player_get_location(game->player);
}

/*gets the object location*/
Id game_get_object_location(Game* game) {
  int i;
  Id aux=NO_ID;

  if(!game)
    return NO_ID;

  for(i=0;game->spaces[i]!=NULL;i++){
    if(space_get_object(game->spaces[i])!=NO_ID){
      aux=space_get_id(game->spaces[i]);
      return aux;
    }
  }

 return aux;
}


/*calls one function or another according to the command entered*/
STATUS game_update(Game *game, T_Command cmd)
{
  game->last_cmd = cmd;
  
  switch (cmd)
  {
    case UNKNOWN:
      game_command_unknown(game);
      break;

    case EXIT:
      game_command_exit(game);
      break;

    case NEXT:
      game_command_next(game);
      break;

    case BACK:
      game_command_back(game);
      break;

    case TAKE:
      game_command_take(game);
      break;

    case DROP:
      game_command_drop(game);
      break;

    default:
      break;
  }

  return OK;
}

/*it gets the last command entered*/
T_Command game_get_last_command(Game *game)
{
  return game->last_cmd;
}

/*prints all the relevant data, object location, player location and all the spaces*/
void game_print_data(Game *game)
{
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    space_print(game->spaces[i]);
  }

  printf("=> Object location: %d\n", (int)game_get_object_location(game));
  printf("=> Player location: %d\n", (int)game_get_player_location(game));
}

BOOL game_is_over(Game *game)
{
  return FALSE;
}

/**
   Calls implementation for each action 
*/
void game_command_unknown(Game *game)
{
}

void game_command_exit(Game *game)
{
  
}

void game_command_next(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_south(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
      }
      return;
    }
  }
}

void game_command_back(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id)
  {
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_north(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
      }
      return;
    }
  }
}

void game_command_take(Game *game)
{
  int i=0;

  if(!game)
    return;

  for(i=0;game->spaces[i]!=NULL;i++){
    if(game_get_player_location(game)==space_get_id(game->spaces[i])){
      if(player_get_object(game->player)==NO_ID && space_get_object(game->spaces[i])!=NO_ID){
        game_set_object_location(game,space_get_id(game->spaces[i]));
        return;
      }
    }
  }

  return;
}

void game_command_drop(Game *game){
  int i=0;
  if(!game) return;

  for (i = 0; game->spaces[i]!=NULL; i++){
    if (game_get_player_location(game)==space_get_id(game->spaces[i])){
      if (player_get_object(game->player)!=NO_ID && space_get_object(game->spaces[i])==NO_ID){
        game_set_object_location(game,space_get_id(game->spaces[i]));
        return;
      }
    }
  }
  return;
}