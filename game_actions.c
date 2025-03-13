/**
 * @brief It implements the game update through user actions
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Private functions
*/

/**
 * @brief Handles the "unknown" command.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 */
void game_actions_unknown(Game *game);

/**
 * @brief Handles the "exit" command.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 */
void game_actions_exit(Game *game);

/**
 * @brief Handles the "next" command.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 */
void game_actions_next(Game *game);

/**
 * @brief Handles the "back" command.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 */
void game_actions_back(Game *game);

/**
 * @brief Handles the "take" command.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 */
void game_actions_take(Game *game);

/**
 * @brief Handles the "drop" command.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 */
void game_actions_drop(Game *game);

/**
 * @brief Handles the "attack" command.
 * @author Izan Robles
 *
 * @param game A pointer to the game structure.
 */
void game_actions_attack(Game *game);

/**
 * @brief Handles the "left" command.
 * @author Izan Robles
 * 
 * @param game A pointer to the game structure.
 */
void game_actions_left(Game *game);

/**
 * @brief Handles the "right" command.
 * @author Izan Robles 
 * 
 * @param game A pointer to the game structure.
 */
void game_actions_right(Game *game);

/**
   Game actions implementation
*/

Status game_actions_update(Game *game, Command *command) {
  CommandCode cmd;

  game_set_last_command(game, command);

  cmd = command_get_code(command);

  switch (cmd) {
    case UNKNOWN:
      game_actions_unknown(game);
      break;

    case EXIT:
      game_actions_exit(game);
      break;

    case NEXT:
      game_actions_next(game);
      break;

    case BACK:
      game_actions_back(game);
      break;

    case TAKE:
      game_actions_take(game);
      break;
      
    case DROP:
      game_actions_drop(game);
      break;

    case ATTACK:
      game_actions_attack(game);
      break;

    case LEFT:
      game_actions_left(game);
      break;

    case RIGHT:
      game_actions_right(game);
      break;

    default:
      break;
  }

  return OK;
}

/**
   Calls implementation for each action
*/

void game_actions_unknown(Game *game) {}

void game_actions_exit(Game *game) {}

void game_actions_next(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_south(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_back(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    return;
  }

  current_id = space_get_north(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}



void game_actions_take(Game *game){
  Id object_id = NO_ID;
  Id player_id = NO_ID;
  int i = 0;

  player_id = game_get_player_location(game);
  
  if ((player_get_object(game_get_player(game))  == FALSE )) {
    for (i = 0; i < *(game_get_n_objects(game)); i++) {
      object_id = game_get_object_location(game, i);

      if (object_id == player_id) {
        game_set_object_location(game, NO_ID, i); 
        player_set_object(game_get_player(game), TRUE); 
      }
    }    
  }
}

void game_actions_drop(Game *game) {
  Id object_id = NO_ID;
  Id player_id = NO_ID;
  int i;

  player_id = game_get_player_location(game);

  if ((player_get_object(game_get_player(game)) == TRUE)) {

    for (i = 0; i < *(game_get_n_objects(game)); i++) {
      object_id = game_get_object_location(game, i);

      if (object_id == NO_ID) {
        game_set_object_location(game, player_id, i);  
        player_set_object(game_get_player(game), FALSE); 
      }
    }      
  }
}

void game_actions_attack(Game *game) {
  if (game == NULL) {
    return;
  }

  int random;
  random = rand() % 2;

  if (random == 0) {
    player_set_health(game_get_player(game), player_get_health(game_get_player(game)) - 10);
  } else {
    character_set_health(space_get_character(game_get_player_location), character_get_health(space_get_character(game_get_player_location)) - 10);
  }
}

void game_actions_right(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_east(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_left(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_west(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}
