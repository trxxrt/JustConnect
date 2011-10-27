#ifndef SHARED_COLOR_H
#define SHARED_COLOR_H

// 0. définition de constantes
#define MAX_NB_COLOR 5 // nombre maximum de couleurs

// 0.1 paramétrage des couleurs IHM
#define RED create_color(255, 0, 0)
#define GREEN create_color(0, 255, 0)
#define BLUE create_color(0, 0, 255)
#define YELLOW create_color(255, 255, 0)
#define WHITE create_color(255, 255, 255)
//#define ORANGE create_color(255, 165, 0)
#define PINK create_color(255, 0, 255)
//#define GREY create_color(131, 131, 131)
//#define BROWN create_color(139, 69, 19)
#define BLACK create_color(255, 255, 255)
//#define PURPLE create_color(132, 112, 255)

typedef struct my_color
{
    int r;
    int g;
    int b;
}t_color;

// 1. déclaration des fonctions
t_color* create_color(int r, int g, int b);
t_color* create_color_from_id(int id);
gboolean is_same_color(t_color* color1, t_color* color2);
t_color* copy_color(t_color* color);
void delete_color(t_color* color);

#endif
