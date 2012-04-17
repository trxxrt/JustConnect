#include "game_board.h"

/* création du plateau de jeu avec des valeurs fixées */
t_game_board* create_game_board (int nb_brick_x, int nb_brick_y, int rules)
{
    // 0. déclaration des variables
    t_game_board* pt = NULL;
    int i, j;

    // 1. infos de debug
    if(DEBUG) printf("+ création du plateau de jeu de taille %dx%d\n", nb_brick_x, nb_brick_y);

    // 2. allocation dynamique
    while(pt == NULL) pt = (t_game_board*)malloc(sizeof(t_game_board));

    // 3. initialisation des éléments simples
    pt->rules = rules;
    pt->is_running = TRUE;
    pt->best_score.value = 0;
    pt->last_score.value = 0;
    pt->score.value = 0;
    pt->best_score.label = NULL;
    pt->last_score.label = NULL;
    pt->score.label = NULL;
    pt->brick = NULL;
    pt->remaining_bricks.label = NULL;
    pt->remaining_bricks.value = 80;
    pt->nb_brick_x = nb_brick_x;
    pt->nb_brick_y = nb_brick_y;
    pt->table = NULL;
    pt->new_game_menu = NULL;
    pt->window = NULL;
    if(rules == SOLO_GAME_EASY) pt->color = rand()%MAX_NB_COLOR;
    pt->next_brick = create_random_brick(pt->rules, pt->color);

    // 4. réglage de l'aide des fonds colorés pour la gui
    if(rules == SOLO_GAME_EASY || rules == SOLO_GAME_MEDIUM) pt->gui_color_help =  TRUE;

    // 5. allocation dynamique des éléments complexes
    while(pt->brick == NULL) pt->brick = (t_brick***)malloc((nb_brick_x)*sizeof(t_brick**));
    for(i=0; i<nb_brick_x; i++) pt->brick[i] = NULL;
    for(i=0; i<nb_brick_x; i++) {
        while(pt->brick[i] == NULL)
            pt->brick[i] = (t_brick**)malloc((nb_brick_y)*sizeof(t_brick*));
    }

    // 6. initialisation des éléments complexes
    for(i=0; i<nb_brick_x; i++)
        for(j=0; j<nb_brick_y; j++)
            pt->brick[i][j] = create_empty_brick();

    // 7. retour du pointeur
    return pt;
}

/* création du plateau de jeu avec des valeurs par défault */
t_game_board* create_game_board_with_default_value ()
{
    return create_game_board (9, 9, SOLO_GAME_MEDIUM);
}

/* suppression du plateau de jeu */
void delete_game_board(t_game_board* game)
{
    // 0. déclaration des variables
    int i = 0, j = 0;

    // 1. suppression des bricks
    for(i=0; i<game->nb_brick_x; i++)
        for(j=0; j<game->nb_brick_y; j++)
            delete_brick(game->brick[i][j]);

    // 2. suppression du plateau de jeu
    free(game);

    // 3. infos de debug
    if(DEBUG) printf("- suppression du plateau de jeu\n");
}


void destroy_game_board_bricks_from_path(t_game_board* pt, int** tab_test, t_color* color)
{
    // 0. création des variables locales
    int i, j, k, l;
    t_color** temp = NULL;
    int nb_stick_to_keep = 0;
    int nb_color = 0;
    int nb_deleted_brick = 0;
    int score_to_be_added = 0;
    t_brick* temp_brick = NULL;

    // 1. suppression des bricks de la boucle ouverte
    for (i=0; i< pt->nb_brick_x; i++)
    {
        for (j=0; j< pt->nb_brick_y; j++)
        {
            if (tab_test[i][j] == 1)
            {
                get_different_colors_from_brick(pt->brick[i][j], &temp, &nb_color);

                // 1.1 si il n'y a qu'une seule couleur, on crée une nouvelle brick vide
                if(nb_color == 1)
                {
                    temp_brick = create_empty_brick();
                    temp_brick->image = pt->brick[i][j]->image;
                    pt->brick[i][j] = temp_brick;
                    on_brick_table_expose_event(pt->brick[i][j]->image, NULL, (gpointer)pt);
                    nb_deleted_brick++;
                }

                // 1.2 sinon on reprend les anciens sticks
                else
                {
                    nb_stick_to_keep = 0;
                    for(k=0; k<pt->brick[i][j]->nb_stick; k++)
                        if(!is_same_color(pt->brick[i][j]->stick[k].color, color))
                            nb_stick_to_keep++;

                    temp_brick = create_brick(FALSE, ATTACHED_BRICK, create_stick_table(nb_stick_to_keep), nb_stick_to_keep);

                    l = -1;
                    for(k=0; k<pt->brick[i][j]->nb_stick; k++)
                    {
                        if(!is_same_color(pt->brick[i][j]->stick[k].color, color))
                        {
                            l++;
                            temp_brick->stick[l].direction = pt->brick[i][j]->stick[k].direction;
                            temp_brick->stick[l].color = copy_color(pt->brick[i][j]->stick[k].color);
                        }
                    }

                    temp_brick->image = pt->brick[i][j]->image;
                    pt->brick[i][j] = temp_brick;
                    on_brick_table_expose_event(pt->brick[i][j]->image, NULL, (gpointer)pt);
                    nb_deleted_brick++;
                }
            }
        }
    }

    // 2. incrémentation du score
    score_to_be_added = nb_deleted_brick;
    if(pt->rules == SOLO_GAME_MEDIUM || pt->rules == SOLO_GAME_HARD) score_to_be_added *= nb_deleted_brick;
    if(pt->rules == SOLO_GAME_HARD) score_to_be_added *= nb_deleted_brick;

    // 3. dans le cas où il ne restait pas de brick, on re-genere la brick suivante
    if(pt->remaining_bricks.value == 0 && pt->rules != SOLO_GAME_HARD)
    {
        temp_brick = create_random_brick(pt->rules, pt->color);
        temp_brick->image = pt->next_brick->image;
        pt->next_brick = temp_brick;
        g_signal_connect(pt->next_brick->image, "expose-event", G_CALLBACK(on_next_brick_expose_event), pt->next_brick);
        on_next_brick_expose_event(pt->next_brick->image, NULL, pt->next_brick);
    }

    // 4. raffraichissement de l'affichage
    edit_displayed_int_value(&pt->score, pt->score.value+score_to_be_added);
    edit_displayed_int_value(&pt->last_score, score_to_be_added);
    edit_displayed_int_value(&pt->remaining_bricks, pt->remaining_bricks.value + nb_deleted_brick/2);
    if(score_to_be_added > pt->best_score.value) edit_displayed_int_value(&pt->best_score, score_to_be_added);

    // 5. debug
    if(DEBUG) printf("score obtenu : %d\n+ ajout de %d bricks dans la pioche\n", score_to_be_added, nb_deleted_brick/2);
}
