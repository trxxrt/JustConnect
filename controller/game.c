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
    // 0 déclaration de variables
    int i = 0, j = 0;
    int x = 0, y = 0;
    t_brick* temp_brick = NULL;
    t_game_board* game = (t_game_board*)pt;

    // 1. recherche de la brick appellée par le click
    for(i=0; i<game->nb_brick_x; i++)
        for(j=0; j<game->nb_brick_y; j++)
            if(game->brick[i][j]->image == widget) { x = i; y = j; }

    // 2. info de debug générique
    if(DEBUG) printf("click sur la brick (%d, %d) : ", x, y);

    // 3. cas n°1 : la brique est vide
    if(is_empty_brick(game->brick[x][y]))
    {
        if(DEBUG) printf("ajout de la brick sur le plateau\n");
        temp_brick = copy_brick(game->next_brick);
        temp_brick->image = game->brick[x][y]->image;
        game->brick[x][y] = temp_brick;
        temp_brick = create_random_brick();
        temp_brick->image = game->next_brick->image;
        game->next_brick = temp_brick;
        g_signal_connect(game->next_brick->image, "expose-event", G_CALLBACK(on_next_brick_expose_event), game->next_brick);
        on_brick_table_expose_event(game->brick[x][y]->image, NULL, game);
        on_next_brick_expose_event(game->next_brick->image, NULL, game->next_brick);
        return FALSE;
    }

    // 4. cas n°2 : il y a fusion possible entre la brique suivante et la brique déjà en place
    if(are_superposable_bricks(game->brick[x][y], game->next_brick))
    {
        if(DEBUG) printf("fusion des 2 bricks\n");
        fusion_bricks(game->brick[x][y], game->next_brick, &temp_brick);
        temp_brick->image = game->brick[x][y]->image;
        game->brick[x][y] = temp_brick;
        temp_brick = create_random_brick();
        temp_brick->image = game->next_brick->image;
        game->next_brick = temp_brick;
        g_signal_connect(game->next_brick->image, "expose-event", G_CALLBACK(on_next_brick_expose_event), game->next_brick);
        on_brick_table_expose_event(game->brick[x][y]->image, NULL, game);
        on_next_brick_expose_event(game->next_brick->image, NULL, game->next_brick);
        return FALSE;
    }

    // 5. cas n°3 : on recherche à savoir si une boucle est bouclée
    if(DEBUG) printf("recherche de boucle fermée\n");

    return FALSE;
}
