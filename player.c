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
  int player_health; /*Player's health*/
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
    return ERROR;
  }

  free(player);
  player = NULL;
  return OK;
}

Id player_get_id(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->id;
}

Status player_set_name(Player* player, char* name) {
  if ((player) == NULL || !(name)) {
    return ERROR;
  }

  if (!strcpy(player->name, name)) {
    return ERROR;
  }
  return OK;
}

const char* player_get_name(Player* player) {
  if ((player) == NULL) {
    return NULL;
  }
  return player->name;
}

Status player_set_object(Player* player, Bool value) {
  if ((player) == NULL) {
    return ERROR;
  }
  player->object = value;
  return OK;
}

Bool player_get_object(Player* player) {
  if ((player) == NULL) {
    return FALSE;
  }
  
  
  return player->object;  
  /*return TRUE;*/
}

Status player_print(Player* player) {
  
  /*Error Control */
  if ((player) == NULL) {
    return ERROR;
  }

  /* 1. Print the id and the name of the player*/
  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->id, player->name);

  /* 2. Print if there is an object in the player or not */
  if (player_get_object(player)) {
    fprintf(stdout, "---> Object in the space.\n");
  } else {
    fprintf(stdout, "---> No object in the space.\n");
  }

  return OK;
}


Id player_get_location(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->location;
}

Id *player_get_location_pointer(Player* player) {
  if (!player) {
    return NULL;
  }
  return &(player->location);
}

Status player_set_health(Player* player, int health) {
  if (!player || health < 0) {
    return ERROR;
  }
  player->player_health = health;
  return OK;
}

int player_get_health(Player* player) {
  if (!player) {
    return -1;
  }
  return player->player_health;
}