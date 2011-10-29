#include "best_score.h"

void display_best_score(GtkWidget* win)
{
    // 0. déclarion des variables
    GtkWidget* window = NULL;
    GtkWidget* global_vbox = NULL;
    GtkWidget* vbox = NULL;
    GtkWidget* frame = NULL;
    GtkWidget* button = NULL;
    char* test = "prout";
    char* buffer;
    char temp[50], temp2[50];
    int i = 0;
    t_best_score* list = load_best_scores();
    for(i=0; i<list->nb; i++)
        printf("%d : %s\n", list->scores[i].score, list->scores[i].pseudo);

    list = insert_in_best_score(list, 21, test);

    save_best_scores(list);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Meilleurs scores");
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width (GTK_CONTAINER (window), 8);
    gtk_widget_realize (window);
    g_signal_connect (window, "destroy", GTK_SIGNAL_FUNC(gtk_widget_destroy), window);

    frame = gtk_frame_new(" Meilleurs scores ");
    gtk_container_set_border_width(GTK_CONTAINER(frame), 15);

    vbox = gtk_vbox_new(TRUE, 5);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 15);

    global_vbox = gtk_vbox_new(FALSE, 15);
    gtk_container_add (GTK_CONTAINER(window), global_vbox);

    gtk_box_pack_start (GTK_BOX(global_vbox), frame, TRUE, TRUE, 0);
    button = gtk_button_new_from_stock(GTK_STOCK_CLOSE);
    g_signal_connect(button, "clicked", GTK_SIGNAL_FUNC(gtk_widget_destroy_from_callback), window);
    gtk_box_pack_end (GTK_BOX(global_vbox), button, TRUE, FALSE, 0);

    gtk_container_add (GTK_CONTAINER(frame), vbox);

    for(i=0; i<list->nb; i++)
    {
        sprintf(temp, "%02d .  ", i+1);
        buffer = strcat(temp, list->scores[i].pseudo);
        buffer = strcat(buffer, " : ");
        sprintf(temp2, "%d", list->scores[i].score);
        buffer = strcat(buffer, temp2);
        list->scores[i].label = gtk_label_new(buffer);
        gtk_box_pack_start (GTK_BOX(vbox), list->scores[i].label, TRUE, TRUE, 2);
        gtk_misc_set_alignment(GTK_MISC(list->scores[i].label), 0, 0.5);
    }

    gtk_widget_show_all(window);
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
    FILE* file_high_score = NULL;
    int i = 0;

    file_high_score=fopen("highscore.txt","w+");
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
