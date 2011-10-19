#ifndef MODEL_STICK_H
#define MODEL_DIRECTION_H

// 0. inclusion des librairies
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../shared/const.h"

// 1. déclaration des structures
typedef struct struct_stick
{
    int direction;
    int color;
    GtkWidget* picture;
}t_stick;

// 2. déclaration des fonctions
t_stick* create_stick_table (int nb);
t_stick* copy_stick_table(t_stick* stick, int nb_stick);
gboolean are_same_stick_table(t_stick* stick1, int nb1, t_stick* stick2, int nb2);
t_stick* fusion_sticks_table(t_stick* stick1, int nb1, t_stick* stick2, int nb2);
void set_stick_informations(int color, int direction, t_stick* stick);

#endif
