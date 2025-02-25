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
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure to be initialized.
 * @param gengine A pointer to the graphic engine to be initialized.
 * @param file_name The name of the file containing the game data.
 * @return 0 if initialization is successful, 1 otherwise.
 */
int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name);

/**
 * @brief Runs the main game loop.
 * @author Profesores PPROG
 *
 * @param game The game structure.
 * @param gengine The graphic engine used to render the game.
 */
void game_loop_run(Game *game, Graphic_engine *gengine);

/**
 * @brief Cleans up resources used by the game loop.
 * @author Profesores PPROG
 *
 * @param game The game structure.
 * @param gengine The graphic engine.
 */
void game_loop_cleanup(Game *game, Graphic_engine *gengine);

/**
 * @brief Main function of the game.
 * @author Profesores PPROG
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return 0 if the game runs successfully, 1 otherwise.
 */
int main(int argc, char *argv[]) {
    Game *game = NULL;
    Graphic_engine *gengine;

    /* Check if the game data file is provided */
    if (argc < 2) {
        fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
        return 1;
    }

    /* Initialize the game loop */
    if (game_loop_init(&game, &gengine, argv[1]) == 0) {
        /* Run the game loop */
        game_loop_run(game, gengine);
        /* Clean up resources */
        game_loop_cleanup(game, gengine);
    }

    return 0;
}

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name) {
    /* Allocate memory for the game */
    if (game_create(game) == ERROR) {
        fprintf(stderr, "Error while allocating memory for game.\n");
        return 1;
    }

    /* Initialize the game from the file */
    if (game_create_from_file(game, file_name) == ERROR) {
        fprintf(stderr, "Error while initializing game.\n");
        free(*game);
        return 1;
    }

    /* Initialize the graphic engine */
    if ((*gengine = graphic_engine_create()) == NULL) {
        fprintf(stderr, "Error while initializing graphic engine.\n");
        game_destroy(*game);
        free(*game);
        return 1;
    }

    return 0;
}

void game_loop_run(Game *game, Graphic_engine *gengine) {
    Command *last_cmd;

    /* Check if the graphic engine is valid */
    if (!gengine) {
        return;
    }

    /* Get the last command from the game */
    last_cmd = game_get_last_command(game);

    /* Main game loop */
    while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(game) == FALSE)) {
        /* Render the game */
        graphic_engine_paint_game(gengine, game);
        /* Get user input */
        command_get_user_input(last_cmd);
        /* Update the game state based on the command */
        game_actions_update(game, last_cmd);
    }
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine) {
    /* Destroy the game */
    game_destroy(game);
    /* Free the game memory */
    free(game);
    /* Destroy the graphic engine */
    graphic_engine_destroy(gengine);
}
