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




#define CMD_LENGHT 30
#define CMD_ARG_SIZE 32

char *cmd_to_str[N_CMD][N_CMDT] = {{"", "No command"}, {"", "Unknown"}, {"e", "Exit"}, {"n", "Next"}, {"b", "Back"}, 
                                   {"t", "Take"}, {"d", "Drop"}, {"a", "Attack"}, {"l", "Left"}, {"r", "Right"}, {"c", "Chat"}};

/**
 * @brief Command
 *
 * This struct stores all the information related to a command.
 */
struct _Command {
  CommandCode code; /*!< Name of the command */
  char arg[CMD_ARG_SIZE]; /*!< Argument of the command */
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

  newCommand->code = NO_CMD;
  newCommand->arg[0] = '\0';

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

  command->code=code;

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

    if (cmd == TAKE) {
      token = strtok(NULL, "\n");
      if (token) {
        while (*token == ' ') token++;
        command_set_arg(command, token);
      }
    }

    return OK;
  }
  return command_set_code(command, EXIT);
}

const char* command_get_arg(Command* command) {
  if (!command) {
    return NULL;
  }
  return command->arg;
}

Status command_set_arg(Command* command, char* arg) {
  if (!command || !arg) {
    return ERROR;
  }
  
  if (strlen(arg) >= CMD_ARG_SIZE) {
    return ERROR;
  }
  
  strcpy(command->arg, arg);
  return OK;
}
