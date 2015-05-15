#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "../include/jeu.h"
#include "../include/fonction_jeu.h"
#include "../include/fonction_grille.h"
#include "../include/SDL_image.h"



int main(int argc, char *argv[])
{

    grille s;
    joueur j;
    mob un;
    mob deux;
    init_joueur(&j);
    init_mobv2(&un);
    init_mobv2(&deux);
    lecture_grille(&s,&j,&un,&deux);

    while ( jeu(&j,&s, &un,&deux) ==1)
    {
        switch (jeu(&j,&s,&un,&deux))
        {
        case 0:
            break;
        case 1:
            init_joueur(&j);
            init_mobv2(&un);
            init_mobv2(&deux);
            lecture_grille(&s,&j,&un,&deux);
            jeu(&j,&s,&un,&deux);
            break;
        default:
            break;
        }
    }
    return 0;

}
