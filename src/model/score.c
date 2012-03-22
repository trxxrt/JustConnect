#include "score.h"

t_best_score* load_best_scores()
{
    char* filename = "res/highscore.txt";
    FILE* file_high_score = NULL;
    t_best_score* best_score = NULL;
    int i = 0;
    char temp;

    while(best_score == NULL) best_score = (t_best_score*)malloc(sizeof(t_best_score));
    best_score->scores = NULL;
    best_score->nb = 0;

    file_high_score=fopen(filename,"r+");

    if(file_high_score!=NULL)
    {
        temp = fgetc(file_high_score); // On initialise caractereActuel

        // Boucle de lecture des caractères un à un
        while (temp != EOF) // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
        {
            if(temp=='\n') best_score->nb++; // On affiche le caractère stocké dans caractereActuel
            temp = fgetc(file_high_score); // On lit le caractère suivant
        }

        rewind(file_high_score); //retour au début

        while(best_score->scores == NULL) best_score->scores = (t_best_score_item*)malloc(sizeof(t_best_score_item)*best_score->nb);

        for(i=0; i<best_score->nb; i++)
            temp = fscanf(file_high_score, "%s %d",  best_score->scores[i].pseudo, &best_score->scores[i].score); // on stocke les highscores dans un tableau de structure

        if(DEBUG) printf("Ouverture du fichier %s : %d meilleurs scores trouvés !\n", filename, best_score->nb);

        fclose(file_high_score);
    }
    else if(DEBUG) printf("Erreur d'ouverture du fichier %s\n", filename);

    return best_score;

}

void save_best_scores(t_best_score* list)
{
	char* filename = "res/highscore.txt";
    FILE* file_high_score = NULL;
    int i = 0;

    file_high_score=fopen(filename,"w+");
    if(file_high_score!=NULL)
    {
        if(DEBUG) printf("sauvegarde des %d meilleurs scores\n", list->nb);
        for(i=0; i< list->nb ; i++)
            fprintf(file_high_score,"%s %d\n", list->scores[i].pseudo, list->scores[i].score);

    fclose(file_high_score);
    }
    else if(DEBUG) printf("echec de l'ouverture du fichier de sauvegarde\n");
}

gboolean is_a_best_score(t_best_score* list, int score)
{
    if(score>list->scores[list->nb-1].score) return TRUE;
    else return FALSE;
}

t_best_score* insert_in_best_score(t_best_score* list, int score, char* pseudo)
{
    int i=0, j=0;
    t_best_score* pt = (t_best_score*)malloc(sizeof(t_best_score));
    pt->nb = list->nb;
    pt->scores = NULL;
    while(pt->scores == NULL) pt->scores = (t_best_score_item*)malloc(sizeof(t_best_score_item)*pt->nb);

    if(is_a_best_score(list, score))
    {
        for(i=0; i<list->nb && score<list->scores[i].score; i++)
        {
            strcpy(pt->scores[i].pseudo,list->scores[i].pseudo);
            pt->scores[i].label = list->scores[i].label;
            pt->scores[i].score = list->scores[i].score;
        }

        j = i;
        strcpy(pt->scores[j].pseudo, pseudo);
        pt->scores[j].label = list->scores[j].label;
        pt->scores[j].score = score;
        if(DEBUG) printf("insertion du meilleur score %d de %s au rang %d\n", score, pseudo, j+1);

        for(i=j+1; i<list->nb; i++)
        {
            strcpy(pt->scores[i].pseudo, list->scores[i-1].pseudo);
            pt->scores[i].label = list->scores[i].label;
            pt->scores[i].score = list->scores[i-1].score;
        }
        return pt;
    }
    if(DEBUG) printf("le score %d de %s ne fait pas parti des meilleurs scores (< %d)\n", score, pseudo, list->scores[list->nb-1].score);
    return list;
}

