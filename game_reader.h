#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"

Status game_load_spaces(Game *game, char *filename);
Status game_add_space(Game *game, Space *space);
Id game_get_space_id_at(Game *game, int position);

#endif
