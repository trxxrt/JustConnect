#include "game.h"

void display_game (t_game_board* game)
{
// 0. déclarion des variables
GtkWidget* winGame = NULL;
GtkWidget* table = NULL;
GtkWidget* table2 = NULL;
GtkWidget* hbox = NULL;
GtkWidget* vbox = NULL;
GtkWidget* frame_best_score = NULL;
GtkWidget* frame_last_score = NULL;
GtkWidget* frame_score = NULL;
GtkWidget* frame_next_brick = NULL;
GtkWidget* frame_remaining_brick = NULL;
int i = 0;
int j = 0;

// 1.initialisation des variables.
winGame = gtk_window_new (GTK_WINDOW_TOPLEVEL);
table = gtk_table_new(game->nb_brick_x, game->nb_brick_y,TRUE);
table2 = gtk_table_new (21, 21, TRUE);
vbox = gtk_vbox_new (FALSE, 0);
frame_best_score = gtk_frame_new(" MEILLEUR SCORE ");
frame_last_score = gtk_frame_new(" DERNIER SCORE ");
frame_score = gtk_frame_new(" SCORE ACTUEL ");
frame_next_brick = gtk_frame_new(" PROCHAINE PIECE ");
frame_remaining_brick = gtk_frame_new(" PIECES RESTANTES ");
hbox = gtk_hbox_new (FALSE, 0);
game->best_score.label = gtk_label_new("0");
game->last_score.label = gtk_label_new("0");
game->score.label = gtk_label_new("0");
game->remaining_bricks.label = gtk_label_new("80");

//position des frames dans le tableau de gauche
gtk_table_attach_defaults(GTK_TABLE(table2), frame_best_score, 1, 5, 1, 4);
gtk_table_attach_defaults(GTK_TABLE(table2), frame_last_score, 1, 5, 5, 8);
gtk_table_attach_defaults(GTK_TABLE(table2), frame_score, 1, 5, 9, 12);
gtk_table_attach_defaults(GTK_TABLE(table2), frame_remaining_brick, 1, 5, 13, 16);
gtk_table_attach_defaults(GTK_TABLE(table2), frame_next_brick, 1, 5, 17, 20);

// ajout de la prochaine pièce
game->next_brick->image = gtk_drawing_area_new();
gtk_widget_set_size_request(game->next_brick->image, 40, 40);
gtk_container_add (GTK_CONTAINER(frame_next_brick), game->next_brick->image);
gtk_widget_add_events(game->next_brick->image, GDK_BUTTON_PRESS_MASK);
g_signal_connect(game->next_brick->image, "button_press_event", G_CALLBACK(on_next_brick_click_event), game);
g_signal_connect(game->next_brick->image, "expose-event", G_CALLBACK(on_next_brick_expose_event), game->next_brick);

// ajout des scores
gtk_container_add (GTK_CONTAINER(frame_best_score), game->best_score.label);
gtk_container_add (GTK_CONTAINER(frame_last_score), game->last_score.label);
gtk_container_add (GTK_CONTAINER(frame_score), game->score.label);
gtk_container_add (GTK_CONTAINER(frame_remaining_brick), game->remaining_bricks.label);

//position du label dans les frames
gtk_frame_set_label_align(GTK_FRAME(frame_best_score), 0.5, 0.5);
gtk_frame_set_label_align(GTK_FRAME(frame_last_score), 0.5, 0.5);
gtk_frame_set_label_align(GTK_FRAME(frame_score), 0.5, 0.5);
gtk_frame_set_label_align(GTK_FRAME(frame_next_brick), 0.5, 0.5);

// 2.Creation du tableau de boutons
for(i = 0; i<game->nb_brick_x; i++)
    for(j = 0; j<game->nb_brick_y; j++)
    {
        game->brick[i][j]->image = gtk_drawing_area_new();
        gtk_widget_set_size_request(game->brick[i][j]->image, 40, 40);
        gtk_widget_add_events(game->brick[i][j]->image, GDK_BUTTON_PRESS_MASK);
        g_signal_connect(game->brick[i][j]->image, "button_press_event", G_CALLBACK(on_brick_click_event), game);
        g_signal_connect(game->brick[i][j]->image, "expose-event", G_CALLBACK(on_brick_table_expose_event), game);
        gtk_table_attach_defaults(GTK_TABLE(table), game->brick[i][j]->image, i,i+1,j,j+1);
    }

gtk_table_set_row_spacings(GTK_TABLE(table), 0);
gtk_table_set_col_spacings(GTK_TABLE(table), 0);

gtk_table_attach_defaults(GTK_TABLE(table2), table, 7, 19, 1, 20);
gtk_box_pack_end (GTK_BOX(hbox), table2, TRUE, TRUE, 0);
gtk_container_add (GTK_CONTAINER(winGame), hbox);
gtk_widget_show_all (winGame);

}


