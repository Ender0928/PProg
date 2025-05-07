#include "../include/game_rules.h"
#include "../include/character.h"
#include "../include/player.h"
#include "../include/object.h"
#include "../include/link.h"

#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>

typedef struct {
    Id character_id;
    Id object_id;
    Bool triggered;
} DropRule;

typedef struct {
    Id character_id;
    Id link_id;
    bool triggered;
} OpenLinkOnDeathRule;

typedef struct {
    Id object_id;
    Id link_id;
    bool triggered;
} OpenLinkWithObjectRule;

typedef struct {
    Id object_id;
    int heal_amount;
    bool triggered;
} HealOnPickupRule;

struct _CraftRule{
    Id object_id_1;
    Id object_id_2;
    Id result_object;
    bool triggered;
    bool requested;
} ;

typedef struct {
    Id object_id;
    int extra_damage;
} DamageBoostObjectRule;

typedef struct {
    Id character_id;
    int extra_damage;
} EnemyDamageRule;

typedef struct {
    Id object_id;
    Bool triggered;
} RevivalRule;



struct _GameRules{
    DropRule drop_rules[MAX_DROP_RULES];
    int num_rules;

    OpenLinkOnDeathRule links_rules[MAX_OPEN_LINKS];
    int num_open_links;

    HealOnPickupRule health_objects[MAX_HEALTH_OBJECTS];
    int num_heal_rules;

    CraftRule craft_rules[MAX_CRAFTS_RULES];
    int num_crafts_rules;

    DamageBoostObjectRule object_damage_rules[MAX_DAMAGE_OBJECT_RULES];
    int num_object_damage_rules;

    EnemyDamageRule enemy_damage_rules[MAX_ENEMY_DAMAGE_RULES];
    int num_enemy_damage_rules;

    RevivalRule revival_rules[MAX_REVIVAL_OBJECTS];
    int num_revival_rules;

    OpenLinkWithObjectRule open_link_with_object_rules[MAX_OPEN_LINKS];
    int num_open_link_with_object_rules;

};

GameRules *gamerules_create() {
    GameRules *rules = malloc(sizeof(GameRules));
    if (!rules) return NULL;

    rules->num_rules = 0;
    rules->num_open_links = 0;
    rules->num_heal_rules = 0;
    rules->num_crafts_rules = 0;
    rules->num_object_damage_rules = 0;
    rules->num_enemy_damage_rules = 0;
    rules->num_revival_rules = 0;
    rules->num_open_link_with_object_rules = 0;
    return rules;
}

void gamerules_destroy(GameRules *rules) {
    if (!rules) return;

    free(rules);
}

/**
 * @brief Añade una nueva regla de soltar objeto al morir un personaje
 * 
 * @param rules Puntero a GameRules
 * @param character_id ID del personaje al que se asocia
 * @param object_id ID del objeto que soltará
 * @return Status OK si se añade correctamente, ERROR en caso contrario
 */
Status gamerules_add_drop_rule(GameRules *rules, Id character_id, Id object_id) {
    if (!rules || character_id == NO_ID || object_id == NO_ID || rules->num_rules >= MAX_DROP_RULES) {
        return ERROR;
    }

    rules->drop_rules[rules->num_rules].character_id = character_id;
    rules->drop_rules[rules->num_rules].object_id = object_id;
    rules->drop_rules[rules->num_rules].triggered = FALSE;
    rules->num_rules++;

    return OK;
}

/**
 * @brief Asocia un objeto para que sea dejado cuando un personaje muera.
 * Esta función se puede llamar desde gamerules_run u otro sistema de reglas.
 * @param game puntero al juego
 * @param character_id ID del personaje a observar
 * @param object_id ID del objeto a soltar al morir
 * @return Status OK si todo fue bien, ERROR en caso contrario
 */
