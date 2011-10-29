#include "about.h"

void display_about(GtkWidget *win)
{
    // 0. déclarion des variables
    GtkWidget *about = NULL;
    const gchar* names[3];
    names[0] = "Jean-Charles Leneveu";
    names[1] = "Mathieu delion";
    names[2] = "Arnaud Delafont";

    // 1. création de la boite de dilogue
    about = gtk_about_dialog_new();

    gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(about), "Just Connect");
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(about), "1.0.0");
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about), "Jeu de réfléxion codé en C à l'aide des librairies GTK+ et cairo.");
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(about), "Programme publié selon les termes de la Licence Publique Générale GNU");
    gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(about), "JustConnect v1.0.0\nCopyright (C) 2011 ((Jean-Charles Leneveu, Mathieu Delion, Arnaud Delafont))\n\nCe programme est libre, vous pouvez le redistribuer et/ou le modifier selon les termes de la Licence Publique Générale GNU\npubliée par la Free Software Foundation (version 2 ou bien toute autre version ultérieure choisie par vous).\n\nCe programme est distribué car potentiellement utile, mais SANS AUCUNE GARANTIE, ni explicite ni implicite,\ny compris les garanties de commercialisation ou d'adaptation dans un but spécifique.\nReportez-vous à la Licence Publique Générale GNU pour plus de détails.\n\nVous devez avoir reçu une copie de la Licence Publique Générale GNU en même temps que ce programme ;\nsi ce n'est pas le cas, écrivez à la Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, États-Unis.\n\nVous pouvez également écrire à leneveu@ece.fr, delion@ece.fr ou delafont@ece.fr pour plus de précision.");
    gtk_about_dialog_set_website (GTK_ABOUT_DIALOG(about), "https://github.com/trxxrt/JustConnect");
    gtk_about_dialog_set_authors (GTK_ABOUT_DIALOG(about), names);

    g_signal_connect_swapped (about, "response", G_CALLBACK (gtk_widget_destroy), about);

    gtk_widget_show_all(about);
}
