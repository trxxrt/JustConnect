#ifndef MODEL_PATH_H
#define MODEL_GAME_BOARD_H

// 0. inclusion des librairies
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../shared/const.h"
#include "brick.h"

// 1. déclaration des structures
typedef struct struct_path
{
    int nb_brick;
    GList* list;
}t_path;

// 2. déclaration des fonctions
t_path* create_path();
void destroy_path(t_path* path);
void add_brick_to_patch(t_brick* brick, t_path* path);
void remove_brick_from_path(t_brick* brick, t_path* path);

#endif
