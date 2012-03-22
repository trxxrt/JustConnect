#include "best_score.h"

void display_best_score(GtkWidget* win)
{
    // 0. déclarion des variables
    GtkWidget* window = NULL;
    GtkWidget* global_vbox = NULL;
    GtkWidget* vbox = NULL;
    GtkWidget* frame = NULL;
    GtkWidget* button = NULL;
    char* buffer;
    char temp[50], temp2[50];
    int i = 0;
    t_best_score* list = load_best_scores();
    for(i=0; i<list->nb; i++)
        printf("%d : %s\n", list->scores[i].score, list->scores[i].pseudo);

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
