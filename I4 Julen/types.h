/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 2.0
 * @date 29-11-2021
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 500
#define WORD_S 255
#define NO_ID -1
#define NO_DIRECTION -1

#define MAX_ID 200

#define MAX_DESCR 500

#define MAX_OBJ 4

#define MAX_LINK 100

#define ENEMY_ID 55

#define PLAYER_ID 56

#define NROWS 5
#define NCOLS 9

typedef long Id;

typedef enum /*the two types of values for the boolean type function*/
{
  FALSE,
  TRUE
} BOOL;

typedef enum /*the two types of values for the function type status*/
{
  ERROR,
  OK
} STATUS;

typedef enum /*the four cardinal directions*/
{
  N,
  S,
  E,
  W,
  U,
  D
} DIRECTION;

#endif
