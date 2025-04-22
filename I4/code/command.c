/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

 #include "command.h"

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <strings.h>
 
 #define CMD_LENGHT 30
 
 char *cmd_to_str[N_CMD][N_CMDT] = {{"", "No command"}, {"", "Unknown"}, {"e", "Exit"}, {"t", "Take"}, {"d", "Drop"}, {"a", "Attack"}, {"c", "Chat"}, {"i", "Inspect"}, {"m", "Move"},{"k", "Recruit"},{"n", "Abandon"}, {"s", "Save"}, {"l", "Load"}};
 
 /**
  * @brief Command
  *
  * This struct stores all the information related to a command.
  */
 struct _Command {
   CommandCode code;          /*!< Name of the command */
   char argument[CMD_LENGHT]; /*!< Argument of the command */
   Direction direction;       /*!< direction of the command */
 };
 
 /** space_create allocates memory for a new space
  *  and initializes its members
  */
 Command* command_create() {
   Command* newCommand = NULL;
 
   newCommand = (Command*)malloc(sizeof(Command));
   if (newCommand == NULL) {
     return NULL;
   }
 
   /* Initialization of an empty command*/
   newCommand->code = NO_CMD;
   newCommand->argument[0] = '\0';
 
   return newCommand;
 }
 
 Status command_destroy(Command* command) {
   if (!command) {
     return ERROR;
   }
 
   free(command);
   command = NULL;
   return OK;
 }
 
 Status command_set_code(Command* command, CommandCode code) {
   if (!command) {
     return ERROR;
   }
 
   command->code = code;
 
   return OK;
 }
 
 CommandCode command_get_code(Command* command) {
   if (!command) {
     return NO_CMD;
   }
   return command->code;
 }
 
 Status command_get_user_input(Command* command) {
   char input[CMD_LENGHT] = "", *token = NULL;
   int i = UNKNOWN - NO_CMD + 1;
   CommandCode cmd;
 
   if (!command) {
     return ERROR;
   }
 
   if (fgets(input, CMD_LENGHT, stdin)) {
     token = strtok(input, " \n");
     if (!token) {
       return command_set_code(command, UNKNOWN);
     }
 
     cmd = UNKNOWN;
     while (cmd == UNKNOWN && i < N_CMD) {
       if (!strcasecmp(token, cmd_to_str[i][CMDS]) || !strcasecmp(token, cmd_to_str[i][CMDL])) {
         cmd = i + NO_CMD;
       } else {
         i++;
       }
     }
     command_set_code(command, cmd);
 
     token = strtok(NULL, " \n");
     if (token) {
      if (strcasecmp(token, "N")==0 || strcasecmp(token, "NORTH")==0){
        command->direction = N;
      } else if (strcasecmp(token, "E")==0 || strcasecmp(token, "EAST")==0){
        command->direction = E;
      } else if (strcasecmp(token, "W")==0 || strcasecmp(token, "WEST")==0){
        command->direction = W;
      } else if (strcasecmp(token, "S")==0 || strcasecmp(token, "SOUTH")==0){
        command->direction = S;
      } else if (strcasecmp(token, "D")==0 || strcasecmp(token, "DOWN")==0){
        command->direction = D;
      } else if (strcasecmp(token, "U")==0 || strcasecmp(token, "UP")==0){
        command->direction = UP;
      } else {
        strncpy(command->argument, token, CMD_LENGHT - 1);
        command->argument[CMD_LENGHT - 1] = '\0';
      }
     }
     else {
        command->argument[0] = '\0';
     }
     return OK;
   }
 
   return command_set_code(command, EXIT);
 }
 
 char *command_get_argument(Command *command) {
   if (!command) {
     return NULL;
   }
   return command->argument;
 }

 Direction command_get_direction(Command *command) {
  if (!command) {
    return U;
  }
  return command->direction;
 }

 char *command_get_name(Command *code) {
   if (command_get_code(code) < NO_CMD || command_get_code(code) >= N_CMD) {
     return NULL;
   }
   return cmd_to_str[command_get_code(code) + 1][CMDL];
 }
 