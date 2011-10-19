#ifndef MODEL_BRICK_H
#define MODEL_BRICK_H

// 0. inclusion des librairies
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../shared/const.h"
#include "stick.h"

// 1. déclaration des structures
typedef struct struct_brick
{
    t_stick* stick;
    int nb_stick;
    int turnable;
    GtkWidget* button;
    GtkWidget* image;
}t_brick;

// 2. déclaration des fonctions
t_brick* create_brick (int turnable, t_stick* stick, int nb_stick);
t_brick* create_random_brick ();
void delete_brick (t_brick* brick);
t_brick* copy_brick (t_brick* brick);
gboolean are_same_brick (t_brick* brick1, t_brick* brick2);
gboolean are_superposable_bricks (t_brick* brick1, t_brick* brick2);
gboolean is_turnable_brick (t_brick* brick);
int fusion_bricks (t_brick* brick1, t_brick* brick2, t_brick** destination);
int turn_brick(t_brick* brick);

#endif
