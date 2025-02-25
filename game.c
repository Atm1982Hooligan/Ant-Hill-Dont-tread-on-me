/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
* @copyright GNU Public License
 */

#include "game.h"
#include "game_reader.h"
#include "player.h"
#include "objects.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Game structure
*/

struct _Game {
  Id player_location;       /**< Current location of the player. */
  Player *player;           /**< Pointer to the player. */
  Object *object;           /**< Pointer to the object in the game. */
  Space *spaces[MAX_SPACES]; /**< Array of spaces in the game. */
  int n_spaces;             /**< Number of spaces in the game. */
  Command *last_cmd;        /**< Last command executed. */
  Bool finished;            /**< Whether the game is finished or not. */
};


/**
   Private functions
*/


/**
   Game interface implementation
*/

Status game_create(Game **game) {
    int i;

    *game = (Game*)malloc(sizeof(Game));
    if (*game == NULL) {
        free (*game);
        return ERROR;
    }

    for (i = 0; i < MAX_SPACES; i++) {
        (*game)->spaces[i] = NULL;
    }

    (*game)->n_spaces = 0;
    (*game)->player = player_create(NO_ID);
    (*game)->object = object_create(NO_ID);
    (*game)->last_cmd = command_create();
    (*game)->finished = FALSE;

    return OK;
}

Status game_create_from_file(Game **game, char *filename) {
    if (game_create(game) == ERROR) {
        return ERROR;
    }

    if (game_load_spaces(*game, filename) == ERROR) {
        game_destroy(*game);
        return ERROR;
    }

    /* The player and the object are located in the first space */
    game_set_player_location(*game, game_get_space_id_at(*game, 0));
    game_set_object_location(*game, game_get_space_id_at(*game, 0));

    return OK;
}

Status game_destroy(Game *game) {
  int i = 0;

  if (!game) {
    return ERROR;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (game->spaces[i] != NULL) {
      space_destroy(game->spaces[i]);
      game->spaces[i] = NULL;
    }
  }

  if (game->player != NULL) {
    player_destroy(game->player);
    game->player = NULL;
  }

  if (game->object != NULL) {
    object_destroy(game->object);
    game->object = NULL;
  }

  if (game->last_cmd != NULL) {
    command_destroy(game->last_cmd);
    game->last_cmd = NULL;
  }

  free(game);
  game = NULL;
  return OK;
}

Space *game_get_space(Game *game, Id id) {
  int i;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (id == space_get_id(game->spaces[i])) {
      return game->spaces[i];
    }
  }

  return NULL;
}

Id game_get_player_location(Game *game) { 
  return player_get_location(game->player); 
}

Status game_set_player_location(Game *game, Id id) {
  if (id == NO_ID) {
    return ERROR;
  }
  
  player_set_location(game->player, id);
  return OK;
}

Id game_get_object_location(Game *game) { 
  int i;

  if (game == NULL || game->object == NULL) {
    return NO_ID;  
  }
 
  for (i = 0; i < game->n_spaces; i++) {
    if (game->spaces[i] != NULL && space_get_id(game->spaces[i]) == object_get_location(game->object)) {
      return object_get_location(game->object);
    }
  }

  return NO_ID; 
}

Status game_set_object_location(Game *game, Id id) {
  object_set_location(game->object, id);
  space_set_object(game_get_space(game, id), TRUE);
  return OK;
}

Command* game_get_last_command(Game *game) { return game->last_cmd; }

Status game_set_last_command(Game *game, Command *command) {
  game->last_cmd = command;
  return OK;
}

Bool game_get_finished(Game *game) { return game->finished; }

Status game_set_finished(Game *game, Bool finished) {
  game->finished = finished;
  return OK;
}

Player* game_get_player(Game *game) {
  return game->player;
}

int game_get_number_of_spaces(Game *game) {
  if (!game) {
    return -1;
  }
  return game->n_spaces;
}

Space* game_get_space_at(Game *game, int position) {
  if (!game || position < 0 || position >= game->n_spaces) {
    return NULL;
  }
  return game->spaces[position];
}
int* game_get_numid_pointer(Game *game) {
  if (!game) {
    return NULL;
  }
  return &(game->n_spaces);
}

void game_print(Game *game) {
  int i;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }

  printf("=> Object location: %d\n", (int)game_get_object_location(game));
  printf("=> Player location: %d\n", (int)game_get_player_location(game));
}











