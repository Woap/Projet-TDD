#include <stdio.h>
#include <stdlib.h>
#include "jeu.h"
#include "ncurses.h"


int main()
{
    grille s;
    joueur j;
    init_joueur(&j);
	
	
    lecture_grille(&s,&j); 
    initscr();
    affiche_grille(&s,&j); 

    while(1)
    {
        deplacer_joueur(&s,&j);
        affiche_grille(&s,&j);
    }
    endwin();
	
    free_grille(&s);
	
    return 0;

}

