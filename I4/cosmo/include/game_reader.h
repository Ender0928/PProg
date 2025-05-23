/**
 * @brief It implements the game_reader module
 * 
 * @file game_reader.h
 * @author Javier and Rubén
 * @version 1.0
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"
#include "game_rules.h"

/**
  * @brief It loads the spaces
  * @author Profesores PPROG
  * @param game a pointer to the game
  * @param filename the name of the file
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status game_reader_load_spaces(Game *game, char *filename);

/**
  * @brief It loads the objects
  * @author Rubén
  * @param game a pointer to the game
  * @param filename the name of the file
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status game_reader_load_objects(Game *game, char *filename);

/**
  * @brief It loads the links
  * @author Rubén
  * @param game a pointer to the game
  * @param filename the name of the file
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status game_reader_load_links(Game *game, char *filename);

/**
  * @brief It loads the characters
  * @author Rubén
  * @param game a pointer to the game
  * @param filename the name of the file
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status game_reader_load_character(Game *game, char *filename);

/**
  * @brief It loads the players
  * @author Rubén
  * @param game a pointer to the game
  * @param filename the name of the file
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status game_reader_load_players(Game *game, char *filename);

Status game_reader_load_drop_rule(Game *game, char *filename);

Status game_reader_open_link_rule(Game *game, char *filename);

Status game_reader_load_heal_rule(Game *game, char *filename);

Status game_reader_load_craft_rule(Game *game, char *filename);

Status game_reader_add_objet_damage_rule(Game *game, char *filename);

Status game_reader_add_damage_enemy_rule(Game *game, char *filename);

Status game_reader_add_revival_object(Game *game, char *filename);
#endif