#include "brick.h"

/* fonction de création d'un brick */
t_brick* create_brick (int turnable, t_stick* stick, int nb_stick)
{
    // 0. déclaration des variables
    t_brick* pt = NULL;

    // 1. allocation dynamique
    while(pt == NULL) pt = (t_brick*)malloc(sizeof(t_brick));

    // 2. allocation dynamique des éléments dynamiques
    pt->stick = stick;

    // 3. affectation des variables
    pt->nb_stick = nb_stick;
    pt->turnable = turnable;
    pt->image = NULL;
    // TODO (jc#1#): ajouter la fusion des images à partir de celles des sticks
    pt->button = NULL;
    // TODO (jc#1#): créer le bouton avec comme fond l'image de la brick

    // 4. infos de debug
    if(DEBUG) printf("+ création d'une nouvelle brick\n");

    // 5. retour de la variable dynamique
    return pt;
}

/* fonction de création d'une brick aléatoire */
t_brick* create_random_brick ()
{
    // 0. déclaration des variables et initialisation
    int i = 0;
    int temp_direction;
    int turnable = 0;
    t_stick* stick = NULL;
    int nb_stick = 0;
    int taken_value[MAX_NB_DIRECTION];
    for(i=0; i<MAX_NB_DIRECTION; i++) taken_value[i] = -1;

    // 1. génération aléatoire de turnable : 0 ou 1
    turnable = random()%2;

    // 2. génération aléatoire du nb de sticks
    nb_stick = (random()%MAX_NB_DIRECTION)+1;

    // 3. infos de debug
    if(DEBUG) printf("+ création d'une brick aléatoire\n");

    // 4. création du tableau de sticks
    stick = create_stick_table(nb_stick);
    for(i=0; i<nb_stick; i++)
    {
        // 4.1 génération de la direction (on vérifie qu'elle n'a pas déjà été prise)
        do { temp_direction = random()%MAX_NB_DIRECTION; } while(is_in_int_table(taken_value, MAX_NB_DIRECTION, temp_direction));

        // 4.2 on update les infos du stick
        set_stick_informations(random()%MAX_NB_COLOR, temp_direction, &(stick[i]));

        // 4.3 on rajoute la nouvelle direction dans la liste des valeurs interdites
        taken_value[i] = stick[i].direction;
    }


    return create_brick (turnable, stick, nb_stick);
}

/* fonction de suppression d'une brick */
void delete_brick (t_brick* brick)
{
    // 0. suppression des sticks
    free(brick->stick);

    // 1. suppression de la brick
    free(brick);

    // 2. print de debug
    if(DEBUG) printf("- suppression d'une brick\n");
}

/* fonction de copie d'une brick */
t_brick* copy_brick (t_brick* brick)
{
    if(DEBUG) printf("<- copie d'une brick\n");
    return create_brick(brick->turnable, copy_stick_table(brick->stick, brick->nb_stick), brick->nb_stick);
}

/* fonction de comparaison de 2 brick */
gboolean are_same_brick (t_brick* brick1, t_brick* brick2)
{
    if(DEBUG) printf("> comparaison de 2 bricks\n");
    if((brick1 == brick2) || (brick1->nb_stick == brick2->nb_stick && brick1->turnable == brick2->turnable && are_same_stick_table(brick1->stick, brick1->nb_stick, brick2->stick, brick2->nb_stick))) return TRUE;
    return FALSE;
}

/* fonction pour checker si 2 bricks sont superposables  */
gboolean are_superposable_bricks (t_brick* brick1, t_brick* brick2)
{
    // 0. déclaration des variables
    int i = 0;
    int j = 0;

    // 1. print de debug
    if(DEBUG) printf("> test si 2 bricks sont superposables\n");

    // 2. si jamais il y a supersposition forcée, on return FAUX directement
    if(brick1->nb_stick + brick2->nb_stick > MAX_NB_DIRECTION) return FALSE;

    // 3. sinon on regarde au cas par cas si il y a superposition ou non
    for(i=0; i<brick1->nb_stick; i++)
        for(j=0; j<brick2->nb_stick; j++)
            if(brick1->stick[i].direction == brick2->stick[j].direction) return FALSE;

    // 4. si il n'y a eu aucune superposition, les bricks sont superposables
    return TRUE;
}

/* fonction pour checker si 1 brick est superposable */
gboolean is_turnable_brick (t_brick* brick)
{
    if(DEBUG) printf("> test de supersposition de 2 bricks\n");
    if(brick->turnable == 1) return TRUE;
    else return FALSE;
}

/* fonction pour fusionner 2 bricks si elles sont superposables */
int fusion_bricks (t_brick* brick1, t_brick* brick2, t_brick** destination)
{
    if(are_superposable_bricks(brick1, brick2))
    {
        if(DEBUG) printf("-> fusion de 2 bricks\n");
        *destination = create_brick(brick1->turnable, fusion_sticks_table(brick1->stick, brick1->nb_stick, brick2->stick, brick2->nb_stick), brick1->nb_stick + brick2->nb_stick);
        return 1;
    }
    else return 0;
}

/* fonction de rotation d'une brick */
int turn_brick(t_brick* brick)
{
    // 0. déclaration des variables
    int i = 0;

    // 1. on ne tourne les bricks que si elles sont tournables
    if(is_turnable_brick(brick))
    {
        // 2. print de debug
        if(DEBUG) printf("= rotation d'une brick");

        // 3. rotation de la brick
        for(i=0; i<brick->nb_stick; i++) brick->stick[i].direction = (brick->stick[i].direction + 1)%MAX_NB_DIRECTION;
        return 1;
    }
    else return 0;
}

