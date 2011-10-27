#include "game.h"

/* fonction de lancement du jeu */
int game (GtkWidget *wid, GtkWidget *win)
{
    t_game_board* game = NULL;

    game = create_game_board_with_default_value();

    display_game(game);
    return 0;
}

/* fonction appelée lors d'un click sur une brick */
gboolean on_brick_click_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt)
{
    // 0 déclaration de variables
    int i = 0, j = 0;
    int x = 0, y = 0;
    int is_closed_path = 0;
    t_brick* temp_brick = NULL;
    t_game_board* game = (t_game_board*)pt;
    int** tab_test = (int**)malloc(game->nb_brick_x*sizeof(int*));
    for(i=0; i<game->nb_brick_x; i++) tab_test[i] = (int*)malloc(game->nb_brick_y*sizeof(int));

    for (i=0; i < game->nb_brick_x; i++)
        for (j=0; j < game->nb_brick_y; j++)
            tab_test[i][j] = 0;

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

        // 3.1 copie de la nouvelle brick sur le plateau
        temp_brick = copy_brick(game->next_brick);
        temp_brick->image = game->brick[x][y]->image;
        game->brick[x][y] = temp_brick;
        game->brick[x][y]->type = ATTACHED_BRICK;

        // 3.2 création d'une nouvelle brick dans la pile
        temp_brick = create_random_brick();
        temp_brick->image = game->next_brick->image;
        game->next_brick = temp_brick;

        // 3.3 raffraichssement de l'affichage
        g_signal_connect(game->next_brick->image, "expose-event", G_CALLBACK(on_next_brick_expose_event), game->next_brick);
        on_brick_table_expose_event(game->brick[x][y]->image, NULL, game);
        on_next_brick_expose_event(game->next_brick->image, NULL, game->next_brick);
        return FALSE;
    }

    // 4. cas n°2 : il y a fusion possible entre la brique suivante et la brique déjà en place
    if(are_superposable_bricks(game->brick[x][y], game->next_brick))
    {
        if(DEBUG) printf("fusion des 2 bricks\n");

        // 4.1 fusion des 2 bricks
        fusion_bricks(game->brick[x][y], game->next_brick, &temp_brick, ATTACHED_BRICK);
        temp_brick->image = game->brick[x][y]->image;
        game->brick[x][y] = temp_brick;

        // 4.2 création d'une nouvelle brick
        temp_brick = create_random_brick();
        temp_brick->image = game->next_brick->image;
        game->next_brick = temp_brick;

        // 4.3 raffraichissement de l'affichage
        g_signal_connect(game->next_brick->image, "expose-event", G_CALLBACK(on_next_brick_expose_event), game->next_brick);
        on_brick_table_expose_event(game->brick[x][y]->image, NULL, game);
        on_next_brick_expose_event(game->next_brick->image, NULL, game->next_brick);
        return FALSE;
    }

    // 5. cas n°3 : on recherche à savoir si une boucle est bouclée
    if(DEBUG) printf("recherche de boucle fermée\n");

    is_closed_path = detect_looped_brick (TRUE, tab_test, game, x, y, 0);

    if(is_closed_path)
    {
        if(DEBUG) printf("boucle fermée\n");
        destroy_game_board_bricks_from_path(game, tab_test);
    }
    else if(DEBUG) printf("boucle ouverte\n");

    return FALSE;
}


int detect_looped_brick (int init, int* tab_test[], t_game_board * pt, int pos_x, int pos_y, int direction_of_parent)
{
    int i;
    int reciprocal_result = 1;
    int bottom_result = 1, top_result = 1, right_result = 1, left_result = 1;

    tab_test[pos_x][pos_y] = 1;

    if (pt->brick[pos_x][pos_y]->nb_stick > 0)
    {
        if(!init)
        {
            reciprocal_result = 0;
            for(i=0; i <pt->brick[pos_x][pos_y]->nb_stick; i++)
                if(pt->brick[pos_x][pos_y]->stick[i].direction == direction_of_parent) reciprocal_result = 1;
        }

        for(i=0; i <pt->brick[pos_x][pos_y]->nb_stick; i++)
        {
            switch(pt->brick[pos_x][pos_y]->stick[i].direction)
            {
                case BOTTOM:
                    if (pos_y < pt->nb_brick_y-1) { if(tab_test[pos_x][pos_y+1] == 0) bottom_result = detect_looped_brick (FALSE, tab_test, pt, pos_x, pos_y+1, TOP); }
                    else if ( pos_y == pt->nb_brick_y-1) if(tab_test[pos_x][0] == 0) bottom_result = detect_looped_brick (FALSE, tab_test, pt, pos_x, 0, TOP );
                break;

                case TOP:
                    if (pos_y > 0) { if(tab_test[pos_x][pos_y-1] == 0) top_result = detect_looped_brick (FALSE, tab_test, pt, pos_x, pos_y-1, BOTTOM ); }
                    else if ( pos_y == 0 ) if(tab_test[pos_x][pt->nb_brick_y-1] == 0) bottom_result = detect_looped_brick (FALSE, tab_test, pt, pos_x, pt->nb_brick_y - 1, BOTTOM);
                break;

                case RIGHT:
                    if (pos_x < pt->nb_brick_x - 1) { if(tab_test[pos_x+1][pos_y] == 0) right_result = detect_looped_brick (FALSE, tab_test, pt, pos_x+1, pos_y, LEFT ); }
                    else if ( pos_x == pt->nb_brick_x - 1) if(tab_test[0][pos_y] == 0) bottom_result = detect_looped_brick (FALSE, tab_test, pt, 0, pos_y, LEFT );
                break;

                case LEFT:
                    if (pos_x > 0) { if(tab_test[pos_x-1][pos_y] == 0) left_result = detect_looped_brick (FALSE, tab_test, pt, pos_x-1, pos_y, RIGHT ); }
                    else if ( pos_x == 0) if(tab_test[pt->nb_brick_x-1][pos_y] == 0) left_result = detect_looped_brick (FALSE, tab_test, pt, pt->nb_brick_x-1, pos_y, RIGHT );
                break;

                default:
                printf("problem : unexpeted default on switch");
                break;
            }
        }
        return (bottom_result && top_result && right_result && left_result && reciprocal_result);
    }
    return 0;
}

gboolean on_next_brick_click_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt)
{
    t_game_board* game = (t_game_board*)pt;
    if(turn_brick(game->next_brick)) on_next_brick_expose_event(game->next_brick->image, NULL, game->next_brick);
    return FALSE;
}
