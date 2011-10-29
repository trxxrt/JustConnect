#include "game_launcher.h"

void display_launcher_pop_up (gpointer pt)
{
    // 0. déclaration des variables locales
    t_game_board* game = (t_game_board*)pt;
    GtkWidget* dialog = NULL;
    GtkWidget* content_area = NULL;
    GtkWidget* misc = NULL;
    int rules = SOLO_GAME_EASY;
    int size_of_game = 10;

    // 1. première boite de dialogue de séléction de la difficulté

        // 1.1 création de la boite
    dialog = gtk_dialog_new();

        // 1.2 paramétrage de la boite de dialogue
    gtk_container_set_border_width (GTK_CONTAINER (dialog), 8);
    gtk_window_set_title(GTK_WINDOW(dialog), "Nouvelle partie");
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);

        // 1.3 ajout du misc GUI
    content_area = gtk_dialog_get_content_area (GTK_DIALOG(dialog));
    gtk_box_set_spacing(GTK_BOX(content_area), 10);
    misc = gtk_label_new("sélectionnez la difficulté");
    gtk_misc_set_alignment(GTK_MISC(misc), 0, 0.5);
    gtk_box_pack_end (GTK_BOX(content_area), misc, TRUE, TRUE, 0);

        // 1.4 ajout des boutons de choix
    gtk_dialog_add_button(GTK_DIALOG(dialog), "facile", SOLO_GAME_EASY);
    gtk_dialog_add_button(GTK_DIALOG(dialog), "intermédiaire", SOLO_GAME_MEDIUM);
    gtk_dialog_add_button(GTK_DIALOG(dialog), "difficile", SOLO_GAME_HARD);
    gtk_dialog_set_default_response(GTK_DIALOG(dialog), SOLO_GAME_EASY);

        // 1.5 activation du widget
    gtk_widget_show_all(dialog);
    rules = gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);

    // 2. seconde boite de dialogue (séléction de la taille)

        // 2.1 création de la boite
    dialog = gtk_dialog_new();

        // 2.2 paramétrage de la boite de dialogue
    gtk_container_set_border_width (GTK_CONTAINER (dialog), 8);
    gtk_window_set_title(GTK_WINDOW(dialog), "Nouvelle partie");
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);

        // 2.3 ajout du label GUI + le spinbutton de selection
    content_area = gtk_dialog_get_content_area (GTK_DIALOG(dialog));
    misc = gtk_label_new("sélectionnez la taille du plateau");
    gtk_misc_set_alignment(GTK_MISC(misc), 0, 0.5);
    gtk_box_pack_start (GTK_BOX(content_area), misc, TRUE, TRUE, 0);
    gtk_box_set_spacing(GTK_BOX(content_area), 10);
    misc = gtk_spin_button_new_with_range(5.0, 15.0, 1.0);
    gtk_box_pack_start (GTK_BOX(content_area), misc, TRUE, TRUE, 0);
    g_object_ref(misc);

        // 2.4 ajout du bouton de validation
    gtk_dialog_add_button(GTK_DIALOG(dialog), GTK_STOCK_OK, 1);
    gtk_dialog_set_default_response(GTK_DIALOG(dialog), 1);

        // 2.5 activation du widget
    gtk_widget_show_all(dialog);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);

    // 3. récupération des infos sur la taille du plateau et suppressions du misc plus nécessaire
    size_of_game = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(misc));
    g_object_unref(misc);

    // 4. lancement du nouveau jeu
    new_game(game, rules, size_of_game, size_of_game);
}
