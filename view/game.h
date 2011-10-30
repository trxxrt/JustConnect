#ifndef VIEW_GAME_H
#define VIEW_GAME_H

// 0. inclusion des librairies
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../model/game_board.h"
#include "game_launcher.h"
#include "about.h"
#include "best_score.h"

#define WHITE_BACKGROUND 0
#define GREEN_BACKGROUND 1
#define RED_BACKGROUND 2

// 1. déclaration des fonctions
void display_game (t_game_board* game);
void display_new_game (t_game_board* old_game, t_game_board* new_game);
extern gboolean on_brick_click_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt);
extern gboolean on_next_brick_click_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt);
extern int detect_looped_brick (int init, int* tab_test[], t_game_board * pt, int pos_x, int pos_y, int direction_of_parent);
gboolean on_brick_table_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt);
gboolean on_next_brick_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt);
void draw_cairo_surface_from_brick(cairo_t* cr, t_brick* brick, int width, int height, int background_color);

#endif
