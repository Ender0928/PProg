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

#define WORD_SIZE 1000
#define NO_ID -1

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
  W
} DIRECTION;

#endif
