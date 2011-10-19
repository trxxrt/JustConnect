#include "path.h"

/* fonction de création d'un chemin */
t_path* create_path()
{
    // 0. déclaration des variables
    t_path* pt = NULL;

    // 1. intialisation
    while(pt == NULL) pt = (t_path*)malloc(sizeof(t_path));

    // 2. retour du pointeur
    return pt;
}

/* fonction de destruction d'un chemin */
void destroy_path(t_path* path)
{
    // 0. suppresion du path
    free(path);
}

/* fonction d'ajout d'une brick dans chemin */
void add_brick_to_patch(t_brick* brick, t_path* path)
{
    path->list = g_list_append(path->list, brick);
    path->nb_brick++;
}

void remove_brick_from_path(t_brick* brick, t_path* path)
{
    path-> list = g_list_remove(path->list, brick);
    if(path->nb_brick !=0) path->nb_brick--;
}
