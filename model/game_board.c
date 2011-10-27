#include "game_board.h"

/* création du plateau de jeu avec des valeurs fixées */
t_game_board* create_game_board (int nb_brick_x, int nb_brick_y)
{
    // 0. déclaration des variables
    t_game_board* pt = NULL;
    int i, j;

    // 1. infos de debug
    if(DEBUG) printf("+ création du plateau de jeu de taille %dx%d\n", nb_brick_x, nb_brick_y);

    // 2. allocation dynamique
    while(pt == NULL) pt = (t_game_board*)malloc(sizeof(t_game_board));

    // 3. initialisation des éléments simples
    pt->best_score.value = 0;
    pt->last_score.value = 0;
    pt->score.value = 0;
    pt->best_score.label = NULL;
    pt->last_score.label = NULL;
    pt->score.label = NULL;
    pt->brick = NULL;
    pt->nb_brick_x = nb_brick_x;
    pt->nb_brick_y = nb_brick_y;
    pt->next_brick = create_random_brick();

    // 4. allocation dynamique des éléments complexes
    while(pt->brick == NULL) pt->brick = (t_brick***)malloc((nb_brick_x)*sizeof(t_brick**));
    for(i=0; i<nb_brick_x; i++) pt->brick[i] = NULL;
    for(i=0; i<nb_brick_x; i++) {
        while(pt->brick[i] == NULL)
            pt->brick[i] = (t_brick**)malloc((nb_brick_y)*sizeof(t_brick*));
    }

    // 5. initialisation des éléments complexes
    for(i=0; i<nb_brick_x; i++)
        for(j=0; j<nb_brick_y; j++)
            pt->brick[i][j] = create_empty_brick();

    // 6. retour du pointeur
    return pt;
}

/* création du plateau de jeu avec des valeurs par défault */
t_game_board* create_game_board_with_default_value ()
{
    return create_game_board (10, 10);
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


void destroy_game_board_bricks_from_path(t_game_board* pt, int** tab_test)
{
    // 0. création des variables locales
    int i, j;
    char label[5];
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
                temp_brick = create_empty_brick();
                temp_brick->image = pt->brick[i][j]->image;
                pt->brick[i][j] = temp_brick;
                on_brick_table_expose_event(pt->brick[i][j]->image, NULL, (gpointer)pt);
                nb_deleted_brick++;
            }
        }
    }

    // 2. incrémentation du score
    score_to_be_added = nb_deleted_brick*nb_deleted_brick;
    pt->score.value += score_to_be_added;
    pt->last_score.value = score_to_be_added;
    if(score_to_be_added > pt->best_score.value) pt->best_score.value = score_to_be_added;

    // 3. raffraichssement de l'affichage
    sprintf(label, "%d", pt->score.value);
    gtk_label_set_text(GTK_LABEL(pt->score.label), label);
    sprintf(label, "%d", pt->best_score.value);
    gtk_label_set_text(GTK_LABEL(pt->best_score.label), label);
    sprintf(label, "%d", pt->last_score.value);
    gtk_label_set_text(GTK_LABEL(pt->last_score.label), label);
}
