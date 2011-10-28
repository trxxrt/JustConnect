#include "game.h"

/* fonction de lancement du jeu */
int game ()
{
    t_game_board* game = NULL;

    game = create_game_board_with_default_value();

    display_game(game);
    return 0;
}

/* fonction appelée lors d'un click sur une brick */
gboolean on_brick_click_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt)
{
    // 0 déclaration de variables et initialisations
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

        // 3.4 décrémentation de la pile de pioche
        edit_displayed_int_value(&game->remaining_bricks, game->remaining_bricks.value-1);
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

        // 4.4 décrémentation de la pile de la pioche
        edit_displayed_int_value(&game->remaining_bricks, game->remaining_bricks.value-1);
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

/* fonction recursive de détéction de boucle fermée */
int detect_looped_brick (int init, int* tab_test[], t_game_board * pt, int pos_x, int pos_y, int direction_of_parent)
{
    int i;
    int reciprocal_result = 1;
    int next_x = pos_x, next_y = pos_y, next_direction = 0;
    int direction_result = 1;

    tab_test[pos_x][pos_y] = 1;

    if (pt->brick[pos_x][pos_y]->nb_stick > 0)
    {
        if(!init) reciprocal_result = check_relationship_beetween_bricks(pt, pos_x, pos_y, direction_of_parent);

        for(i=0; i <pt->brick[pos_x][pos_y]->nb_stick; i++)
        {
            next_x = pos_x; next_y = pos_y;

            switch(pt->brick[pos_x][pos_y]->stick[i].direction)
            {
                case BOTTOM:
                    next_direction = TOP;
                    if (pos_y < pt->nb_brick_y-1) next_y = pos_y+1;
                    else next_y = 0;
                break;

                case TOP:
                    next_direction = BOTTOM;
                    if (pos_y > 0) next_y = pos_y-1;
                    else next_y = pt->nb_brick_y-1;
                break;

                case RIGHT:
                    next_direction = LEFT;
                    if (pos_x < pt->nb_brick_x - 1) next_x = pos_x+1;
                    else next_x = 0;
                break;

                case LEFT:
                    next_direction = RIGHT;
                    if (pos_x > 0) next_x = pos_x-1;
                    else next_x = pt->nb_brick_x-1;
                break;

                default:
                next_direction = MAX_NB_DIRECTION+1;
                printf("problem : unexpeted default on switch");
                break;
            }

            if(tab_test[next_x][next_y] == 0) direction_result = direction_result && detect_looped_brick (FALSE, tab_test, pt, next_x, next_y, next_direction);
            else direction_result = direction_result && check_relationship_beetween_bricks(pt, next_x, next_y, next_direction);
        }
        return (direction_result && reciprocal_result);
    }
    return 0;
}

/* fonction de rotation de la prochaine brick en cas de clic dessus */
gboolean on_next_brick_click_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt)
{
    t_game_board* game = (t_game_board*)pt;
    if(turn_brick(game->next_brick)) on_next_brick_expose_event(game->next_brick->image, NULL, game->next_brick);
    return FALSE;
}

/* fonction servat à vérifier qu'un fils a bien une realtion avec le aprent qui l'a appelé */
int check_relationship_beetween_bricks(t_game_board* pt, int pos_x, int pos_y, int direction)
{
    int i =0;

    for(i=0; i <pt->brick[pos_x][pos_y]->nb_stick; i++)
        if(pt->brick[pos_x][pos_y]->stick[i].direction == direction) return 1;

    return 0;
}
