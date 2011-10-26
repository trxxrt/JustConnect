#include "game.h"

/* fonction de lancement du jeu */
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

/* fonction appelée lors d'un click sur une brick */
gboolean on_brick_click_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt)
{
    int i = 0, j = 0;
    int x = 0, y = 0;
    t_brick* temp_brick = NULL;
    t_game_board* game = (t_game_board*)pt;

    for(i=0; i<game->nb_brick_x; i++)
    {
        for(j=0; j<game->nb_brick_y; j++)
        {
            if(game->brick[i][j]->image == widget)
            {
                x = i;
                y = j;
            }
        }
    }

    printf("click sur la brick (%d, %d) !\n", x, y);

    if(is_empty_brick(game->brick[x][y]))
    {
        temp_brick = copy_brick(game->next_brick);
        temp_brick->image = game->brick[x][y]->image;
        game->brick[x][y] = temp_brick;
        temp_brick = create_random_brick();
        temp_brick->image = game->next_brick->image;
        game->next_brick = temp_brick;
        on_brick_table_expose_event(game->brick[x][y]->image, NULL, game);
        on_next_brick_expose_event(game->next_brick->image, NULL, game->next_brick);
    }

    return FALSE;
}
