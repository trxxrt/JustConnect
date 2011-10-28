#include "const.h"

/* fonction servant à vérifier si un int est déjà présent dans un tableau d'int ou non */
gboolean is_in_int_table(int* table, int length, int n)
{
    int i = 0;
    for(i=0; i<length; i++) if(n == table[i]) return TRUE;
    return FALSE;
}

/* fonction servant à modifier la valeur d'un entier qui est contenu dans un label */
void edit_displayed_int_value(t_displayed_int* pt, int value)
{
    char buffer[10];

    pt->value = value;
    sprintf(buffer, "%d", value);
    gtk_label_set_text(GTK_LABEL(pt->label), buffer);
}
