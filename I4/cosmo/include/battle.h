#ifndef BATTLE_H
#define BATTLE_H

#include "types.h"

typedef struct _Battle Battle;

Battle *battle_create();
void battle_destroy(Battle *battle);

Status battle_set_enemy_id(Battle *battle, Id id);
Id battle_get_enemy_id(Battle *battle);

void battle_set_initial_healths(Battle *battle, int player, int enemy);
int battle_get_initial_player_health(Battle *battle);
int battle_get_initial_enemy_health(Battle *battle);

#endif /* BATTLE_H */