Status gamerules_drop_object_on_death(Game *game, Id character_id, Id object_id) {
    Character *character = NULL;
    Id location = NO_ID;
    if (!game || character_id == NO_ID || object_id == NO_ID)
        return ERROR;


    character = game_get_character(game, character_id);
    if (!character) return ERROR;

    location = character_get_location(character);
    /* Si el personaje está muerto y el objeto no tiene ubicación definida*/
    if (character_is_dead(character) && location != NO_ID) {
        if(game_set_object_location(game, object_id, location) == OK ) {
            space_remove_object(game_get_space(game, (Id)ID_SPACE_OBJECTS), object_id);
            return OK;
        } else {
            return FALSE;
        }
    }

    return ERROR;
}

Status gamerules_add_open_link_on_death_rule(GameRules *rules, Id character_id, Id link_id) {

    if (!rules || character_id == NO_ID || link_id == NO_ID || rules->num_open_links >= MAX_OPEN_LINKS)
        return ERROR;

    rules->links_rules[rules->num_open_links].character_id = character_id;
    rules->links_rules[rules->num_open_links].link_id = link_id;
    rules->links_rules[rules->num_open_links].triggered = FALSE;
    rules->num_open_links++;

    return OK;
}

Status gamerules_add_open_link_with_object_rule(GameRules *rules, Id obj, Id link_id) {

    if (!rules || obj == NO_ID || link_id == NO_ID || rules->num_open_links >= MAX_OPEN_LINKS)
        return ERROR;

    rules->open_link_with_object_rules[rules->num_open_link_with_object_rules].object_id= obj;
    rules->open_link_with_object_rules[rules->num_open_link_with_object_rules].link_id = link_id;
    rules->open_link_with_object_rules[rules->num_open_link_with_object_rules].triggered = FALSE;
    rules->num_open_link_with_object_rules++;

    return OK;
}

Status gamerules_add_heal_on_pickup(GameRules *rules, Id object_id, int heal_amount) {
    if (!rules || object_id == NO_ID || rules->num_heal_rules >= MAX_HEALTH_OBJECTS) return ERROR;

    rules->health_objects[rules->num_heal_rules].object_id = object_id;
    rules->health_objects[rules->num_heal_rules].heal_amount = heal_amount;
    rules->health_objects[rules->num_heal_rules].triggered = FALSE;
    rules->num_heal_rules++;

    return OK;
}

/**
 * @brief Añade una nueva regla de crafteo con dos objetos que crean uno nuevo
 * 
 * @param rules Puntero a GameRules
 * @param obj1 Primer objeto requerido
 * @param obj2 Segundo objeto requerido
 * @param result_obj Objeto resultante al craftear
 * @return Status OK si se añade correctamente, ERROR si hay error
 */
Status gamerules_add_craft_rule(GameRules *rules, Id obj1, Id obj2, Id result_obj) {
    if (!rules || obj1 == NO_ID || obj2 == NO_ID || result_obj == NO_ID || rules->num_crafts_rules >= MAX_CRAFTS_RULES)
        return ERROR;

    rules->craft_rules[rules->num_crafts_rules].object_id_1 = obj1;
    rules->craft_rules[rules->num_crafts_rules].object_id_2 = obj2;
    rules->craft_rules[rules->num_crafts_rules].result_object = result_obj;
    rules->craft_rules[rules->num_crafts_rules].triggered = false;
    rules->craft_rules[rules->num_crafts_rules].requested = false;
    rules->num_crafts_rules++;

    return OK;
}

int gamerules_get_craft_rules_by_name(Game *game, GameRules *rules, const char *name, CraftRule **results) {
    int i, found = 0;

    if (!game || !rules || !name || !results) return 0;

    for (i = 0; i < rules->num_crafts_rules; i++) {
        Object *res = game_get_object(game, rules->craft_rules[i].result_object);
        if (res && strcasecmp(object_get_name(res), name) == 0) {
            if (found < MAX_CRAFTS_RULES) {
                results[found++] = &rules->craft_rules[i];
            }
        }
    }

    return found;
}

Status gamerules_set_requested(CraftRule *rule, Bool value) {
    if (!rule) return ERROR;

    rule->requested = value;
    return OK;
}

