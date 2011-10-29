#ifndef MODEL_GAME_BOARD_H
#define MODEL_GAME_BOARD_H

// 0. inclusion des librairies
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../shared/const.h"
#include "brick.h"

#define SOLO_GAME_EASY 1
#define SOLO_GAME_MEDIUM 2
#define SOLO_GAME_HARD 3
#define SOLO_GAME_CUSTOM 4

#define VERSUS_GAME 10

#define GAME_DEFAULT_SIZE_OF_BRICK 40

// 1. déclaration des structures
typedef struct struct_game_board
{
    int rules;
    int nb_brick_x;
    int nb_brick_y;
    gboolean gui_color_help;
    t_displayed_int score;
    t_displayed_int last_score;
    t_displayed_int best_score;
    t_displayed_int remaining_bricks;
    GtkWidget* table;
    GtkWidget* new_game_menu;
    t_brick* next_brick;
    t_brick*** brick;
}t_game_board;

// 2. déclaration des fonctions
t_game_board* create_game_board (int nb_brick_x, int nb_brick_y, int rules);
t_game_board* create_game_board_with_default_value ();
void delete_game_board(t_game_board* game);
void destroy_game_board_bricks_from_path(t_game_board* pt, int** tab_test);

#endif
