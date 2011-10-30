#include "game_over.h"

char* display_game_over (gpointer pt)
{
    // 0. déclaration des variables locales
    int i = 0;
    GtkWidget* dialog = NULL;
    GtkWidget* content_area = NULL;
    GtkWidget* label = NULL;
    GtkWidget* entry = NULL;
    GtkWidget* entry_buffer = NULL;
    char* buffer = (char*)malloc(15*sizeof(char));

    // 1. boite de dialogue de séléction du pseudo

        // 1.1 création de la boite
    dialog = gtk_dialog_new();

        // 1.2 paramétrage de la boite de dialogue
    gtk_container_set_border_width (GTK_CONTAINER (dialog), 8);
    gtk_window_set_title(GTK_WINDOW(dialog), "Fin de la partie");
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);

        // 1.3 ajout du label GUI
    content_area = gtk_dialog_get_content_area (GTK_DIALOG(dialog));
    gtk_box_set_spacing(GTK_BOX(content_area), 10);
    label = gtk_label_new("veuillez entrer votre pseudo");
    gtk_misc_set_alignment(GTK_MISC(label), 0, 0.5);
    gtk_box_pack_end (GTK_BOX(content_area), label, TRUE, TRUE, 0);

        // 1.4 ajout du gtkentry
    entry_buffer = gtk_entry_buffer_new("", 0);
    entry = gtk_entry_new_with_buffer(entry_buffer);
    gtk_entry_set_max_length(GTK_ENTRY(entry), 15);
    gtk_box_pack_end (GTK_BOX(content_area), entry, TRUE, TRUE, 0);
    strcpy(buffer, gtk_entry_get_text(GTK_ENTRY(entry)));

        // 1.5 ajout des boutons de choix
    gtk_dialog_add_button(GTK_DIALOG(dialog), GTK_STOCK_OK, 1);
    gtk_dialog_set_default_response(GTK_DIALOG(dialog), 1);

        // 1.6 activation du widget
    gtk_widget_show_all(dialog);
    gtk_dialog_run (GTK_DIALOG (dialog));

    // 2. recopie de la chaine de caractère
    strcpy(buffer, gtk_entry_get_text(GTK_ENTRY(entry)));
    if(DEBUG) printf("pseudo entré par le joueur : %s\n", buffer);

    // 3. destruction des widgets
    gtk_widget_destroy (dialog);

    // 4. on vérifie qu'il n'y a pas d'espace
    for(i=0; i<strlen(buffer); i++)
        if(buffer[i] == ' ') buffer[i] = '_';

    return buffer;
}
