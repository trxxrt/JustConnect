#include "rules.h"

void display_rules(GtkWidget* win)
{
    // 0. déclaration des variables locales
    GtkWidget* window = NULL;
    GtkWidget* global_vbox = NULL;
    GtkWidget* vbox = NULL;
    GtkWidget* frame = NULL;
    GtkWidget* label = NULL;

    // 1. printf de debug
    if(DEBUG) printf("affichage des règles du jeu\n");

    // 2. création de la fenetre
    window = gtk_dialog_new();

        // 1.2 paramétrage de la boite de dialogue
    gtk_container_set_border_width (GTK_CONTAINER (window), 8);
    gtk_window_set_title(GTK_WINDOW(window), "Nouvelle partie");
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);

    frame = gtk_frame_new(" Règles du jeu ");
    gtk_container_set_border_width(GTK_CONTAINER(frame), 10);

    vbox = gtk_vbox_new(TRUE, 5);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);

    global_vbox = gtk_vbox_new(FALSE, 15);
    gtk_container_add (GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(window))), global_vbox);

    gtk_box_pack_start (GTK_BOX(global_vbox), frame, FALSE, FALSE, 0);
    gtk_dialog_add_button(GTK_DIALOG(window), GTK_STOCK_CLOSE, 1);

    gtk_container_add (GTK_CONTAINER(frame), vbox);

    label = gtk_label_new("« Just Connect » est un jeu de réfléxion codé en GTK+ et cairo placé sous licence GNU GPL.");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 2);
    label = gtk_label_new("Le but du jeu est de fermer des chemins d'une même couleur :\n  - Pour que le chemin soit validé, toutes les pièces le constituant doivent être connectées\n  - plus un chemin est long, plus il rapporte de points.");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 2);
    label = gtk_label_new("Si la brique proposée dans la pioche est tournable, un symbole l'indique.\nIl suffit alors au joueur de cliquer sur la brique pour la tourner de 90° dans le sens de l'aiguille d'une montre.");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 2);
    label = gtk_label_new("Le joueur peut fusionner la brique de la pioche avec une brique du plateau en cliquant sur la brique du plateau,\nsous la condition que les deux briques devant être fusionnées n'aient aucun segment en commun.");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 2);
    label = gtk_label_new("En mode \"facile\" ou \"intermédiaire\", le jeu est fini quand le joueur ne peut plus placer de brique sur la grille.\nEn mode \"difficile\", le joueur peut continuer à fusionner des briques,\njusqu'à l'impossibilité de fusionner une brique sur le plateau.");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 2);

    g_signal_connect_swapped (window, "response", G_CALLBACK (gtk_widget_destroy), window);

    gtk_widget_show_all(window);

}
