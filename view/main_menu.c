#include "main_menu.h"

void display_main_menu ()
{
    // 0. déclaration des variables
    GtkWidget *button = NULL;
    GtkWidget *image = NULL;
    GtkWidget *win = NULL;
    GtkWidget *vbox = NULL;

    // 2. création de la fenetre principale
    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (win), 8);
    gtk_window_set_title (GTK_WINDOW (win), "Just Connect");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_main_quit, NULL);

    // 3. création de la vbox
    vbox = gtk_vbox_new (FALSE, 6);
    gtk_container_add (GTK_CONTAINER (win), vbox);

    // 4. création de l'image du menu principale
    image = gtk_image_new_from_file("picture/menu.png");
    gtk_container_add (GTK_CONTAINER(vbox), image);

    // 4. création du bouton du lancement du jeu
    button = gtk_button_new_with_label("Lancer le jeu !");
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (game), (gpointer) win);
    gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

    // 5. création du bouton des options
    button = gtk_button_new_from_stock (GTK_STOCK_PREFERENCES);
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (options), (gpointer) win);
    gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

    // 6. création du bouton pour quitter
    button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
    g_signal_connect (button, "clicked", gtk_main_quit, NULL);
    gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

    // 7. lancement de la main-windows
    gtk_widget_show_all (win);
    gtk_main ();
}
