#ifndef VIEW_BEST_SCORE_H
#define VIEW_BEST_SCORE_H

// 0. inclusion des librairies
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../shared/const.h"
#include <string.h>

#define MAX_PSEUDO_LENGTH 50

typedef struct my_best_score_item
{
    int score;
    char pseudo[MAX_PSEUDO_LENGTH];
    GtkWidget* label;
}t_best_score_item;

typedef struct my_best_score
{
    t_best_score_item* scores;
    int nb;
}t_best_score;

// 1. déclaration des fonctions
void display_best_score(GtkWidget* win);
t_best_score* load_best_scores();
void save_best_scores(t_best_score* list);
gboolean is_a_best_score(t_best_score* list, int score);
t_best_score* insert_in_best_score(t_best_score* list, int score, char* pseudo);

#endif

