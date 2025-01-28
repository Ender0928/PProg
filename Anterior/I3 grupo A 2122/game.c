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
#include <time.h>

#include "game.h"
#include "game_reader.h"

/**
 * @brief Game
 *
 * This struct stores all the information of a game.
 */
struct _Game{
 Player *player; /*pointer to the player*/
  Object *object[MAX_OBJ]; /*an array with all the spaces*/
  Link *link[MAX_LINK];
  Space *spaces[MAX_SPACES]; /*an array with all the spaces */
  T_Command last_cmd; /*the last command entered*/
  char description[MAX_DESCR]; /*Auxiliary character string of the last inspection*/
  Enemy *enemy; /*pointer of the enemy*/
};
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
  * @brief functions with the instructions for each command entered by the user
  * @author Profesores PPROG
  * @param space a pointer to the game
  * @return nothing 
  */
void game_command_unknown(Game *game);
void game_command_next(Game* game);
void game_command_back(Game* game);
void game_command_move(Game* game);
DIRECTION game_command_get_dir();
void game_command_exit(Game *game);
void game_command_take(Game *game);
void game_command_drop(Game *game);
void game_command_attack(Game *game);
void game_command_inspect(Game* game);

/**
   Game interface implementation
*/

/*initializes its members*/
Game* game_create(Game* game)
{
  int i;

  game = (Game*) malloc(sizeof(Game));
  if(!game) return NULL;

  for (i = 0; i < MAX_SPACES; i++)
  {
    game->spaces[i] = NULL;
  }

  game->player = NULL;
  
  for(i=0;i<MAX_OBJ;i++){
    game->object[i]=NULL;
  }

  for(i=0;i<MAX_LINK;i++){
    game->link[i]=NULL;
  }
      
  game->last_cmd = NO_CMD;
  game->description[0] = '\0';
  game->enemy = NULL;

  return game;
}

/*sets the position of the player and the object*/
STATUS game_create_from_file(Game* game,char *filename)
{
  /*error handling*/

  if (game_reader_load_spaces(game, filename) == ERROR)
    return ERROR;

  if (game_reader_load_objects(game, filename) == ERROR)
      return ERROR;

  if (game_reader_load_player(game, filename)==ERROR){
    return ERROR;
  }

  if(game_reader_load_enemy(game,filename)==ERROR){
    return ERROR;
  }
  
  if(game_reader_load_links(game,filename)==ERROR){
    return ERROR;
  }

  

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

  for (i=0;i<MAX_OBJ;i++){
    object_destroy(game->object[i]);

  }

  for(i=0; i < MAX_LINK; i++){
    link_destroy(game->link[i]);
  }
  
  player_destroy(game->player);

  enemy_destroy(game->enemy);
  
  free(game);

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

  space_print(space);
  return OK;
}

STATUS game_add_link(Game *game, Link *link)
{
  int i = 0;

  if(!game||!link){
    return ERROR;
  }

  while (i < MAX_LINK && game->link[i] != NULL)
  {
    i++;
  }

  if (i >= MAX_LINK)
  {
    return ERROR;
  }

  game->link[i] = link;

  return OK;
}

STATUS game_add_player(Game* game, Player* player){
  if(!game||!player) return ERROR;
  game->player=player;
  return OK;
}

