/**
 * @brief It defines the command interpreter interface
 *
 * @file command.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define N_CMDT 2
#define N_CMD 13

/**
 * @brief Types of commands
 *
 * CMDS represents short commands,
 * CMDL represents long commands.
 */
typedef enum { CMDS, CMDL } CommandType;

/**
 * @brief Command codes
 *
 * These codes represent different commands that can be executed.
 */
typedef enum { NO_CMD = -1, UNKNOWN, EXIT, NEXT, BACK, LEFT, RIGHT, TAKE, DROP, ATTACK, CHAT, INSPECT, MOVE} CommandCode;

/**
 * @brief Definition of Command structure
 *
 * This structure represents a command and its properties.
 */
typedef struct _Command Command;

/**
 * @brief Creates a new command
 *
 * Allocates memory and initializes a new command.
 *
 * @return Pointer to the new command, or NULL on failure
 */
Command* command_create();

/**
 * @brief Destroys a command
 *
 * Frees the allocated memory of a given command.
 *
 * @param command Pointer to the command to be destroyed
 * @return OK if successful, ERROR otherwise
 */
Status command_destroy(Command* command);

/**
 * @brief Sets the command code
 *
 * Assigns a command code to the given command structure.
 *
 * @param command Pointer to the command
 * @param code Command code to set
 * @return OK if successful, ERROR otherwise
 */
Status command_set_code(Command* command, CommandCode code);

/**
 * @brief Gets the command code
 *
 * Retrieves the command code stored in the command structure.
 *
 * @param command Pointer to the command
 * @return The stored command code, or NO_CMD if invalid
 */
CommandCode command_get_code(Command* command);

/**
 * @brief Gets user input as a command
 *
 * Reads user input, parses it, and sets the corresponding command code.
 *
 * @param command Pointer to the command
 * @return OK if successful, ERROR otherwise
 */
Status command_get_user_input(Command* command);

/**
 *@brief Gets the command argument
 *
 *Retrieves the argument of the command write by the player
 *
 *@param command Pointer to the command
 *@return The text of the argument given by the player   
 */
char *command_get_argument(Command *command);

/**
 *@brief Gets the direction of the command
 *
 *Retrieves the direction of the command
 *
 *@param command Pointer to the command
 *@return The direction of the command 
 */
Direction command_get_direction(Command *command);

char *command_get_name(Command *code);

#endif