Status gamerules_add_object_damage_rule(GameRules *rules, Id object_id, int extra_damage) {
    if (!rules || object_id == NO_ID || rules->num_object_damage_rules >= MAX_DAMAGE_OBJECT_RULES)
        return ERROR;

    rules->object_damage_rules[rules->num_object_damage_rules].object_id = object_id;
    rules->object_damage_rules[rules->num_object_damage_rules].extra_damage = extra_damage;
    rules->num_object_damage_rules++;

    return OK;
}

int gamerules_get_extra_damage_from_objects(Game *game) {
    GameRules *rules;
    int i, extra = 0;

    if (!game) return -1;
    rules = game_get_rules(game);
    if (!rules) return -1;

    for (i = 0; i < rules->num_object_damage_rules; i++) {
        if (player_has_object(game_get_player(game), rules->object_damage_rules[i].object_id)) {
            extra += rules->object_damage_rules[i].extra_damage;
        }
    }

    return extra;
}

int gamerules_add_enemy_damage_rule(GameRules *rules, Id character_id, int extra_damage) {
    if (!rules || character_id == NO_ID || extra_damage <= 0 || rules->num_enemy_damage_rules >= MAX_ENEMY_DAMAGE_RULES) {
        return ERROR;
    }

    rules->enemy_damage_rules[rules->num_enemy_damage_rules].character_id = character_id;
    rules->enemy_damage_rules[rules->num_enemy_damage_rules].extra_damage = extra_damage;
    rules->num_enemy_damage_rules++;

    return OK;
}

int gamerules_get_extra_damage_from_enemy(Game *game, Id character_id) {
    GameRules *rules;
    int i;

    if (!game || character_id == NO_ID) return 0;

    rules = game_get_rules(game);
    if (!rules) return 0;

    for (i = 0; i < rules->num_enemy_damage_rules; i++) {
        if (rules->enemy_damage_rules[i].character_id == character_id) {
            return rules->enemy_damage_rules[i].extra_damage;
        }
    }

    return 0;
}

Status gamerules_add_revival_object(GameRules *rules, Id object_id) {
    if (!rules || object_id == NO_ID || rules->num_revival_rules >= MAX_REVIVAL_OBJECTS) {
        return ERROR;
    }

    rules->revival_rules[rules->num_revival_rules].object_id = object_id;
    rules->revival_rules[rules->num_revival_rules].triggered = FALSE;
    rules->num_revival_rules++;

    return OK;
}

Bool gamerules_check_revival_object(Game *game, GameRules *rules) {
    int i;
    if (!rules) return FALSE;

    for (i = 0; i < rules->num_revival_rules; i++) {
        if (player_has_object(game_get_player(game), rules->revival_rules[i].object_id) &&
            rules->revival_rules[i].triggered == FALSE) {
                rules->revival_rules[i].triggered = TRUE;
            return TRUE;
        }
    }

    return FALSE;
}