STATUS game_add_enemy(Game* game, Enemy* enemy){
  if(!game||!enemy) return ERROR;
  game->enemy=enemy;
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

/*add an object into a space*/
STATUS game_set_object_location(Game *game, Id space, Id object) {
  int i;

  if (!game||space==NO_ID||object==NO_ID) return ERROR;

  for (i=0;game->spaces[i]!=NULL;i++){
    if(space_get_id(game->spaces[i])==space){
      space_add_object(game->spaces[i],object);
      return OK;
    }  
  }
  return ERROR;
} 

/*add an object to the game*/
STATUS game_add_object(Game* game, Object* object){
  int i=0;

  if(!game || !object) return ERROR;

  while (game->object[i]!=NULL){
    i++;
  }

  if(i>=MAX_OBJ) return ERROR;

  game->object[i]=object;
  object_print(object);

  return OK;
}

/*get a pointer to an object*/
Object* game_get_object(Game* game, int pos){
  if(!game||pos<0||pos>=MAX_OBJ) return NULL;

  return game->object[pos];
}


/*gets the player location*/
Id game_get_player_location(Game *game) {
  return player_get_location(game->player);
}

Player* game_get_player(Game* game){
  if(!game){
    return 0;
  }

  return game->player;
}
Id game_get_object_id(Game *game, char *name)
{
    int i;
    
    if(!game || !name)
        return NO_ID;
    
    for(i=0;i<MAX_OBJ; i++) {
        if(strcmp(object_get_name(game->object[i]), name) == 0)
            return object_get_id(game->object[i]);
    }
    return NO_ID;
}

/*gets the object location*/
Id game_get_object_location(Game* game,Id id) {
  int i,j;
  Id aux=NO_ID;

  if(!game || id==NO_ID) return NO_ID;

  for(i=0;i<MAX_OBJ;i++){
    if(object_get_id(game->object[i])==id){
      break;
    }
  }

  for(j=0;j<MAX_SPACES;j++){
    if(space_find_object(game->spaces[j],object_get_id(game->object[i]))==TRUE){
      aux=space_get_id(game->spaces[j]);
      return aux;
    }
  }

  return aux;
}

BOOL game_inventory_find_object(Game* game, Id id){
  if(!game||id==NO_ID) return FALSE;

  return player_find_object(game->player,id);
}


/*calls one function or another according to the command entered*/
STATUS game_update(Game *game, T_Command cmd)
{
  game->last_cmd = cmd;
  game_clean_descr(game);
  
  
  switch (cmd)
  {
    case UNKNOWN:
      game_command_unknown(game);
      break;

    case EXIT:
      game_command_exit(game);
      break;

    case MOVE:
      game_command_move(game);
      break;

    case TAKE:
      game_command_take(game);
      break;

    case DROP:
      game_command_drop(game);
      break;
    
    case ATTACK:
      game_command_attack(game);
      break;

    case INSPECT:
      game_command_inspect(game);
      break;

    default:
      break;
  }

  return OK;
}

STATUS game_clean_descr(Game* game){
  int i=0;

for(i=0;i<MAX_DESCR;i++){
    game->description[i]= '\0';

  }
  return OK;
}

STATUS game_set_player_MaxInv(Game* game,int MaxInv){
  if(!game||MaxInv<=0) return ERROR;

  return player_set_MaxInv(game->player,MaxInv);
}

STATUS game_set_player_name(Player *player, char* name){
  if(player_set_name(player, name)==ERROR){
    return ERROR;
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

  for(i=0;i < MAX_OBJ;i++){
    printf("Object: %d location: %d\n",i+1,(int)game_get_object_location(game,object_get_id(game->object[i])));

  }


  printf("=> Player location: %d\n", (int)game_get_player_location(game));
  printf("=> Enemy location:  %d\n", (int)game_get_enemy_location(game));
}

/*finish the game*/
BOOL game_is_over(Game *game){
  if (game_get_player_health(game) <= 0)
    return TRUE;

  return FALSE;

}

/*gets the enemy location*/
Id game_get_enemy_location(Game *game){
  if(!game) return NO_ID;

  return enemy_get_location(game->enemy);
}

/*sets the enemy location*/
STATUS game_set_enemy_location(Game *game,Id id){
  if(!game || id==NO_ID) return ERROR;

  enemy_set_location(game->enemy,id);
  
  return OK;
}

/*gets the pointer of the enemy*/
Enemy* game_get_enemy(Game* game){
  return game->enemy;
}

/*gets the health of the enemy*/
int game_get_enemy_health(Game *game) {
  if (!game)
    return 0;
  
  return enemy_get_health(game->enemy);
}

/*sets the enemy health*/
STATUS game_set_enemy_health(Game *game, int health) {
  if (!game||health<0)
    return ERROR;
  
  enemy_set_health(game->enemy, health);

  return OK;
}

STATUS game_set_enemy_name(Game* game, char* name){
  if(!game||!name) return ERROR;

  return enemy_set_name(game->enemy,name);
}

/*gets the player of the health*/
int game_get_player_health(Game *game) {
  if (!game)
    return 0;
  
  return player_get_health(game->player);
}

/*sets the health of the player*/
STATUS game_set_player_health(Game *game, int health) {
  if (!game||health<0)
    return ERROR;
  
  player_set_health(game->player, health);

  return OK;
}

STATUS game_get_connection_status(Game* game, Id space, DIRECTION dir){
  int i;

  if(!game||space==NO_ID||dir==NO_DIRECTION) return 1;

  for(i=0;i<MAX_LINK;i++){
    if(space==link_get_origin(game->link[i])){
      if(dir==link_get_direction(game->link[i])){
        return link_get_status(game->link[i]);

      }
    }
  }
  return 1;
}


Id game_get_connection(Game* game, Id space, DIRECTION dir){
  int i;

  if(!game||space==NO_ID||dir==NO_DIRECTION) return NO_ID;

  for(i=0;i<MAX_LINK;i++){
    if(space==link_get_origin(game->link[i])){
      if(dir==link_get_direction(game->link[i])){
        return link_get_destination(game->link[i]);

      }
    }
  }
  return NO_ID;
}

void game_unlock_link(Game* game){
  int i;

  if(!game) return;

  for(i=0; i<MAX_LINK&&game->link[i]!=NULL ;i++){
    if(link_get_id(game->link[i])==306){
      link_set_status(game->link[i],0);
      return;

    }
  }  
  

return;
}

char* game_get_descr(Game* game){
  if(!game) return NULL;

  return game->description; 

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

/*go ahead*/
void game_command_move(Game *game){
  DIRECTION dir;

  if(!game) return;



  dir=game_command_get_dir();
  if(dir<0) return;

  if(game_get_connection_status(game,game_get_player_location(game),dir)==ERROR){
    game_set_player_location(game,game_get_connection(game,game_get_player_location(game),dir));
  }

  return;
}


/*take an item*/
void game_command_take(Game *game){
  int i;
  Id id;
  char name[WORD_SIZE];

  if(!game) return;

  printf("introduce el nombre del objeto\n");
  scanf("%s", name);

  id = game_get_object_id(game, name);

  for(i=0;i<MAX_SPACES;i++){
    if(game_get_player_location(game)==space_get_id(game->spaces[i])){
      if(player_inv_isFull(game->player)==FALSE && space_find_object(game->spaces[i],id)==TRUE){
        player_inv_add_object(game->player,id);
        space_del_object(game->spaces[i],id);
      
        return;

      }
    }
  }
  return;
}

/*drop an item*/
void game_command_drop(Game *game){
  
  int i;
  Id id;
  char name[WORD_SIZE];
  printf("introduce el nombre del objecto\n");
  scanf("%s",name);

  if(!game) return;

  id = game_get_object_id(game, name);

  for(i=0;i<MAX_SPACES;i++){
    if(game_get_player_location(game)==space_get_id(game->spaces[i])){
      if(player_find_object(game->player,id)==TRUE){
        space_add_object(game->spaces[i],id);
        player_inv_del_object(game->player,id);
        return;

      }
    }
  }
  return;
  
}

/*attack the enemy*/
void game_command_attack(Game *game) {
  int n, h_en, h_pl;

  srand(time(NULL));
  n = rand() % 10;
  h_en = game_get_enemy_health(game);
  h_pl = game_get_player_health(game);

  if(game_get_enemy_health(game)==0) return;


  if (game_get_player_location(game) == game_get_enemy_location(game)) {
    

    if (game_is_over(game) == TRUE)
      return;
    

    if (n>=0 && n<5) {
      h_pl--;

      if (game_set_player_health(game, h_pl) == ERROR)
        game_is_over(game);

    }

    else{
      h_en--;
      if (game_set_enemy_health(game, h_en) == ERROR)
        game_is_over(game);
      if(h_en==0) game_unlock_link(game);
    
    }
  }
}

DIRECTION game_command_get_dir(){
  char imput[100];


  printf("introduce la direccion que quieras (n, s, e, w) o (north, south, east, west): \n");

  scanf("%s",imput);

  if(!strcmp(imput,"n")||!strcmp(imput,"north"))
    return N;
  
  if(!strcmp(imput,"s")||!strcmp(imput,"south"))
    return S;

  if(!strcmp(imput,"e")||!strcmp(imput,"east"))
    return E;
  
  if(!strcmp(imput,"w")||!strcmp(imput,"west"))
    return W;


  return -1;
}

void game_command_inspect(Game *game){
  int i;
  char arg[MAX_DESCR];
  Id id;
  if(!game) return;

  printf("¿Que buscas inspeccionar?\n");
  scanf("%s", arg);

  /*Para space*/
  if(!strcmp(arg,"space")){
    for(i=0;i<MAX_SPACES;i++){
      if(game_get_player_location(game)==space_get_id(game->spaces[i])){
        strcpy(game->description, space_get_description(game->spaces[i]));
        return;
      }
    }
  }

  else{
    id = atol(arg);

    /*Para los objetos del space en el set*/
    for(i=0;i<MAX_SPACES;i++){
      if(game_get_player_location(game)==space_get_id(game->spaces[i])){
        if(space_find_object(game->spaces[i],id)==TRUE){
          for(i=0;i<MAX_OBJ;i++){
            if(object_get_id(game_get_object(game, i)) == id){
              strcpy(game->description, object_get_description(game_get_object(game, i)));
              return;
            }
          }
        }
      }
    }

    /*Para los objetos del inventory*/
    if(player_find_object(game->player, id)==TRUE){
      for(i=0;i<MAX_OBJ;i++){
        if(object_get_id(game_get_object(game, i)) == id){
          strcpy(game->description, object_get_description(game_get_object(game, i)));
          return;
        }
      }
    }

  }

  return;
}