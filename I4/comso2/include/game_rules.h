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

Status gamerules_add_open_link_with_object_rule(GameRules *rules, Id obj, Id link_id);

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

Id gamerules_get_character_id_drop(GameRules *rules, int index);
Id gamerules_get_object_id_drop(GameRules *rules, int index);
Bool gamerules_get_triggered_drop(GameRules *rules, int index);

Id gamerules_get_link_id_open_link(GameRules *rules, int index);
Bool gamerules_get_triggered_open_link(GameRules *rules, int index);

Id gamerules_get_object_id_heal(GameRules *rules, int index);
int gamerules_get_heal_amount(GameRules *rules, int index);
Bool gamerules_get_triggered_heal(GameRules *rules, int index);

Id gamerules_get_object_id_craft_1(GameRules *rules, int index);
Id gamerules_get_object_id_craft_2(GameRules *rules, int index);
Id gamerules_get_result_object_craft(GameRules *rules, int index);
Bool gamerules_get_triggered_craft(GameRules *rules, int index);
Bool gamerules_get_requested_craft(GameRules *rules, int index);

Id gamerules_get_object_id_damage(GameRules *rules, int index);
int gamerules_get_extra_damage_object(GameRules *rules, int index);

Id gamerules_get_character_id_enemy(GameRules *rules, int index);
int gamerules_get_extra_damage_enemy(GameRules *rules, int index);

Id gamerules_get_object_id_revival(GameRules *rules, int index);
Bool gamerules_get_triggered_revival(GameRules *rules, int index);

Id gamerules_get_link_character_id_open_link(GameRules *rules, int index);

int gamerules_get_num_drop_rules(GameRules *rules);
int gamerules_get_num_open_links(GameRules *rules);
int gamerules_get_num_heal_rules(GameRules *rules);
int gamerules_get_num_craft_rules(GameRules *rules);
int gamerules_get_num_object_damage_rules(GameRules *rules);
int gamerules_get_num_enemy_damage_rules(GameRules *rules);
int gamerules_get_num_revival_rules(GameRules *rules);
#endif
