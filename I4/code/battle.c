#include "battle.h"
#include <stdlib.h>

struct _Battle {
    Id enemy_id;
    int initial_player_health;
    int initial_enemy_health;
};

Battle *battle_create() {
    Battle *battle = malloc(sizeof(Battle));
    if (!battle) return NULL;

    battle->enemy_id = NO_ID;
    battle->initial_player_health = 0;
    battle->initial_enemy_health = 0;

    return battle;
}

void battle_destroy(Battle *battle) {
    if (!battle) return;
    free(battle);
}

Status battle_set_enemy_id(Battle *battle, Id id) {
    if (!battle) return ERROR;
    battle->enemy_id = id;
    return OK;
}

Id battle_get_enemy_id(Battle *battle) {
    if (!battle) return NO_ID;
    return battle->enemy_id;
}

void battle_set_initial_healths(Battle *battle, int player, int enemy) {
    if (!battle) return;
    battle->initial_player_health = player;
    battle->initial_enemy_health = enemy;
}

int battle_get_initial_player_health(Battle *battle) {
    if (!battle) return -1;
    return battle->initial_player_health;
}

int battle_get_initial_enemy_health(Battle *battle) {
    if (!battle) return -1;
    return battle->initial_enemy_health;
}
