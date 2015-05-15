#include <stdio.h>
#include <SDL/SDL.h>
#include "SDL_image.h"
#include <SDL/SDL_ttf.h>
#include <time.h>
#include <stdlib.h>

#include "../include/jeu.h"
#define VIE_MAX 3



void init_joueur( joueur *p)
{
    p->att=1;
    p->def=1;
    p->vie=VIE_MAX;
}

void init_mob( mob *m)
{
    m->att=1;
    m->vie=1;
}

void init_mobv2( mob *m)
{
    m->att=1;
    m->vie=2;
}




void pause( SDL_Surface *screen, joueur *j)
{
    int pause = 1;
    SDL_Event event;

    while (pause)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            pause = 0;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_p:
                pause = 0;
                break;
            default:
                break;
            }
            break;


        }
    }
}

int combat(joueur *j)
{
    mob m;
    init_mob(&m);

    while ( m.vie > 0)
    {

        if ( j->def > 0)
        {
            j->def -= m.att;
        }
        else
        {
            j->vie -= m.att;
        }


        m.vie -= j->att;

    }

    if ( m.vie <= 0)
        return 0; // Victoire
    else
        return 1; // Defaite

}

int combat2(joueur *j,mob *nb)
{


    while ( nb->vie > 0)
    {

        if ( j->def > 0)
        {
            j->def -= nb->att;
        }
        else
        {
            j->vie -= nb->att;
        }


        nb->vie -= j->att;

    }

    if ( j->vie > 0)
        return 0; // Victoire
    else
        return 1; // Defaite

}


int rand_a_b(int a, int b)
{
    return rand()%(b-a) +a;
}


