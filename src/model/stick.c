#include "stick.h"

/*fonction de création d'un tableau de sticks*/
t_stick* create_stick_table (int nb)
{
    // 0. déclaration des variables
    t_stick* pt = NULL;
    int i = 0;

    // 1. création du tableau dynamique
    while(pt == NULL) pt = (t_stick*)malloc(nb*sizeof(t_stick));

    // 2. initialisation de chaque stick du tableau
    for(i=0; i<nb; i++)
        pt[i].direction = 0;

    // 3.infos de debug
    if(DEBUG) printf("+ création d'une nouvelle table de %d stick(s)\n", nb);

    // 4. retour de la valeur
    return pt;
}

/*fonction de copie de tableaux de sticks*/
t_stick* copy_stick_table(t_stick* stick, int nb_stick)
{
    // 0. déclaration des variables
    int i = 0;
    t_stick* pt = NULL;

    // 1. création du nouveau stick
    pt = create_stick_table(nb_stick);

    // 2. copie des informations dans le nouveau tablau de sticks
    for(i=0; i<nb_stick; i++)
    {
        pt[i].color = copy_color(stick[i].color);
        pt[i].direction = stick[i].direction;
    }

    // 3. infos de debug
    if(DEBUG) printf("+ copie d'un tableau de sticks\n");

    // 4. on retourne l'adresse de la nouvelle valeur
    return pt;
}

/*fonction de comparaison de 2 tableaux de sticks*/
gboolean are_same_stick_table(t_stick* stick1, int nb1, t_stick* stick2, int nb2)
{
    // 0. déclaration des variables
    int i = 0;

    // 1. infos de debug
    if(DEBUG) printf("> comparaison de 2 tables de sticks\n");

    // 1. test de comparaison des tableaux
    if(nb1 == nb2)
    {
        for(i=0; i<nb1; i++)
        {
            // 2. si quelque chose est différent on retourne 0
            if(!is_same_color(stick1[i].color, stick2[i].color)) return FALSE;
            if(stick2[i].direction != stick2[i].direction) return FALSE;
        }
        // 3. sinon tout est bon
        return TRUE;
    }
    else return FALSE;
}

/*fonction de fusion de tableaux de sticks*/
t_stick* fusion_sticks_table(t_stick* stick1, int nb1, t_stick* stick2, int nb2)
{
    // 0. déclaration des variables
    t_stick* pt = NULL;
    int i = 0;

    // 1. allocatioon dynamique
    pt = create_stick_table(nb1+nb2);

    // 2. fusion
    for(i=0; i<nb1; i++)
    {
        pt[i].color = copy_color(stick1[i].color);
        pt[i].direction = stick1[i].direction;
    }
    for(i=nb1; i<nb2+nb1; i++)
    {
        pt[i].color = copy_color(stick2[i-nb1].color);
        pt[i].direction = stick2[i-nb1].direction;
    }

    // 3. info de debug
    if(DEBUG) printf("-> fusion de 2 tableaux de sticks\n");

    // 4. on retourne la valeur
    return pt;
}

/* fonction d'update des infos d'un stick */
void set_stick_informations(t_stick* stick, t_color* color, int direction)
{
    // 0. mise à jour des infos du stick
    stick->color = color;
    stick->direction = direction;
}
