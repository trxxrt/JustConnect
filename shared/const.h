#ifndef SHARED_CONST_H
#define SHARED_CONST_H

// 0. définition de constantes génériques
#define DEBUG 1

// 1. inclusions des autres .h de constantes
#include <gtk/gtk.h>
#include "color.h"
#include "direction.h"

// 1. déclaration des fonctions génériques
gboolean is_in_int_table(int* table, int length, int n);

#endif
