#include "game.h"

void display_game (GtkWidget *wid, GtkWidget *win)
{
    // 0. déclarion des variables
    GtkWidget *dialog = NULL;

    // 1. création de la boite de dilogue
    dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "lancement du jeu ! \\o/");
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}
