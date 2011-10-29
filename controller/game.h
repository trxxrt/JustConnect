#ifndef CONTROL_GAME_H
#define CONTROL_GAME_H

// 0. inclusion des librairies
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../view/game.h"
#include "../model/game_board.h"

// 1. déclaration des fonctions
int game ();
int new_game(t_game_board* old_game, int rules, int size_x, int size_y);
int detect_looped_brick (int init, int* tab_test[], t_game_board * pt, int pos_x, int pos_y, int direction_of_parent);
gboolean on_brick_click_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt);
gboolean on_next_brick_click_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt);
int check_relationship_beetween_bricks(t_game_board* pt, int pos_x, int pos_y, int direction);
void game_over(t_game_board* game);
extern gboolean on_next_brick_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt);
extern gboolean on_brick_table_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt);
extern void update_display_game_to_new(t_game_board* old_game, t_game_board* new_game);

#endif