void gamerules_run(Game *game) {
    GameRules *rules;
    DropRule *d_rule;
    int i, new_health;

    if (!game) return;

    rules = game_get_rules(game);
    if (!rules) return;

    /*Drop on dead rules*/
    for (i = 0; i < rules->num_rules; i++) {
        d_rule = &rules->drop_rules[i];

        if (!d_rule->triggered) {
            if (gamerules_drop_object_on_death(game, d_rule->character_id, d_rule->object_id) == OK) {
                d_rule->triggered = true;
            }
        }
    }
    
    /*Open links by death rules*/
    for (i = 0; i < rules->num_open_links; i++) {
        Link *link = NULL;
        OpenLinkOnDeathRule *rule = &rules->links_rules[i];
        Character *character = game_get_character(game, rule->character_id);

        if (!rule->triggered && character && character_is_dead(character)) {
            link = game_get_link(game, rule->link_id);
            if (link) {
                link_set_open(link, true);
                rule->triggered = true;
            }
        }
    }

      
    /*Open links with objects rules*/
    for (i = 0; i < rules->num_open_link_with_object_rules; i++) {
        Link *link = NULL;
        OpenLinkWithObjectRule *rule = &rules->open_link_with_object_rules[i];
        Object *obj = game_get_object(game, rule->object_id);

        if (!rule->triggered && obj && player_has_object(game_get_player(game), rule->object_id)) {
            link = game_get_link(game, rule->link_id);
            if (link) {
                link_set_open(link, true);
                rule->triggered = true;
            }
        }
    }



    /*Health objects rules*/
    for (i = 0; i < rules->num_heal_rules; i++) {
        HealOnPickupRule *r = &rules->health_objects[i];
    
        if (!r->triggered && player_has_object(game_get_player(game), r->object_id)) {
            new_health = game_get_player_health(game) + r->heal_amount;
            game_set_player_health(game, new_health);
            r->triggered = true;
        } else if (r->triggered && !player_has_object(game_get_player(game), r->object_id)) {
            new_health = game_get_player_health(game) - r->heal_amount;
            game_set_player_health(game, new_health);
            r->triggered = false;
        }
    }
    
    /* Crafting rules */
    for (i = 0; i < rules->num_crafts_rules; i++) {
        CraftRule *r = &rules->craft_rules[i];
    
        if (!r->triggered && r->requested &&
            player_has_object(game_get_player(game), r->object_id_1) &&
            player_has_object(game_get_player(game), r->object_id_2)) {
            
            /* Elimina los materiales del jugador*/
            player_remove_object(game_get_player(game), r->object_id_1);
            player_remove_object(game_get_player(game), r->object_id_2);
    
            /* Añade el objeto resultante al jugador*/
            player_add_object(game_get_player(game), r->result_object);
    
            /* Elimina el objeto del espacio 10*/
            space_remove_object(game_get_space(game, (Id)ID_SPACE_OBJECTS), r->result_object);

            /* Añade el objeto resultante al espacio de objetos*/
            space_add_object(game_get_space(game, (Id)ID_SPACE_OBJECTS), r->object_id_1);
            space_add_object(game_get_space(game, (Id)ID_SPACE_OBJECTS), r->object_id_2);
    
            /* Marca la regla como ejecutada*/
            r->triggered = true;
            r->requested = false;
        } else {
            r->requested = FALSE;
        }
    }
    

    /* Regla 2: Ataque automático si enemigo y jugador están en el mismo espacio*/
    /*int i;
    for (i = 0; i < game_get_num_characters(game); i++) {
        Character *c = game_get_character(game, i);
        if (c && !character_is_friendly(c) && character_get_health(c) > 0 &&
            character_get_location(c) == game_get_player_location(game)) {
            Player *p = game_get_player(game);
            player_set_health(p, player_get_health(p) - 1);
        }
    }*/

    /* Regla 3: Personaje aliado que sigue al jugador*/
    /*for (i = 0; i < game_get_num_characters(game); i++) {
        Character *c = game_get_character(game, i);
        if (c && character_is_friendly(c) &&
            character_get_follow(c) == game_get_player_id(game)) {
            character_set_location(c, game_get_player_location(game));
        }
    }*/
}

//Getters
Id gamerules_get_character_id_drop(GameRules *rules, int index) {
    if (!rules || index < 0 || index >= rules->num_rules) return NO_ID;
    return rules->drop_rules[index].character_id;
}

Id gamerules_get_object_id_drop(GameRules *rules, int index) {
    if (!rules || index < 0 || index >= rules->num_rules) return NO_ID;
    return rules->drop_rules[index].object_id;
}

Bool gamerules_get_triggered_drop(GameRules *rules, int index) {
    if (!rules || index < 0 || index >= rules->num_rules) return FALSE;
    return rules->drop_rules[index].triggered;
}

Id gamerules_get_link_character_id_open_link(GameRules *rules, int index) {
    if (!rules || index < 0 || index >= rules->num_open_links) return NO_ID;
    return rules->links_rules[index].character_id;
}

Id gamerules_get_link_id_open_link(GameRules *rules, int index) {
    if (!rules || index < 0 || index >= rules->num_open_links) return NO_ID;
    return rules->links_rules[index].link_id;
}

Bool gamerules_get_triggered_open_link(GameRules *rules, int index) {
    if (!rules || index < 0 || index >= rules->num_open_links) return FALSE;
    return rules->links_rules[index].triggered;
}

