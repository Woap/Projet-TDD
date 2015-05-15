#include <stdio.h>
#include <stdlib.h>
#include "../../include/1.0/jeu.h"
#include "curses.h"


int main()
{
    grille s;
    joueur j;
    init_joueur(&j);
    int gwin =0;
    int resultat=0;;


    lecture_grille(&s,&j);
    initscr();
    affiche_grille(&s,&j);

    while(j.vie >0 && resultat==0)
    {
        resultat=deplacer_joueur(&s,&j,gwin);
        affiche_grille(&s,&j);
    }
    endwin();

    free_grille(&s);

    return 0;

}

