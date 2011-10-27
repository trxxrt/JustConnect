#ifndef VIEW_GAME_H
#define VIEW_GAME_H

// 0. inclusion des librairies
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../model/game_board.h"

// 1. déclaration des fonctions
void display_game (t_game_board* game);
extern gboolean on_brick_click_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt);
extern gboolean on_next_brick_click_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt);
gboolean on_brick_table_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt);
gboolean on_next_brick_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt);
void draw_cairo_surface_from_brick(cairo_t* cr, t_brick* brick, int width, int height);

#endif
