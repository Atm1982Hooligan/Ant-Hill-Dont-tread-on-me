#include "game_reader.h"
#include "space.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Status game_load_spaces(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space *space = NULL;
  Status status = OK;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);
#ifdef DEBUG
      printf("Leído: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
      space = space_create(id);
      if (space != NULL) {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        game_add_space(game, space);
      }
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);
  return status;
}

Status game_add_space(Game *game, Space *space) {
  Space *java;
  
  if ((space == NULL) || (game_get_number_of_spaces(game) >= MAX_SPACES)) {
    return ERROR;
  }
  
  java =  game_get_space_at(game, game_get_number_of_spaces(game));

  space_destroy(java);
  java = space;
  /*game->spaces[game_get_number_of_spaces(game)] = space;*/
  (*game_get_numid_pointer(game))++;

  return OK;
}

Id game_get_space_id_at(Game *game, int position) {
  if (position < 0 || position >= game_get_number_of_spaces(game)) {
    return NO_ID;
  }

  return space_get_id(game_get_space_at(game, position));
}
