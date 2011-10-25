#include "game.h"

void display_game (t_game_board* game)
{
// 0. déclarion des variables
GtkWidget* winGame = NULL;
GtkWidget* table = NULL;
GtkWidget* table2 = NULL;
GtkWidget* hbox = NULL;
GtkWidget* vbox = NULL;
GtkWidget* frame1 = NULL;
GtkWidget* frame2 = NULL;
GtkWidget* frame3 = NULL;
GtkWidget* frame4 = NULL;
int i = 0;
int j = 0;

// 1.initialisation des variables.
winGame = gtk_window_new (GTK_WINDOW_TOPLEVEL);
table2 = gtk_table_new (21, 21, TRUE);
vbox = gtk_vbox_new (FALSE, 0);
frame1 = gtk_frame_new(" MEILLEUR SCORE ");
frame2 = gtk_frame_new(" DERNIER SCORE ");
frame3 = gtk_frame_new(" SCORE ACTUEL ");
frame4 = gtk_frame_new(" PROCHAINE PIECE ");
hbox = gtk_hbox_new (FALSE, 0);

//position des frames dans le tableau de gauche
gtk_table_attach_defaults(GTK_TABLE(table2), frame1, 1, 5, 1, 5);
gtk_table_attach_defaults(GTK_TABLE(table2), frame2, 1, 5, 6, 10);
gtk_table_attach_defaults(GTK_TABLE(table2), frame3, 1, 5, 11, 15);
gtk_table_attach_defaults(GTK_TABLE(table2), frame4, 1, 5, 16, 20);

//position du label dans les frames
gtk_frame_set_label_align(GTK_FRAME(frame1), 0.5, 0.5);
gtk_frame_set_label_align(GTK_FRAME(frame2), 0.5, 0.5);
gtk_frame_set_label_align(GTK_FRAME(frame3), 0.5, 0.5);
gtk_frame_set_label_align(GTK_FRAME(frame4), 0.5, 0.5);

// 2.Creation du tableau de boutons
table = gtk_table_new(10,10,TRUE);
for(i = 0; i<game->nb_brick_x; i++)
    for(j = 0; j<game->nb_brick_y; j++)
        gtk_table_attach_defaults(GTK_TABLE(table), game->brick[i][j]->button, i,i+1,j,j+1);

gtk_table_attach_defaults(GTK_TABLE(table2), table, 7, 19, 1, 20);
gtk_box_pack_end (GTK_BOX(hbox), table2, TRUE, TRUE, 0);
gtk_container_add (GTK_CONTAINER(winGame), hbox);
gtk_widget_show_all (winGame);

}
