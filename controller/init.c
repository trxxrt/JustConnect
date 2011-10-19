#include "init.h"

void global_init(int argc, char *argv[])
{
    // 0. intialisation du temps
    srandom(time(0));

    // 1. initialisation de gtk
    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
    gtk_init (&argc, &argv);
    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);
}
