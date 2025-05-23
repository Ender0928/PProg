/**
 * @file game_management.c
 * @brief Game management functions for loading and saving game state.
 *
 * This file contains functions to load and save the game state, including spaces, objects, characters, and players.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/game_management.h"

#define GCHAR_WIDTH (GDESC_COLS - 1)
#define GDESC_FORMAT "%-*s"

Status game_management_save(Game *game, char *filename)
{
    FILE *file = NULL;
    Space *space = NULL;
    Object *obj = NULL;
    Link *link = NULL;
    Character *ch = NULL;
    Player *p = NULL;
    int i, j;

    if (!filename || !game)
        return ERROR;

    file = fopen(filename, "w");
    if (!file)
        return ERROR;

    for (i = 0; i < game_get_n_spaces(game); i++)
    {
        space = game_get_space_by_index(game, i);
        if (space)
        {
            fprintf(file, "#s:%ld|%s", space_get_id(space), space_get_name(space));
            for (j = 0; j < GDESC_ROWS; j++)
            {
                char *row = space_get_gdesc(space)[j];
                fprintf(file, "|" GDESC_FORMAT, GCHAR_WIDTH, row ? row : "");
            }
            fprintf(file, "|\n");
        }
    }

    for (i = 0; i < game_get_n_objects(game); i++)
    {
        obj = game_get_object_by_index(game, i);
        if (obj)
        {
            fprintf(file, "#o:%ld|%s|%ld|%s|%d|%d|%ld|%ld|\n",
                    object_get_id(obj),
                    object_get_name(obj),
                    game_get_object_location(game, object_get_id(obj)),
                    object_get_description(obj),
                    object_get_health(obj),
                    object_get_movable(obj) ? 1 : 0,
                    object_get_dependency(obj),
                    object_get_open(obj));
        }
    }

    for (i = 0; i < game_get_n_links(game); i++)
    {
        link = game_get_link_by_index(game, i);
        if (link)
        {
            fprintf(file, "#l:%ld|%s|%ld|%ld|%d|%d|\n",
                    link_get_id(link),
                    link_get_name(link),
                    link_get_origin(link),
                    link_get_destination(link),
                    link_get_direction(link),
                    link_is_open(link) ? 1 : 0);
        }
    }

    for (i = 0; i < game_get_n_characters(game); i++)
    {
        ch = game_get_character_by_index(game, i);
        if (ch)
        {
            fprintf(file, "#c:%ld|%s|%s|%ld|%d|%d|%s|%s\n",
                    character_get_id(ch),
                    character_get_name(ch),
                    character_get_gdesc(ch),
                    character_get_location(ch),
                    character_get_health(ch),
                    character_is_friendly(ch) ? 1 : 0,
                    character_get_message(ch),
                    character_get_all_gdesc_battle(ch));
        }
    }

    for (i = 0; i < game_get_n_players(game); i++)
    {
        p = game_get_player_by_index(game, i);
        if (p)
        {
            fprintf(file, "#p:%ld|%s|%s|%ld|%d|%d|%s|\n",
                    player_get_id(p),
                    player_get_name(p),
                    player_get_graphic_desc(p),
                    player_get_location(p),
                    player_get_health(p),
                    player_get_max_objects(p),
                    player_get_all_gdesc_battle(p));
        }
    }
    
    for (i = 0; i < gamerules_get_num_drop_rules(game_get_rules(game)); i++)
    {
        fprintf(file, "#rd:%ld|%ld|\n",
                gamerules_get_character_id_drop(game_get_rules(game), i),
                gamerules_get_object_id_drop(game_get_rules(game), i));
            }
    for (i = 0; i < gamerules_get_num_open_links(game_get_rules(game)); i++)
    {
        fprintf(file, "#rl:%ld|%ld|\n",
                gamerules_get_link_character_id_open_link(game_get_rules(game), i),
                gamerules_get_link_id_open_link(game_get_rules(game), i));
            }
    for (i = 0; i < gamerules_get_num_heal_rules(game_get_rules(game)); i++)
    {
        fprintf(file, "#rh:%ld|%d|\n",
                gamerules_get_object_id_heal(game_get_rules(game), i),
                gamerules_get_heal_amount(game_get_rules(game), i));
    }
    for (i = 0; i < gamerules_get_num_craft_rules(game_get_rules(game)); i++)
    {
        fprintf(file, "#rc:%ld|%ld|%ld|\n",
                gamerules_get_object_id_craft_1(game_get_rules(game), i),
                gamerules_get_object_id_craft_2(game_get_rules(game), i),
                gamerules_get_result_object_craft(game_get_rules(game), i));
    }
    for (i = 0; i < gamerules_get_num_object_damage_rules(game_get_rules(game)); i++)
    {
        fprintf(file, "#ro:%ld|%d|\n",
                gamerules_get_object_id_damage(game_get_rules(game), i),
                gamerules_get_extra_damage_object(game_get_rules(game), i));
    }
    for (i = 0; i < gamerules_get_num_enemy_damage_rules(game_get_rules(game)); i++)
    {
        fprintf(file, "#re:%ld|%d|\n",
                gamerules_get_character_id_enemy(game_get_rules(game), i),
                gamerules_get_extra_damage_enemy(game_get_rules(game), i));
    }
    for (i = 0; i < gamerules_get_num_revival_rules(game_get_rules(game)); i++)
    {
        fprintf(file, "#rr:%ld|\n",
                gamerules_get_object_id_revival(game_get_rules(game), i));
    }
    
    fclose(file);
    return OK;
}

Status game_management_load(Game *game, char *filename)
{
    if (!game || !filename)
        return ERROR;

    if (game_reader_load_spaces(game, filename) == ERROR)
        return ERROR;
    if (game_reader_load_objects(game, filename) == ERROR)
        return ERROR;
    if (game_reader_load_links(game, filename) == ERROR)
        return ERROR;
    if (game_reader_load_character(game, filename) == ERROR)
        return ERROR;
    if (game_reader_load_players(game, filename) == ERROR)
        return ERROR;
    if (game_reader_load_drop_rule(game, filename) == ERROR)
        return ERROR;
    if (game_reader_open_link_rule(game, filename) == ERROR)
        return ERROR;
    if (game_reader_load_heal_rule(game, filename) == ERROR)
        return ERROR;
    if (game_reader_load_craft_rule(game, filename) == ERROR)
        return ERROR;
    if (game_reader_add_objet_damage_rule(game, filename) == ERROR)
        return ERROR;
    if (game_reader_add_damage_enemy_rule(game, filename) == ERROR)
        return ERROR;
    if (game_reader_add_revival_object(game, filename) == ERROR)
        return ERROR;

    return OK;
}
