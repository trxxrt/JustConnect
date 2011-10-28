#ifndef CONTROL_GAME_H
#define CONTROL_GAME_H

// 0. inclusion des librairies
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../view/game.h"
#include "../model/game_board.h"

// 1. déclaration des fonctions
int game ();
int detect_looped_brick (int init, int* tab_test[], t_game_board * pt, int pos_x, int pos_y, int direction_of_parent);
gboolean on_brick_click_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt);
gboolean on_next_brick_click_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt);
int check_relationship_beetween_bricks(t_game_board* pt, int pos_x, int pos_y, int direction);
extern gboolean on_next_brick_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt);
extern gboolean on_brick_table_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt);

#endif
