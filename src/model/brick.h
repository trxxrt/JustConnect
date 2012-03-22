#ifndef MODEL_BRICK_H
#define MODEL_BRICK_H

// 0. inclusion des librairies
#include <stdlib.h>
#include <gtk/gtk.h>
#include <math.h>
#include "../shared/const.h"
#include "stick.h"

#define UNATTACHED_BRICK 1
#define EMPTY_BRICK 2
#define ATTACHED_BRICK 3
#define UNBREAKABLE_BRICK 4

#define GAME_DEFAULT_SIZE_OF_BRICK 40

// 1. déclaration des structures
typedef struct struct_brick
{
    t_stick* stick;
    int nb_stick;
    gboolean turnable;
    int type;
    GtkWidget* image;
}t_brick;

// 2. déclaration des fonctions
t_brick* create_brick (gboolean turnable, int type, t_stick* stick, int nb_stick);
t_brick* create_random_brick (int rules, int color);
t_brick* create_empty_brick ();
void delete_brick (t_brick* brick);
t_brick* copy_brick (t_brick* brick);
gboolean are_same_brick (t_brick* brick1, t_brick* brick2);
gboolean are_superposable_bricks (t_brick* brick1, t_brick* brick2);
gboolean is_turnable_brick (t_brick* brick);
gboolean is_empty_brick(t_brick* brick);
int fusion_bricks (t_brick* brick1, t_brick* brick2, t_brick** destination, int new_type);
int turn_brick(t_brick* brick);
void get_different_colors_from_brick(t_brick* brick, t_color*** colors, int* nb_color);
extern gboolean on_brick_table_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt);
extern gboolean on_next_brick_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt);

#endif
