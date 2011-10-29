#include "best_score.h"

void display_best_score(GtkWidget* win)
{
    // 0. déclarion des variables
    GtkWidget *dialog = NULL;
    int i = 0;
    t_best_score* score = load_best_scores();
    for(i=0; i<score->nb; i++)
        printf("%d : %s\n", score->scores[i].score, score->scores[i].pseudo);

    // 1. création de la boite de dilogue
    dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "lancement des meilleurs scores");
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}


t_best_score* load_best_scores()
{
    char* filename = "highscore.txt";
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
            fscanf(file_high_score, "%s %d",  best_score->scores[i].pseudo, &best_score->scores[i].score); // on stocke les highscores dans un tableau de structure

        if(DEBUG) printf("Ouverture du fichier %s : %d meilleurs scores trouvés !\n", filename, best_score->nb);

        fclose(file_high_score);
    }
    else if(DEBUG) printf("Erreur d'ouverture du fichier %s\n", filename);

    return best_score;

}

void save_best_scores(t_best_score* list)
{

}

gboolean is_a_best_score(t_best_score* list, int score)
{
    if(score>list->scores[list->nb-1].score) return TRUE;
    else return FALSE;
}

void insert_in_best_score(t_best_score* list, int score, char* pseudo)
{
    int i =0;

    if(is_a_best_score(list, score))
    {

    }
}

/*

if(score>highscore[nb_high_score-1].score)
        {
            system("CLS");
            printf("Nouveau meilleur score !!!\n\n");
            printf("entrez votre nom (max 10 caracteres) :\t");
            tampon[0]='\0';
            do
            {
                scanf("%s", tampon);
            }while(tampon[0]=='\0');

            if(pseudo!=NULL) free(pseudo);

            if(strlen(tampon)<10)
            {
                pseudo=malloc(sizeof(char)*(strlen(tampon)+1));
                strcpy(pseudo, tampon);
            }
            else
            {
                pseudo=malloc(11*sizeof(char));
                for(i=0; i<10;i++)
                    pseudo[i]=tampon[i];
                pseudo[10]='\0';
            }









file_high_score=fopen("highscore.txt","r+");
if(file_high_score!=NULL)
{
    temp = fgetc(file_high_score); // On initialise caractereActuel
    nb_high_score=1;

    // Boucle de lecture des caractères un à un
    while (temp != EOF) // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
    {
        if(temp=='\n') nb_high_score++; // On affiche le caractère stocké dans caractereActuel
        temp = fgetc(file_high_score); // On lit le caractère suivant
    }

    rewind(file_high_score); //retour au début

    for(i=0; i<nb_high_score; i++)
        fscanf(file_high_score, "%s %d",  highscore[i].pseudo, &highscore[i].score); // on stocke les highscores dans un tableau de structure

    if(score>highscore[nb_high_score-1].score)
    {
        system("CLS");
        printf("Nouveau meilleur score !!!\n\n");
        printf("entrez votre nom (max 10 caracteres) :\t");
        tampon[0]='\0';
        do
        {
            scanf("%s", tampon);
        }while(tampon[0]=='\0');

        if(pseudo!=NULL) free(pseudo);

        if(strlen(tampon)<10)
        {
            pseudo=malloc(sizeof(char)*(strlen(tampon)+1));
            strcpy(pseudo, tampon);
        }
        else
        {
            pseudo=malloc(11*sizeof(char));
            for(i=0; i<10;i++)
                pseudo[i]=tampon[i];
            pseudo[10]='\0';
        }

        fclose(file_high_score);


        z=0; // booléen : si vaut 1, c'est que le score du joueur a deja été enregistré...
        file_high_score=fopen("highscore.txt","w+");
        if(file_high_score!=NULL)
        {
            for(i=0; i<nb_high_score; i++)
            {
                if(score>highscore[i].score && z==0)
                {
                    printf("superieur au score : %d\n\n",i+1); //useless
                    rewind(file_high_score); //on se repalce au début
                    j=0;
                    while(j<i)
                    {
                        fprintf(file_high_score,"%s %d\n",highscore[j].pseudo, highscore[j].score); //on lis, jusqu'a etre au bon endroit
                        j++;
                    }
                    fprintf(file_high_score,"%s %d", pseudo, score); //on inscrit les info du joueur

                    for(j=i;j<=nb_high_score;j++) //on complete le reste du fichier avec les info restantes.
                    {
                        fprintf(file_high_score,"\n%s %d",highscore[j].pseudo, highscore[j].score);
                    }
                    z++;
                }
            }
        fclose(file_high_score);
        }
*/
