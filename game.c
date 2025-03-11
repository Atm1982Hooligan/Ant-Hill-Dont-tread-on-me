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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Game {
  Id player_location;       /**< Current location of the player. */
  Player *player;           /**< Pointer to the player. */
  Space *spaces[MAX_SPACES];/**< Array of spaces in the game. */
  Object *objects[MAX_OBJECTS];/**< Array of objects in the game. */
  int n_spaces;             /**< Number of spaces in the game. */
  int n_objects;            /**< Number of objects in the game. */
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

  if (*game == NULL) {
    *game = (Game *)malloc(sizeof(Game));
    if (!*game) {
      return ERROR;
    }
  }

  for (i = 0; i < MAX_SPACES; i++) {
    (*game)->spaces[i] = NULL;
  }

  (*game)->n_spaces = 0;
  (*game)->n_objects = 0;
  (*game)->player = player_create(NO_ID);
  if ((*game)->player == NULL) {
    return ERROR;
  }
  /*(*game)->object[0] = object_create(NO_ID);
  if ((*game)->object[0] == NULL) {
    return ERROR;
  }
  (*game)->n_objects++;*/
  (*game)->last_cmd = command_create();
  if ((*game)->last_cmd == NULL) {
    return ERROR;
  }
  (*game)->finished = FALSE;

  return OK;
}

Status game_create_from_file(Game **game, char *filename) {
  if (game_create(game) == ERROR) {
    return ERROR;
  }

  if (game_load_spaces(*game, filename) == ERROR) {
    return ERROR;
  }
  
  if (game_load_objects(*game, filename) == ERROR) {
    return ERROR;
  }

  /* The player and the object are located in the first space */
  game_set_player_location(*game, game_get_space_id_at(*game, 0));
  /*game_set_object_location(*game, game_get_space_id_at(*game, 0), 0);*/

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

  for (i = 0; i < game->n_objects; i++) {
    if (game->objects[i] != NULL) {
      object_destroy(game->objects[i]);
    }
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
  int i = 0;

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

Player *game_get_player(Game *game) {
  if (game == NULL) {
    return NULL;
  }

  return game->player;
}

Id game_get_player_location(Game *game) { 

  Id location =  player_get_location(game->player);

  return location; 
}

Status game_set_player_location(Game *game, Id id) {
  if (id == NO_ID) {
    return ERROR;
  }
  
  *(player_get_location_pointer(game->player)) = id;

  return OK;
}

Id game_get_object_location(Game *game, int position) { 
  /*!< This is for the for-loop further down the code*/
  int i = 0;

  if (game == NULL || position < 0 || position >= MAX_OBJECTS || game->objects[position] == NULL) {
    return NO_ID;  
  }
  
  /*!<It will cycle thorugh each space in "nSpaces" and check if its object is the same one as object id*/
  for (i = 0; i < game->n_spaces; i++)
  {
    
    if (game->spaces[i] != NULL  &&  (space_get_id(game->spaces[i]) ==  object_get_location(game->objects[position])) )
    {
      return object_get_location(game->objects[position]); /* !< Correctly access the id of the first object*/
    }
  }
  
  return NO_ID;  /*!< Returns NO_ID if no object within a space was found*/
}

Status game_set_object_location(Game *game, Id id, int position) {
  if (position < 0 || position >= MAX_OBJECTS || game == NULL) {
    return ERROR;
  }

  *(object_get_location_pointer(game->objects[position])) = id;

  if (game->n_objects == position){
    game->n_objects++;
  }

  space_set_object(game_get_space(game, id), TRUE);

  return OK;
}

Command* game_get_last_command(Game *game) { 
  return game->last_cmd; 
}

Status game_set_last_command(Game *game, Command *command) {
  game->last_cmd = command;

  return OK;
}

Bool game_get_finished(Game *game) { 
  return game->finished; 
}

Status game_set_finished(Game *game, Bool finished) {
  game->finished = finished;

  return OK;
}

void game_print(Game *game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }

  for (i = 0; i < game->n_objects; i++)
  {
    printf("=> Object location: %d\n", (int)object_get_id(game->objects[i]));
  }
  
  printf("=> Player location: %d\n", (int)game->player_location);
}

/*ADDITIONAL FUNCTIONS*/

int *game_get_n_spaces(Game *game) {
  if (game == NULL) {
    return NULL;
  }
  return &(game->n_spaces);
}

Space** game_get_spaces(Game *game) {
  if (game == NULL) {
    return NULL;
  }
  return game->spaces;
}

int *game_get_n_objects(Game *game) {
  if (game == NULL) {
    return NULL;
  }
  return &(game->n_objects);
}

Object **game_get_objects(Game *game) {
  if (game == NULL) {
    return NULL;
  }
  return game->objects;
}









