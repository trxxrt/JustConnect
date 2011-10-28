#include "game.h"

void display_game (t_game_board* game)
{
// 0. déclarion des variables

    // 0.1 variables pour la fenêtre en elle-même
GtkWidget* winGame = NULL;
GtkWidget* right_table = NULL;
GtkWidget* left_table = NULL;
GtkWidget* hbox = NULL;
GtkWidget* vbox = NULL;
GtkWidget* frame_best_score = NULL;
GtkWidget* frame_last_score = NULL;
GtkWidget* frame_score = NULL;
GtkWidget* frame_next_brick = NULL;
GtkWidget* frame_remaining_brick = NULL;

    // 0.2 variables pour la toolbar du haut
GtkWidget* menu_bar = NULL;
GtkWidget* menu_file = NULL;
GtkWidget* new_game_item = NULL;
GtkWidget* option_item = NULL;
GtkWidget* quit_item = NULL;
GtkWidget* file_item = NULL;
GtkWidget* menu_help = NULL;
GtkWidget* rules_item = NULL;
GtkWidget* credit_item = NULL;
GtkWidget* help_item = NULL;

    // 0.3 variables temporaires de parcours de boucle
int i = 0;
int j = 0;

// 1.initialisation des variables.

    // 1.1 initialisation de la fenêtre
winGame = gtk_window_new (GTK_WINDOW_TOPLEVEL);
gtk_window_set_title (GTK_WINDOW (winGame), "Just Connect");
gtk_window_set_position (GTK_WINDOW (winGame), GTK_WIN_POS_CENTER);
gtk_widget_realize (winGame);
g_signal_connect (winGame, "destroy", gtk_main_quit, NULL);

    // 1.2 initialisation des tables
right_table = gtk_table_new(game->nb_brick_x, game->nb_brick_y,TRUE);
left_table = gtk_table_new (21, 21, TRUE);

    // 1.3 initialisation des box
vbox = gtk_vbox_new (FALSE, 0);
hbox = gtk_hbox_new (FALSE, 0);

    // 1.4 initialisation des frames
frame_best_score = gtk_frame_new(" MEILLEUR SCORE ");
frame_last_score = gtk_frame_new(" DERNIER SCORE ");
frame_score = gtk_frame_new(" SCORE ACTUEL ");
frame_next_brick = gtk_frame_new(" PROCHAINE PIECE ");
frame_remaining_brick = gtk_frame_new(" PIECES RESTANTES ");

    // 1.5 initialisation des labels
game->best_score.label = gtk_label_new("0");
game->last_score.label = gtk_label_new("0");
game->score.label = gtk_label_new("0");
game->remaining_bricks.label = gtk_label_new("80");

    // 1.6 initialisation du menu fichier.
menu_bar = gtk_menu_bar_new ();
menu_file = gtk_menu_new ();
menu_help = gtk_menu_new ();
new_game_item = gtk_menu_item_new_with_label ("Nouvelle Partie");
option_item = gtk_menu_item_new_with_label ("Option");
quit_item = gtk_menu_item_new_with_label ("Quitter");
rules_item = gtk_menu_item_new_with_label ("Règles du jeu");
credit_item = gtk_menu_item_new_with_label ("Crédits");
file_item = gtk_menu_item_new_with_label ("Fichier");
help_item = gtk_menu_item_new_with_label ("Aide");

// 2. paramétrage de la menu_bar

    // 2.1 on associe les items d'un menu au menu concerné
gtk_menu_append (GTK_MENU (menu_file), new_game_item);
gtk_menu_append (GTK_MENU (menu_file), option_item);
gtk_menu_append (GTK_MENU (menu_file), quit_item);
gtk_menu_append (GTK_MENU (menu_help), rules_item);
gtk_menu_append (GTK_MENU (menu_help), credit_item);
gtk_menu_bar_append (GTK_MENU_BAR (menu_bar), file_item);
gtk_menu_bar_append (GTK_MENU_BAR (menu_bar), help_item);

    // 2.2 on intègre la barre de menu à la vbox
gtk_box_pack_start (GTK_BOX(vbox), menu_bar, TRUE, TRUE, 0);

//on associe à la barre de menu principale ses items. (fichier, edit, help).
gtk_menu_item_set_submenu (GTK_MENU_ITEM (file_item), menu_file);///association de l'item fichier et du menu fichier.
gtk_menu_item_set_submenu (GTK_MENU_ITEM (help_item), menu_help);///association de l'item fichier et du menu fichier.

//liste des évenements

gtk_signal_connect_object (GTK_OBJECT (new_game_item), "activate", GTK_SIGNAL_FUNC (game), " ");
gtk_signal_connect_object (GTK_OBJECT (option_item), "activate", GTK_SIGNAL_FUNC (options), winGame);
gtk_signal_connect_object (GTK_OBJECT (quit_item), "activate", GTK_SIGNAL_FUNC (gtk_main_quit), " ");
//gtk_signal_connect_object (GTK_OBJECT (help_items), "activate", GTK_SIGNAL_FUNC (détruire), " "); -> pour help_item
//gtk_signal_connect_object (GTK_OBJECT (credit_items), "activate", GTK_SIGNAL_FUNC (détruire), " "); -> pour credit_item

//position des frames dans le tableau de gauche
gtk_table_attach_defaults(GTK_TABLE(left_table), frame_best_score, 1, 5, 1, 4);
gtk_table_attach_defaults(GTK_TABLE(left_table), frame_last_score, 1, 5, 5, 8);
gtk_table_attach_defaults(GTK_TABLE(left_table), frame_score, 1, 5, 9, 12);
gtk_table_attach_defaults(GTK_TABLE(left_table), frame_remaining_brick, 1, 5, 13, 16);
gtk_table_attach_defaults(GTK_TABLE(left_table), frame_next_brick, 1, 5, 17, 20);

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
        gtk_table_attach_defaults(GTK_TABLE(right_table), game->brick[i][j]->image, i,i+1,j,j+1);
    }