Id gamerules_get_object_id_heal(GameRules *rules, int index) {
    if (!rules || index < 0 || index >= rules->num_heal_rules) return NO_ID;
    return rules->health_objects[index].object_id;
}

int gamerules_get_heal_amount(GameRules *rules, int index) {
    if (!rules || index < 0 || index >= rules->num_heal_rules) return 0;
    return rules->health_objects[index].heal_amount;
}

Bool gamerules_get_triggered_heal(GameRules *rules, int index) {
    if (!rules || index < 0 || index >= rules->num_heal_rules) return FALSE;
    return rules->health_objects[index].triggered;
}

Id gamerules_get_object_id_craft_1(GameRules *rules, int index) {
    if (!rules || index < 0 || index >= rules->num_crafts_rules) return NO_ID;
    return rules->craft_rules[index].object_id_1;
}

Id gamerules_get_object_id_craft_2(GameRules *rules, int index) {
    if (!rules || index < 0 || index >= rules->num_crafts_rules) return NO_ID;
    return rules->craft_rules[index].object_id_2;
}

Id gamerules_get_result_object_craft(GameRules *rules, int index) {
    if (!rules || index < 0 || index >= rules->num_crafts_rules) return NO_ID;
    return rules->craft_rules[index].result_object;
}

Bool gamerules_get_triggered_craft(GameRules *rules, int index) {
    if (!rules || index < 0 || index >= rules->num_crafts_rules) return FALSE;
    return rules->craft_rules[index].triggered;
}

Bool gamerules_get_requested_craft(GameRules *rules, int index) {
    if (!rules || index < 0 || index >= rules->num_crafts_rules) return FALSE;
    return rules->craft_rules[index].requested;
}

Id gamerules_get_object_id_damage(GameRules *rules, int index) {
    if (!rules || index < 0 || index >= rules->num_object_damage_rules) return NO_ID;
    return rules->object_damage_rules[index].object_id;
}

int gamerules_get_extra_damage_object(GameRules *rules, int index) {
    if (!rules || index < 0 || index >= rules->num_object_damage_rules) return 0;
    return rules->object_damage_rules[index].extra_damage;
}

Id gamerules_get_character_id_enemy(GameRules *rules, int index) {
    if (!rules || index < 0 || index >= rules->num_enemy_damage_rules) return NO_ID;
    return rules->enemy_damage_rules[index].character_id;
}

int gamerules_get_extra_damage_enemy(GameRules *rules, int index) {
    if (!rules || index < 0 || index >= rules->num_enemy_damage_rules) return 0;
    return rules->enemy_damage_rules[index].extra_damage;
}

Id gamerules_get_object_id_revival(GameRules *rules, int index) {
    if (!rules || index < 0 || index >= rules->num_revival_rules) return NO_ID;
    return rules->revival_rules[index].object_id;
}

Bool gamerules_get_triggered_revival(GameRules *rules, int index) {
    if (!rules || index < 0 || index >= rules->num_revival_rules) return FALSE;
    return rules->revival_rules[index].triggered;
}

int gamerules_get_num_drop_rules(GameRules *rules) {
    if (!rules) return 0;
    return rules->num_rules;
}

int gamerules_get_num_open_links(GameRules *rules) {
    if (!rules) return 0;
    return rules->num_open_links;
}

int gamerules_get_num_heal_rules(GameRules *rules) {
    if (!rules) return 0;
    return rules->num_heal_rules;
}

int gamerules_get_num_craft_rules(GameRules *rules) {
    if (!rules) return 0;
    return rules->num_crafts_rules;
}

int gamerules_get_num_object_damage_rules(GameRules *rules) {
    if (!rules) return 0;
    return rules->num_object_damage_rules;
}

int gamerules_get_num_enemy_damage_rules(GameRules *rules) {
    if (!rules) return 0;
    return rules->num_enemy_damage_rules;
}

int gamerules_get_num_revival_rules(GameRules *rules) {
    if (!rules) return 0;
    return rules->num_revival_rules;
}


