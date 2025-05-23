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
#define MAX_CHARACTERS 3

/**
 * @brief Defines the maximum number of objects allowed in the project
 */
#define MAX_OBJECTS 5

/**
 * @brief Defines the maximum number of links allowed in the project
 */
#define MAX_LINKS 100

/**
 * @brief Defines the maximum number of objects allowed in a inventory
 */
#define MAX_INVENTORY 10

/**
 * @brief Defines the size of the graphical description (gdesc) array
 */
#define TAM_GDESC 7

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
typedef enum { N, S, E, W, U } Direction;

#endif /* TYPES_H */