gtk_table_set_row_spacings(GTK_TABLE(right_table), 0);
gtk_table_set_col_spacings(GTK_TABLE(right_table), 0);

gtk_table_attach_defaults(GTK_TABLE(left_table), right_table, 7, 19, 1, 20);
gtk_box_pack_end (GTK_BOX(hbox), left_table, TRUE, TRUE, 0);
gtk_box_pack_end (GTK_BOX(vbox), hbox, TRUE, TRUE, 0);
gtk_container_add (GTK_CONTAINER(winGame), vbox);
gtk_widget_show_all (winGame);
gtk_main ();

}


/* fonction d'affichage d'une brick */
gboolean on_brick_table_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer pt)
{
    // 0. création des variables temporaires et initialisation
    cairo_t *cr;
    int color;
    int is_closed_path = 0;
    int i = 0, j = 0, x = 0, y = 0;
    t_game_board* game = (t_game_board*)pt;
    int** tab_test = (int**)malloc(game->nb_brick_x*sizeof(int*));
    for(i=0; i<game->nb_brick_x; i++) tab_test[i] = (int*)malloc(game->nb_brick_y*sizeof(int));
    for (i=0; i < game->nb_brick_x; i++)
        for (j=0; j < game->nb_brick_y; j++)
            tab_test[i][j] = 0;

    // 1. on détermine la brick impliquée par le click
    for(i=0; i<game->nb_brick_x; i++)
        for(j=0; j<game->nb_brick_y; j++)
            if(game->brick[i][j]->image == widget) { x = i; y = j; }

    // 2. controle de la fermeture de boucle pour l'interface si l'option est activé
    if(game->brick[x][y]->type != EMPTY_BRICK && game->gui_color_help == TRUE)
    {
        is_closed_path = detect_looped_brick (TRUE, tab_test, game, x, y, 0);
        if(is_closed_path) color = GREEN_BACKGROUND;
        else color = RED_BACKGROUND;

        if(is_closed_path)
        {
            for(i=0; i<game->nb_brick_x; i++)
            {
                for(j=0; j<game->nb_brick_y; j++)
                {
                    cr = gdk_cairo_create(game->brick[i][j]->image->window);
                    if(tab_test[i][j]) draw_cairo_surface_from_brick(cr, game->brick[i][j], (int)game->brick[i][j]->image->allocation.width, (int)game->brick[i][j]->image->allocation.height, color);
                    cairo_destroy(cr);
                }
            }
            return FALSE;
        }
    }
    else color = WHITE_BACKGROUND;

    // 3. tracé de la brique
    cr = gdk_cairo_create (widget->window);
    draw_cairo_surface_from_brick(cr, game->brick[x][y], (int)game->brick[x][y]->image->allocation.width, (int)game->brick[x][y]->image->allocation.height, color);
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
    draw_cairo_surface_from_brick(cr, brick, brick->image->allocation.width, brick->image->allocation.height, 0);

    // 3. suppression de la surface cairo
    cairo_destroy(cr);

    return FALSE;
}

void draw_cairo_surface_from_brick(cairo_t* cr, t_brick* brick, int width, int height, int background_color)
{
    // 0. création variables temporaires
    int i = 0;
    int delta_x = 0, delta_y = 0;
    int directions[MAX_NB_DIRECTION];
    for(i=0; i<MAX_NB_DIRECTION; i++) directions[i] = 0;

    // 1. réinitialisation de la surface
    if(background_color == 1) cairo_set_source_rgb(cr, 50.0/255.0, 200.0/255.0, 50.0/255.0);
    else if(background_color == 2) cairo_set_source_rgb(cr, 205.0/255.0, 50.0/255.0, 50.0/255.0);
    else cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
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
