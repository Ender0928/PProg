/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

/**
 * @brief Defines the maximum word size allowed in the project
 */
#define WORD_SIZE 1000

/**
 * @brief Defines the value for an invalid ID
 */
#define NO_ID -1

/**
 * @brief Defines the maximum number of IDs allowed in the project
 */
#define MAX_ID 200

/**
 * @brief Defines the maximum number of characters allowed in the project
 */
#define TAM_C 256

/**
 * @brief Defines the maximum number of characters allowed in the project
 */
#define MAX_CHARACTERS 15

/**
 * @brief Defines the maximum number of objects allowed in the project
 */
#define MAX_OBJECTS 20

/**
 * @brief Defines the maximum number of links allowed in the project
 */
#define MAX_LINKS 100

/**
 * @brief Defines the maximum number of objects allowed in a inventory
 */
#define MAX_INVENTORY 20

/**
 * @brief Defines the maximum number of players allowed in the project
 */
#define MAX_PLAYERS 8

/**
 * @brief Defines the maximum number of drop rules in the project
 */
#define MAX_DROP_RULES 5

/**
 * @brief Defines ID of the space objects
 */
#define ID_SPACE_OBJECTS 10

/**
 * @brief Defines the maximum number of open links
 */
#define MAX_OPEN_LINKS 5

/**
 * @brief Defines the maximum number of health bojects
 */
#define MAX_HEALTH_OBJECTS 5

/**
 * @brief Defines the maximum health of the players
 */
#define PLAYER_HEALTH 5

/**
 * @brief Defines the maximum number of crafts rules
 */
#define MAX_CRAFTS_RULES 7
/**
 * @brief Defines the size of the graphical description (gdesc) array
 */
#define TAM_GDESC 7

#define GDESC_ROWS 8

#define GDESC_COLS 27

/**
 * @brief Type definition for object IDs
 */
typedef long Id;

/**
 * @brief Boolean type definition
 *
 * This type represents boolean values, where FALSE is 0 and TRUE is 1.
 */
typedef enum { FALSE, TRUE } Bool;

/**
 * @brief Status type definition
 *
 * This type is used to indicate the success or failure of operations.
 */
typedef enum { ERROR, OK } Status;

/**
 * @brief Direction type definition
 *
 * This enumeration defines the four possible movement directions.
 */
typedef enum { N, S, E, W, D, UP, U} Direction;

typedef enum {
    GAME_STATE_NORMAL,
    GAME_STATE_COMBAT,
    GAME_STATE_REVIVAL,
    GAME_STATE_RESPAUWN
} GameState;

#define GDESC_BATTLE_ROWS 22

#define GDESC_BATTLE_COLS 60

#define MAX_DAMAGE_OBJECT_RULES 10

#define MAX_ENEMY_DAMAGE_RULES 20

#define MAX_REVIVAL_OBJECTS 1

#define DEFAULT_REVIVAL_SPACE_ID 111

#endif /* TYPES_H */