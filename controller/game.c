#include "game.h"

int game (GtkWidget *wid, GtkWidget *win)
{
    t_game_board* game = NULL;
    t_brick* brick = NULL ;
    t_stick* stick = NULL;

    game = create_game_board_with_default_value();
    brick = create_random_brick();
    game->brick[0][0] = brick;
    stick = create_stick_table(5);
    //set_stick_informations(RED, TOP, stick);
    //delete_game_board(game);


    display_game(game);
    return 0;
}
