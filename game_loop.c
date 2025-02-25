/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "graphic_engine.h"
#include "game_reader.h"

/**
 * @brief Initializes the game loop.
 * @param game A pointer to the game structure to be initialized.
 * @param gengine A pointer to the graphic engine to be initialized.
 * @param file_name The name of the file containing the game data.
 * @return 0 if initialization is successful, 1 otherwise.
 */
int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name);

/**
 * @brief Runs the main game loop.
 * @param game The game structure.
 * @param gengine The graphic engine used to render the game.
 */
void game_loop_run(Game *game, Graphic_engine *gengine);

/**
 * @brief Cleans up resources used by the game loop.
 * @param game The game structure.
 * @param gengine The graphic engine.
 */
void game_loop_cleanup(Game *game, Graphic_engine *gengine);

/**
 * @brief Main function of the game.
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return 0 if the game runs successfully, 1 otherwise.
 */
int main(int argc, char *argv[]) {
    Game *game = NULL;
    Graphic_engine *gengine = NULL;

    if (argc < 2) {
        fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
        return 1;
    }

    if (!game_loop_init(&game, &gengine, argv[1])) {
        game_loop_run(game, gengine);
        game_loop_cleanup(game, gengine);
    }

    game_destroy(game);
    return 0;
}

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name) {
    if (game_create(game) == ERROR) {
        fprintf(stderr, "Error while allocating memory for game.\n");
        return 1;
    }

    if (game_create_from_file(game, file_name) == ERROR) {
        fprintf(stderr, "Error while initializing game.\n");
        game_destroy(*game);
        return 1;
    }

    if ((*gengine = graphic_engine_create()) == NULL) {
        fprintf(stderr, "Error while initializing graphic engine.\n");
        game_destroy(*game);
        return 1;
    }

    return 0;
}

void game_loop_run(Game *game, Graphic_engine *gengine) {
    Command *last_cmd;

    if (!gengine) {
        return;
    }

    last_cmd = game_get_last_command(game);

    while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(game) == FALSE)) {
        graphic_engine_paint_game(gengine, game);
        command_get_user_input(last_cmd);
        game_actions_update(game, last_cmd);
    }
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine) {
    game_destroy(game);
    graphic_engine_destroy(gengine);
}
