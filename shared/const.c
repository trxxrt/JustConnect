#include "const.h"

/* fonction servant à vérifier si un int est déjà présent dans un tableau d'int ou non */
gboolean is_in_int_table(int* table, int length, int n)
{
    int i = 0;
    for(i=0; i<length; i++) if(n == table[i]) return TRUE;
    return FALSE;
}
