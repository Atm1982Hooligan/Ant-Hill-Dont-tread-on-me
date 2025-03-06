/**
 * @brief It implements the space module
 *
 * @file player.c
 * @author Alejandro Gonzalez
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Player {
  Id id; /*Player's id*/
  char name[WORD_SIZE + 1]; /*Player's name*/
  Id location; /*Player's location*/
  Bool object; /*Player's object*/
};


Player* player_create(Id id) {
  Player* newPlayer = NULL;


  newPlayer = (Player*)malloc(sizeof(Player));
  if (newPlayer == NULL) {
    return NULL;
  }

  /* Initialization of an empty space*/
  newPlayer->id = id;
  newPlayer->name[0] = '\0';
  newPlayer->location = NO_ID;
  newPlayer->object = FALSE;

  return newPlayer;
}

Status player_destroy(Player *player) {
  if (!player) {
    printf("Error: player is NULL in player_destroy\n");
    return ERROR;
  }

  free(player);
  player = NULL;
  return OK;
}

Id player_get_id(Player* player) {
  if (!player) {
    printf("Error: player is NULL in player_get_id\n");
    return NO_ID;
  }
  return player->id;
}

Status player_set_name(Player* player, char* name) {
  if ((player) == NULL || !(name)) {
    printf("Error: invalid parameters in player_set_name\n");
    return ERROR;
  }

  if (!strcpy(player->name, name)) {
    return ERROR;
  }
  return OK;
}

const char* player_get_name(Player* player) {
  if ((player) == NULL) {
    printf("Error: player is NULL in player_get_name\n");
    return NULL;
  }
  return player->name;
}

Status player_set_object(Player* player, Bool value) {
  if ((player) == NULL) {
    printf("Error: player is NULL in player_set_object\n");
    return ERROR;
  }
  player->object = value;
  return OK;
}

Bool player_get_object(Player* player) {
  if ((player) == NULL) {
    printf("Error: player is NULL in player_get_object\n");
    return FALSE;
  }
  
  return player->object;  
}

Status player_print(Player* player) {
  if ((player) == NULL) {
    printf("Error: player is NULL in player_print\n");
    return ERROR;
  }

  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->id, player->name);

  if (player_get_object(player)) {
    fprintf(stdout, "---> Object in the space.\n");
  } else {
    fprintf(stdout, "---> No object in the space.\n");
  }

  return OK;
}


Id player_get_location(Player* player) {
  if (!player) {
    printf("Error: player is NULL in player_get_location\n");
    return NO_ID;
  }
  return player->location;
}

Id *player_get_location_pointer(Player* player) {
  if (!player) {
    printf("Error: player is NULL in player_get_location_pointer\n");
    return NULL;
  }
  return &(player->location);
}