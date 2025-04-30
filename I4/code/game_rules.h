#ifndef GAMERULES_H
#define GAMERULES_H

#include "game.h"

typedef struct _CraftRule CraftRule;
GameRules *gamerules_create();

void gamerules_destroy(GameRules *rules);

/**
 * @brief Ejecuta reglas automáticas sobre el juego
 * @param rules módulo de reglas
 * @param game el juego actual
 * @param command_count número total de comandos ejecutados
 */
void gamerules_run(Game *game);

Status gamerules_add_drop_rule(GameRules *rules, Id character_id, Id object_id);

Status gamerules_add_open_link_on_death_rule(GameRules *rules, Id character_id, Id link_id);

Status gamerules_add_heal_on_pickup(GameRules *rules, Id object_id, int heal_amount);

Status gamerules_add_craft_rule(GameRules *rules, Id obj1, Id obj2, Id result_obj);

int gamerules_get_craft_rules_by_name(Game *game, GameRules *rules, const char *name, CraftRule **results);

Status gamerules_set_requested(CraftRule *rule, Bool value);

Status gamerules_add_object_damage_rule(GameRules *rules, Id object_id, int extra_damage);

int gamerules_get_extra_damage_from_objects(Game *game);

int gamerules_add_enemy_damage_rule(GameRules *rules, Id character_id, int extra_damage);

int gamerules_get_extra_damage_from_enemy(Game *game, Id character_id);

Status gamerules_add_revival_object(GameRules *rules, Id object_id);

Bool gamerules_check_revival_object(Game *game, GameRules *rules);

#endif
