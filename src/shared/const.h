#ifndef SHARED_CONST_H
#define SHARED_CONST_H

// 0. définition de constantes génériques
#define UTF8(string) g_locale_to_utf8(string, -1, NULL, NULL, NULL)

#define DEBUG 0

#define SOLO_GAME_EASY 1
#define SOLO_GAME_MEDIUM 2
#define SOLO_GAME_HARD 3
#define SOLO_GAME_CUSTOM 4

// 1. inclusions des autres .h de constantes
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "color.h"
#include "direction.h"

typedef struct my_displayed_int
{
    int value;
    GtkWidget* label;
}t_displayed_int;

// 1. déclaration des fonctions génériques
gboolean is_in_int_table(int* table, int length, int n);
void edit_displayed_int_value(t_displayed_int* pt, int value);
void gtk_widget_destroy_from_callback(GtkWidget* win, GtkWidget* wid);

#endif
