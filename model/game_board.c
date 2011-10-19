#include "game_board.h"

/* création du plateau de jeu avec des valeurs fixées */
t_game_board* create_game_board (int nb_brick_x, int nb_brick_y)
{
    // 0. déclaration des variables
    t_game_board* pt = NULL;
    int i, j;

    // 1. allocation dynamique
    while(pt == NULL) pt = (t_game_board*)malloc(sizeof(t_game_board));

    // 2. initialisation des éléments simples
    pt->best_score = 0;
    pt->last_score = 0;
    pt->score = 0;
    pt->brick = NULL;
    pt->nb_brick_x = nb_brick_x;
    pt->nb_brick_y = nb_brick_y;

    // 3. allocation dynamique des éléments complexes
    while(pt->brick == NULL) pt->brick = (t_brick***)malloc((nb_brick_x)*sizeof(t_brick**));
    for(i=0; i<nb_brick_x; i++) pt->brick[i] = NULL;
    for(i=0; i<nb_brick_x; i++) {
        while(pt->brick[i] == NULL)
            pt->brick[i] = (t_brick**)malloc((nb_brick_y)*sizeof(t_brick*));
    }

    // 4. initialisation des éléments complexes
    for(i=0; i<nb_brick_x; i++)
        for(j=0; j<nb_brick_y; j++)
            pt->brick[i][j] = NULL;

    // 5. infos de debug
    if(DEBUG) printf("+ création du plateau de jeu\n");

    // 5. retour du pointeur
    return pt;
}

/* création du plateau de jeu avec des valeurs par défault */
t_game_board* create_game_board_with_default_value ()
{
    return create_game_board (50, 50);
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


void destroy_game_board_bricks_from_path(t_game_board* game_board, t_path* path)
{

}
