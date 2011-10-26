#ifndef CONTROL_GAME_H
#define CONTROL_GAME_H

// 0. inclusion des librairies
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../view/game.h"
#include "../model/game_board.h"

// 1. déclaration des fonctions
int game (GtkWidget *wid, GtkWidget *win);
gboolean on_brick_click_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt);

#endif
