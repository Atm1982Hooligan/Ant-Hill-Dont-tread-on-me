/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "graphic_engine.h"

#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"
#include "game.h"

#define WIDTH_MAP 60
#define WIDTH_DES 35
#define WIDTH_BAN 23
#define HEIGHT_MAP 20
#define HEIGHT_BAN 1
#define HEIGHT_HLP 2
#define HEIGHT_FDB 3

struct _Graphic_engine {
  Area *map, *descript, *banner, *help, *feedback;
};

Graphic_engine *graphic_engine_create() {
  static Graphic_engine *ge = NULL;

  if (ge) {
    return ge;
  }

  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
  if (ge == NULL) {
    return NULL;
  }

  ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
  ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
  ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge) {
  if (!ge) return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_loc = NO_ID, id_right, id_left = NO_ID;
  Space *space_act = NULL;
  char obj = '\0';
  char str[255];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i;
  int game_n_objects = *(game_get_n_objects(game));
  const char *message = NULL;
  Character **characters;
  Id player_location;
  Bool same_location = FALSE;
  Object **objects = game_get_objects(game);
  const char *obj_name;
  Bool friendly; 
  const char *temporal_feedback;
  /*const char **gdesc = NULL;*/

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID) {
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);
    id_right = space_get_east(space_act);
    id_left = space_get_west(space_act);
    /*gdesc = space_get_gdesc(space_act);*/

    obj = ' ';

    for (i = 0; i < game_n_objects; i++) {
      if (game_get_object_location(game, i) == id_next) {
        obj = '*';
        break;
      }
    }

    if (id_back != NO_ID) {
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |        %3d|", (int)id_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        ^");
      screen_area_puts(ge->map, str);
    }

    obj = ' ';

    for (i = 0; i < game_n_objects; i++) {
      if (game_get_object_location(game, i) == id_next) {
        obj = '*';
        break;
      }
    }

    if (id_act != NO_ID && id_right == NO_ID && id_left == NO_ID) {
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | m0^    %3d|", (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }

    obj = ' ';

    for (i = 0; i < game_n_objects; i++) {
      if (game_get_object_location(game, i) == id_next) {
        obj = '*';
        break;
      }
    }

    if (id_act != NO_ID && id_right != NO_ID && id_left == NO_ID) {
      sprintf(str, "  +-----------+   +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | m0^    %3d|   |        %3d|", (int)id_act, (int)id_right);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     | > |           |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+   +-----------+");
      screen_area_puts(ge->map, str);
    }
  
    obj = ' ';

    for (i = 0; i < game_n_objects; i++) {
      if (game_get_object_location(game, i) == id_next) {
        obj = '*';
        break;
      }
    }

    if (id_act != NO_ID && id_left != NO_ID && id_right != NO_ID) {  

      sprintf(str, "_");
      screen_area_puts(ge->map, str);
      sprintf(str, "_");
      screen_area_puts(ge->map, str);
      sprintf(str, "_");
      screen_area_puts(ge->map, str);
      sprintf(str, "_");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+   +-----------+   +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |        %3d|   | m0^    %3d|   |        %3d|", (int)id_left, (int)id_act, (int)id_right);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |           | < |      %c    | > |           |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+   +-----------+   +-----------+");
      screen_area_puts(ge->map, str);
    }
    /*!< ----------------------------------------------*/
    
    obj = ' ';

    for (i = 0; i < game_n_objects; i++) {
      if (game_get_object_location(game, i) == id_next) {
        obj = '*';
        break;
      }
    }

    if (id_act != NO_ID && id_right == NO_ID && id_left != NO_ID) {
      
      sprintf(str, "_");
      screen_area_puts(ge->map, str);
      sprintf(str, "_");
      screen_area_puts(ge->map, str);
      sprintf(str, "_");
      screen_area_puts(ge->map, str);
      sprintf(str, "_");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+   +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |        %3d|   |  m0^   %3d|", (int)id_left, (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |           | < |     %c     |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+   +-----------+");
      screen_area_puts(ge->map, str);
    }
    obj = ' ';

    for (i = 0; i < game_n_objects; i++) {
      if (game_get_object_location(game, i) == id_next) {
        obj = '*';
        break;
      }
    }

    if (id_next != NO_ID) {
      sprintf(str, "        v");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |        %3d|", (int)id_next);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }
  }
  
  /*Paint in the description area*/
  screen_area_clear(ge->descript);
  sprintf(str, "  Health: %d", player_get_health(game_get_player(game)));
  screen_area_puts(ge->descript, str);

  
  /* Paint character info if present in current space */
  characters = game_get_character_array(game);
  player_location = game_get_player_location(game);

  sprintf(str, " ");
  screen_area_puts(ge->descript, str); 

  for (i = 0; i < MAX_CHARACTERS; i++) {
    if (characters[i] != NULL && character_get_location(characters[i]) == player_location) {
      sprintf(str, "  %s:", character_get_name(characters[i]));
      screen_area_puts(ge->descript, str);
      sprintf(str, "  Health: %d", character_get_health(characters[i]));
      screen_area_puts(ge->descript, str);
      friendly = character_get_friendly(characters[i]);
      if (friendly == TRUE) {
        sprintf(str, "  Friend");
        screen_area_puts(ge->descript, str);
      } else {
        sprintf(str, "  Enemy");
        screen_area_puts(ge->descript, str);
      }
      
      break; 
    }
  }
  
  sprintf(str, " ");
  screen_area_puts(ge->descript, str);
  sprintf(str, "  Objects:");
  screen_area_puts(ge->descript, str);

  for (i = 0; i < game_n_objects; i++) {
    if (objects[i] != NULL) {
        obj_loc = game_get_object_location(game, i);
        obj_name = object_get_name(objects[i]);
        
        if (obj_loc != NO_ID && obj_name != NULL) {
            sprintf(str, "  %s --> %d", obj_name, (int)obj_loc);
            screen_area_puts(ge->descript, str);
        }
    }
  }
  
  /* Paint in the banner area */
  screen_area_puts(ge->banner, "    The anthill game ");

  /* Paint in the feedback area */
  screen_area_clear(ge->feedback);
  last_cmd = command_get_code(game_get_last_command(game));
  sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  screen_area_puts(ge->feedback, str);
  temporal_feedback = game_get_temporal_feedback(game);
  if (temporal_feedback && last_cmd == ATTACK) {
    sprintf(str, " %s", temporal_feedback);
    screen_area_puts(ge->feedback, str);
  }
  
  /* Add character message if exists */
  message = game_get_last_message(game);
  if (message && last_cmd == CHAT) {
  characters = game_get_character_array(game);
  player_location = game_get_player_location(game);

  for (i = 0; i < MAX_CHARACTERS; i++) {
    if (characters[i] != NULL && character_get_location(characters[i]) == player_location) {
      same_location = TRUE;
      break;
    }
  }

  if (same_location) {
    sprintf(str, " Character says: %s", message);
    screen_area_puts(ge->feedback, str);
  }
}

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}