/* fonction d'affichage d'une brick */
gboolean on_brick_table_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt)
{
    // 0. création des variables temporaires
    cairo_t *cr;
    int i = 0, j = 0, x = 0, y = 0;
    t_game_board* game = (t_game_board*)pt;

    // 1. on détermine la brick impliquée par le click
    for(i=0; i<game->nb_brick_x; i++)
        for(j=0; j<game->nb_brick_y; j++)
            if(game->brick[i][j]->image == widget) { x = i; y = j; }

    // 2. création de la surface cairo
    cr = gdk_cairo_create (widget->window);

    // 3. tracé de la brique
    draw_cairo_surface_from_brick(cr, game->brick[x][y], (int)game->brick[x][y]->image->allocation.width, (int)game->brick[x][y]->image->allocation.height);

    // 4. destruction de la brique
    cairo_destroy(cr);

    return FALSE;
}

/* fonction d'affichage de la prochaine brick */
gboolean on_next_brick_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt)
{
    // 0. création des variables temporaires
    cairo_t *cr;
    t_brick* brick = (t_brick*)pt;

    // 1. création de la surface cairo
    cr = gdk_cairo_create (widget->window);

    // 2. tracé de la brique
    draw_cairo_surface_from_brick(cr, brick, brick->image->allocation.width, brick->image->allocation.height);

    // 3. suppression de la surface cairo
    cairo_destroy(cr);

    return FALSE;
}

void draw_cairo_surface_from_brick(cairo_t* cr, t_brick* brick, int width, int height)
{
    // 0. création variables temporaires
    int i = 0;
    int delta_x = 0, delta_y = 0;
    int directions[MAX_NB_DIRECTION];
    for(i=0; i<MAX_NB_DIRECTION; i++) directions[i] = 0;

    // 1. réinitialisation de la surface
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_rectangle(cr, 0, 0, (double)width, (double)height);
    cairo_fill(cr);

    // 1. réglage de lépaisseur du trait
    cairo_set_line_width(cr, 6);

    // 2. création de la figure à partir des informations des sticks
    for(i=0; i<brick->nb_stick; i++)
    {
        cairo_move_to (cr, width/2, height/2);
        delta_x = 0; delta_y = 0;
        cairo_set_source_rgb(cr, brick->stick[i].color->r, brick->stick[i].color->g, brick->stick[i].color->b);

        if(brick->stick[i].direction == TOP) delta_y = -height/2;
        if(brick->stick[i].direction == BOTTOM) delta_y = height/2;
        if(brick->stick[i].direction == RIGHT) delta_x = width/2;
        if(brick->stick[i].direction == LEFT) delta_x = -width/2;
        directions[brick->stick[i].direction] = 1;

        cairo_rel_line_to (cr, delta_x, delta_y);
        cairo_stroke (cr);
    }

    // 3. si la brique n'est pas vide, on fait la croix noire du milieu
    if(brick->type != EMPTY_BRICK)
    {
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_move_to (cr, width/2, height/2);
        if(directions[RIGHT]) cairo_rel_line_to (cr, width/5, 0);
        cairo_stroke (cr);
        cairo_move_to (cr, width/2, height/2);
        if(directions[LEFT]) cairo_rel_line_to (cr, -width/5, 0);
        cairo_stroke (cr);
        cairo_move_to (cr, width/2, height/2);
        if(directions[BOTTOM]) cairo_rel_line_to (cr, 0, height/5);
        cairo_stroke (cr);
        cairo_move_to (cr, width/2, height/2);
        if(directions[TOP]) cairo_rel_line_to (cr, 0, -height/5);
        cairo_stroke (cr);
    }

    // 4. le tour noir de la case
    cairo_set_line_width(cr, 1);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_move_to (cr, 0, 0);
    cairo_rel_line_to (cr, width, 0);
    cairo_rel_line_to (cr, 0, height);
    cairo_rel_line_to (cr, -width, 0);
    cairo_rel_line_to (cr, 0, -height);
    cairo_stroke (cr);

    if(brick->type == UNATTACHED_BRICK && brick->turnable)
    {
        cairo_set_line_width(cr, 2);
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_arc(cr, 10, 10, 8, 60.*(M_PI / 180.),  360.*(M_PI / 180.));
        cairo_stroke(cr);
        cairo_move_to (cr, 15, 10);
        cairo_rel_line_to (cr, 6, 0);
        cairo_rel_line_to (cr, -3, 4);
        cairo_rel_line_to (cr, -3, -4);
        cairo_fill (cr);
    }

    cairo_stroke_preserve(cr);
}
