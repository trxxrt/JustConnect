#ifndef SHARED_COLOR_H
#define SHARED_COLOR_H

// 0. définition de constantes
#define MAX_NB_COLOR 9 // nombre maximum de couleurs

// 0.1 paramétrage des couleurs IHM
#define RED create_color(255.0/255.0, 0.0, 0.0)
#define GREEN create_color(0.0, 255.0/255.0, 0.0)
#define BLUE create_color(0.0, 0.0, 255.0/255.0)
#define YELLOW create_color(255.0/255.0, 255.0/255.0, 0.0)
#define WHITE create_color(255.0/255.0, 255.0/255.0, 255.0/255.0)
#define ORANGE create_color(255.0/255.0, 165.0/165.0, 0.0)
#define PINK create_color(255.0/255.0, 0.0, 255.0/255.0)
#define GREY create_color(131.0/255.0, 131.0/255.0, 131.0/255.0)
#define BROWN create_color(139.0/255.0, 69.0/255.0, 19.0/255.0)
#define BLACK create_color(255.0/255.0, 255.0/255.0, 255.0/255.0)
#define PURPLE create_color(132.0/255.0, 112.0/255.0, 255.0/255.0)

typedef struct my_color
{
    double r;
    double g;
    double b;
}t_color;

// 1. déclaration des fonctions
t_color* create_color(double r, double g, double b);
t_color* create_color_from_id(int id);
gboolean is_same_color(t_color* color1, t_color* color2);
t_color* copy_color(t_color* color);
void delete_color(t_color* color);

#endif
