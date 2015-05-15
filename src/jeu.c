#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "SDL_image.h"
#include <SDL/SDL_ttf.h>
#include <time.h>
#include "../include/jeu.h"
#include "../include/fonction_grille.h"
#include "../include/fonction_jeu.h"

#define SCREEN_WIDTH  480
#define SCREEN_HEIGHT 530
#define SPRITE_SIZE 32
#define STEP_SIZE 32

#define VIE_MAX 3



int jeu(joueur *j, grille *s,mob *un, mob *deux)
{
    /**
    * @brief Initialisation des variables SDL et chargements des images
    */
    SDL_Surface *screen,*sprite_left,*sprite_down,*sprite_up,*sprite_right, *backbg, *wall, *fire, *life, *texte,*tableau,*mob,*mob2,*mob3,*objectif,*epee,*bouclier,*potion;
    SDL_Rect rcSprite, rcGrass, rcWall, rcFire,rcLife,rcMob,rcObj,position,rcPotion,rcEpee,rcBouclier,rcMob2,rcMob3;
    SDL_Event event;
    Uint8 *keystate;
    int colorkey, gameover,move,val=-1,resultat,deadun=0,deadeux=0;

    TTF_Init();
    TTF_Font *police = NULL;
    TTF_Font *police2 = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("WOAPGAME", "WOAPGAME");
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_DOUBLEBUF);
    char vie[2];
    police = TTF_OpenFont("../src/pixel.TTF",30);
    police2 = TTF_OpenFont("../src/pixel.TTF",17);
    SDL_Color couleurBlanc = { 245,245,245 };


    tableau = IMG_Load("../src/img/tableau.bmp");
    sprite_right= IMG_Load("../src/img/link_right.bmp");
    sprite_left= IMG_Load("../src/img/link_left.bmp");
    sprite_up= IMG_Load("../src/img/link_up.bmp");
    sprite_down= IMG_Load("../src/img/link_down.bmp");
    backbg=IMG_Load("../src/img/background.bmp");
    wall= IMG_Load("../src/img/wall.bmp");
    fire= IMG_Load("../src/img/fire.bmp");
    life= IMG_Load("../src/img/life.bmp");
    mob= IMG_Load("../src/img/mob.bmp");
    objectif= IMG_Load("../src/img/objectif.bmp");
    potion= IMG_Load("../src/img/potion.bmp");
    bouclier= IMG_Load("../src/img/bouclier.bmp");
    epee= IMG_Load("../src/img/epee.bmp");
    mob2= IMG_Load("../src/img/mob2.bmp");
    mob3= IMG_Load("../src/img/mob2.bmp");

    colorkey= SDL_MapRGB(screen->format, 0, 0, 0);
    SDL_SetColorKey(sprite_left, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(sprite_down, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(sprite_up, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(sprite_right, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(fire, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(life, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(mob, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(mob2, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(mob3, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(objectif, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(epee, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(bouclier, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(potion, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);



    rcSprite.x = j->posx * SPRITE_SIZE ;
    rcSprite.y = j->posy * SPRITE_SIZE ;
    rcMob2.x = un->posx * SPRITE_SIZE ;
    rcMob2.y = un->posy * SPRITE_SIZE ;
    rcMob3.x = deux->posx * SPRITE_SIZE ;
    rcMob3.y = deux->posy * SPRITE_SIZE ;

    position.x = 0;
    position.y = 480;
    SDL_BlitSurface(tableau, NULL, screen, &position);

    gameover = 0;
    move = 0;


    /**
    * boucle princpale du jeu permettant le fonctionnement du jeu
    */
    while (gameover == 0 )
    {
        resultat = -1;
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                gameover = 1;
                val=0;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                case SDLK_a:
                    gameover =1;
                    val=0;
                    break;
                case SDLK_r:
                    return 1;
                    break;
                case SDLK_p:
                    pause();
                    break;
                case SDLK_c:
                    if ( j->tab[2]=='P')
                    {
                        j->tab[2]='M';
                        j->vie=VIE_MAX;
                        position.x = 72;
                        position.y = 496;
                        position.w = 29;
                        position.h = 25;
                        SDL_FillRect(screen, &position, 0);
                    }
                    break;
                default:
                    break;
                }
            case SDL_MOUSEBUTTONDOWN:
                if ( (((event.motion.x / SPRITE_SIZE * SPRITE_SIZE == rcSprite.x +SPRITE_SIZE) || (event.motion.x / SPRITE_SIZE * SPRITE_SIZE == rcSprite.x -SPRITE_SIZE)) && (event.motion.y / SPRITE_SIZE * SPRITE_SIZE == rcSprite.y) ) ||
                        (((event.motion.y / SPRITE_SIZE * SPRITE_SIZE == rcSprite.y +SPRITE_SIZE) || (event.motion.y / SPRITE_SIZE * SPRITE_SIZE == rcSprite.y -SPRITE_SIZE)) && (event.motion.x / SPRITE_SIZE * SPRITE_SIZE == rcSprite.x) ) )
                {
                    rcSprite.x= event.motion.x / SPRITE_SIZE * SPRITE_SIZE;
                    rcSprite.y= event.motion.y / SPRITE_SIZE * SPRITE_SIZE;
                    if ( s->grille[(rcSprite.x/32)][rcSprite.y/32] == 2 )
                    {
                        s->grille[(rcSprite.x/32)][rcSprite.y/32] = 0;

                        j->vie--;
                    }
                    if ( s->grille[(rcSprite.x/32)][rcSprite.y/32] == 3 )
                    {
                        s->grille[(rcSprite.x/32)][rcSprite.y/32] =0;

                        if ( j->vie >= VIE_MAX)
                            j->vie =VIE_MAX;
                        else
                            j->vie++;
                    }
                    if ( s->grille[(rcSprite.x/32)][rcSprite.y/32] == 4 )
                    {
                        resultat=combat(j);
                        if ( resultat == 0)
                        {
                            s->grille[(rcSprite.x/32)][rcSprite.y/32] = 0;
                        }
                        else
                        {
                            val = 2;
                            gameover=1;
                        }
                    }
                    if ( s->grille[(rcSprite.x/32)][rcSprite.y/32] == 5 )
                    {
                        return 3;
                    }
                    if ( s->grille[rcSprite.x/32][rcSprite.y/32] == 6 )
                    {
                        s->grille[rcSprite.x/32][(rcSprite.y/32)] = 0;
                        j->tab[0]='E';

                        j->att++;
                    }
                    if ( s->grille[rcSprite.x/32][rcSprite.y/32] == 7 )
                    {
                        s->grille[rcSprite.x/32][(rcSprite.y/32)] = 0;
                        j->tab[2]='P';

                    }
                    if ( s->grille[rcSprite.x/32][rcSprite.y/32] == 8 )
                    {
                        s->grille[rcSprite.x/32][(rcSprite.y/32)] = 0;
                        j->tab[1]='B';

                        j->def++;
                    }

                }
                break;
            }

            if ( j->vie <= 0 )
            {
                return 1;
            }

            /**< Déplacement du joueur et gestion des collisions */
            keystate = SDL_GetKeyState(NULL);

            if (keystate[SDLK_LEFT] )
            {
                move=1;

                if ( (rcSprite.x)-32 >= 0 && s->grille[(rcSprite.x/32)-1][rcSprite.y/32] != 1  )
                {
                    rcSprite.x -= STEP_SIZE;
                    if ( s->grille[(rcSprite.x/32)][rcSprite.y/32] == 2 )
                    {
                        s->grille[(rcSprite.x/32)][rcSprite.y/32] = 0;

                        j->vie--;
                    }
                    if ( s->grille[(rcSprite.x/32)][rcSprite.y/32] == 3 )
                    {
                        s->grille[(rcSprite.x/32)][rcSprite.y/32] =0;

                        if ( j->vie >= VIE_MAX)
                            j->vie =VIE_MAX;
                        else
                            j->vie++;
                    }
                    if ( s->grille[(rcSprite.x/32)][rcSprite.y/32] == 4 )
                    {
                        resultat=combat(j);
                        if ( resultat == 0)
                        {
                            s->grille[(rcSprite.x/32)][rcSprite.y/32] = 0;

                        }
                        else
                        {
                            val = 1;
                            gameover=1;
                        }
                    }
                    if ( s->grille[(rcSprite.x/32)][rcSprite.y/32] == 5 )
                    {
                        gameover=1;
                        val=0;
                    }
                    if ( s->grille[rcSprite.x/32][rcSprite.y/32] == 6 )
                    {
                        s->grille[rcSprite.x/32][(rcSprite.y/32)] = 0;
                        j->tab[0]='E';

                        j->att++;
                    }
                    if ( s->grille[rcSprite.x/32][rcSprite.y/32] == 7 )
                    {
                        s->grille[rcSprite.x/32][(rcSprite.y/32)] = 0;
                        j->tab[2]='P';

                    }
                    if ( s->grille[rcSprite.x/32][rcSprite.y/32] == 8 )
                    {
                        s->grille[rcSprite.x/32][(rcSprite.y/32)] = 0;
                        j->tab[1]='B';

                        j->def++;
                    }

                }
            }
            if (keystate[SDLK_RIGHT] )
            {
                move=2;

                if ( (rcSprite.x)+32 < SCREEN_WIDTH && s->grille[(rcSprite.x/32)+1][rcSprite.y/32] != 1  )
                {
                    rcSprite.x += STEP_SIZE;
                    if ( s->grille[(rcSprite.x/32)][rcSprite.y/32] == 2 )
                    {
                        s->grille[(rcSprite.x/32)][rcSprite.y/32] =0;
                        j->vie--;
                    }
                    if ( s->grille[(rcSprite.x/32)][rcSprite.y/32] == 3 )
                    {
                        s->grille[(rcSprite.x/32)][rcSprite.y/32] =0;
                        if ( j->vie >= VIE_MAX)
                            j->vie = VIE_MAX;
                        else
                            j->vie++;
                    }
                    if ( s->grille[(rcSprite.x/32)][rcSprite.y/32] == 4 )
                    {
                        resultat=combat(j);
                        if ( resultat == 0)
                        {
                            s->grille[(rcSprite.x/32)][rcSprite.y/32] =0;
                        }
                        else
                        {
                            val = 1;
                            gameover=1;
                        }
                    }
                    if ( s->grille[(rcSprite.x/32)][rcSprite.y/32] == 5 )
                    {
                        gameover=1;
                        val=0;
                    }
                    if ( s->grille[rcSprite.x/32][rcSprite.y/32] == 6 )
                    {
                        s->grille[rcSprite.x/32][(rcSprite.y/32)] = 0;
                        j->tab[0]='E';
                        j->att++;
                    }
                    if ( s->grille[rcSprite.x/32][rcSprite.y/32] == 7 )
                    {
                        s->grille[rcSprite.x/32][(rcSprite.y/32)] = 0;
                        j->tab[2]='P';
                    }
                    if ( s->grille[rcSprite.x/32][rcSprite.y/32] == 8 )
                    {
                        s->grille[rcSprite.x/32][(rcSprite.y/32)] = 0;
                        j->tab[1]='B';
                        j->def++;
                    }
                }

            }
            if (keystate[SDLK_UP] )
            {
                move=3;
                if ( (rcSprite.y)-32 >= 0 && s->grille[(rcSprite.x/32)][(rcSprite.y/32)-1] != 1  )
                {
                    rcSprite.y -= STEP_SIZE;

                    if ( s->grille[rcSprite.x/32][(rcSprite.y/32)] == 2 )
                    {
                        s->grille[rcSprite.x/32][(rcSprite.y/32)] =0;

                        j->vie--;
                    }
                    if ( s->grille[rcSprite.x/32][(rcSprite.y/32)] == 3 )
                    {
                        s->grille[rcSprite.x/32][(rcSprite.y/32)] =0;

                        if ( j->vie >= VIE_MAX)
                            j->vie = VIE_MAX;
                        else
                            j->vie++;
                    }
                    if ( s->grille[rcSprite.x/32][(rcSprite.y/32)] == 4 )
                    {
                        resultat=combat(j);
                        if ( resultat == 0)
                        {
                            s->grille[rcSprite.x/32][(rcSprite.y/32)] =0;
                        }
                        else
                        {
                            val = 1;
                            gameover=1;
                        }
                    }
                    if ( s->grille[(rcSprite.x/32)][(rcSprite.y/32)] == 5 )
                    {
                        gameover=1;
                        val=0;
                    }
                    if ( s->grille[rcSprite.x/32][rcSprite.y/32] == 6 )
                    {
                        s->grille[rcSprite.x/32][(rcSprite.y/32)] = 0;
                        j->tab[0]='E';

                        j->att++;
                    }
                    if ( s->grille[rcSprite.x/32][rcSprite.y/32] == 7 )
                    {
                        s->grille[rcSprite.x/32][(rcSprite.y/32)] = 0;
                        j->tab[2]='P';

                    }
                    if ( s->grille[rcSprite.x/32][rcSprite.y/32] == 8 )
                    {
                        s->grille[rcSprite.x/32][(rcSprite.y/32)] = 0;
                        j->tab[1]='B';

                        j->def++;
                    }

                }
            }
            if (keystate[SDLK_DOWN] )
            {
                move=4;
                if ((rcSprite.y)+32 < SCREEN_HEIGHT-50 && s->grille[(rcSprite.x/32)][(rcSprite.y/32)+1] != 1  )
                {
                    rcSprite.y += STEP_SIZE;

                    if ( s->grille[rcSprite.x/32][(rcSprite.y/32)] == 2 )
                    {
                        s->grille[rcSprite.x/32][(rcSprite.y/32)] = 0;

                        j->vie--;
                    }
                    if ( s->grille[rcSprite.x/32][(rcSprite.y/32)] == 3 )
                    {
                        s->grille[rcSprite.x/32][(rcSprite.y/32)] = 0;

                        if ( j->vie >= VIE_MAX)
                            j->vie = VIE_MAX;
                        else
                            j->vie++;
                    }
                    if ( s->grille[rcSprite.x/32][(rcSprite.y/32)] == 4 )
                    {
                        resultat=combat(j);
                        if ( resultat == 0)
                        {
                            s->grille[rcSprite.x/32][(rcSprite.y/32)] = 0;
                        }
                        else
                        {
                            val = 2;
                            gameover=1;
                        }
                    }
                    if ( s->grille[rcSprite.x/32][rcSprite.y/32] == 5 )
                    {
                        gameover=1;
                        val=3;
                    }
                    if ( s->grille[rcSprite.x/32][rcSprite.y/32] == 6 )
                    {
                        s->grille[rcSprite.x/32][(rcSprite.y/32)] = 0;
                        j->tab[0]='E';

                        j->att++;
                    }
                    if ( s->grille[rcSprite.x/32][rcSprite.y/32] == 7 )
                    {
                        s->grille[rcSprite.x/32][(rcSprite.y/32)] = 0;
                        j->tab[2]='P';

                    }
                    if ( s->grille[rcSprite.x/32][rcSprite.y/32] == 8 )
                    {
                        s->grille[rcSprite.x/32][(rcSprite.y/32)] = 0;
                        j->tab[1]='B';
                        j->def++;
                    }
                }

            }




            /**< Affichage des caractéristiques du joueur sur le tableau de score */
            sprintf(vie, "%d",j->vie);
            texte = TTF_RenderText_Solid(police, vie,couleurBlanc);
            position.x = 427;
            position.y = 497;
            position.w =50;
            position.h =50;
            SDL_FillRect(screen, &position, 0);
            SDL_BlitSurface(texte,NULL, screen, &position);
            SDL_FreeSurface(texte);

            position.x = 387;
            position.y = 504;
            sprintf(vie, "%d",j->def);
            texte = TTF_RenderText_Solid(police2, vie,couleurBlanc);
            SDL_FillRect(screen, &position, 0);
            SDL_BlitSurface(texte,NULL, screen, &position);
            SDL_FreeSurface(texte);

            position.x = 387;
            position.y = 488;
            sprintf(vie, "%d",j->att);
            texte = TTF_RenderText_Solid(police2, vie,couleurBlanc);
            SDL_FillRect(screen, &position, 0);
            SDL_BlitSurface(texte,NULL, screen, &position);
            SDL_FreeSurface(texte);

            if ( j->tab[0] =='E')
            {
                position.x = 7;
                position.y = 489;
                SDL_BlitSurface(epee,NULL, screen, &position);
            }
            if ( j->tab[1] =='B')
            {
                position.x = 38;
                position.y = 492;
                SDL_BlitSurface(bouclier,NULL, screen, &position);
            }
            if ( j->tab[2] =='P')
            {
                position.x = 72;
                position.y = 490;
                SDL_BlitSurface(potion,NULL, screen, &position);
            }



            /**< Affichage graphique des objets sur la grille */
            for (int x = 0; x < SCREEN_WIDTH/SPRITE_SIZE; x++)
            {
                for (int y = 0; y < (SCREEN_HEIGHT-50)/SPRITE_SIZE; y++)
                {
                    {
                        if ( s->grille[x][y] == 0 )
                        {
                            rcGrass.x = x * SPRITE_SIZE;
                            rcGrass.y = y * SPRITE_SIZE;
                            SDL_BlitSurface(backbg, NULL, screen, &rcGrass);
                        }
                        if ( s->grille[x][y] == 1 )
                        {
                            rcWall.x = x * SPRITE_SIZE;
                            rcWall.y = y * SPRITE_SIZE;
                            SDL_BlitSurface(wall, NULL, screen, &rcWall);
                        }
                        if ( s->grille[x][y] == 2 )
                        {
                            rcFire.x = x * SPRITE_SIZE;
                            rcFire.y = y * SPRITE_SIZE;
                            rcGrass.x = x * SPRITE_SIZE;
                            rcGrass.y = y * SPRITE_SIZE;
                            SDL_BlitSurface(backbg, NULL, screen, &rcGrass);
                            SDL_BlitSurface(fire, NULL, screen, &rcFire);
                        }
                        if ( s->grille[x][y] == 3 )
                        {
                            rcLife.x = x * SPRITE_SIZE;
                            rcLife.y = y * SPRITE_SIZE;
                            rcGrass.x = x * SPRITE_SIZE;
                            rcGrass.y = y * SPRITE_SIZE;
                            SDL_BlitSurface(backbg, NULL, screen, &rcGrass);
                            SDL_BlitSurface(life, NULL, screen, &rcLife);
                        }
                        if ( s->grille[x][y] == 4 )
                        {
                            rcMob.x = x * SPRITE_SIZE;
                            rcMob.y = y * SPRITE_SIZE;
                            rcGrass.x = x * SPRITE_SIZE;
                            rcGrass.y = y * SPRITE_SIZE;
                            SDL_BlitSurface(backbg, NULL, screen, &rcGrass);
                            SDL_BlitSurface(mob, NULL, screen, &rcMob);
                        }
                        if ( s->grille[x][y] == 5 )
                        {
                            rcObj.x = x * SPRITE_SIZE;
                            rcObj.y = y * SPRITE_SIZE;
                            rcGrass.x = x * SPRITE_SIZE;
                            rcGrass.y = y * SPRITE_SIZE;
                            SDL_BlitSurface(backbg, NULL, screen, &rcGrass);
                            SDL_BlitSurface(objectif, NULL, screen, &rcObj);
                        }
                        if ( s->grille[x][y] == 6 )
                        {
                            rcEpee.x = x * SPRITE_SIZE;
                            rcEpee.y = y * SPRITE_SIZE;
                            rcGrass.x = x * SPRITE_SIZE;
                            rcGrass.y = y * SPRITE_SIZE;
                            SDL_BlitSurface(backbg, NULL, screen, &rcGrass);
                            SDL_BlitSurface(epee, NULL, screen, &rcEpee);
                        }
                        if ( s->grille[x][y] == 7 )
                        {
                            rcPotion.x = x * SPRITE_SIZE;
                            rcPotion.y = y * SPRITE_SIZE;
                            rcGrass.x = x * SPRITE_SIZE;
                            rcGrass.y = y * SPRITE_SIZE;
                            SDL_BlitSurface(backbg, NULL, screen, &rcGrass);
                            SDL_BlitSurface(potion, NULL, screen, &rcPotion);
                        }
                        if ( s->grille[x][y] == 8 )
                        {
                            rcBouclier.x = x * SPRITE_SIZE;
                            rcBouclier.y = y * SPRITE_SIZE;
                            rcGrass.x = x * SPRITE_SIZE;
                            rcGrass.y = y * SPRITE_SIZE;
                            SDL_BlitSurface(backbg, NULL, screen, &rcGrass);
                            SDL_BlitSurface(bouclier, NULL, screen, &rcBouclier);
                        }
                    }
                }
            }




            /**< Affichage graphique du personnage */
            if ( move ==1 )
            {
                SDL_BlitSurface(sprite_left, NULL, screen, &rcSprite);
            }
            if ( move ==2)
            {
                SDL_BlitSurface(sprite_right, NULL, screen, &rcSprite);
            }
            if ( move ==3)
            {
                SDL_BlitSurface(sprite_up, NULL, screen, &rcSprite);
            }
            if ( move ==4)
            {
                SDL_BlitSurface(sprite_down, NULL, screen, &rcSprite);
            }
            if ( move ==0)
            {
                SDL_BlitSurface(sprite_down, NULL, screen, &rcSprite);
            }


            /**< Gestion des monstres en mouvement aléatoire */
            if ( rcMob2.x == rcSprite.x && rcMob2.y == rcSprite.y)
            {
                resultat=combat2(j,un);
                if ( resultat == 0)
                {
                    deadun=1;
                }
                else
                {
                    val = 1;
                    gameover=1;
                }
            }

            if ( rcMob3.x == rcSprite.x && rcMob3.y == rcSprite.y)
            {
                resultat=combat2(j,deux);
                if ( resultat == 0)
                {
                    deadeux=1;
                }
                else
                {
                    val = 1;
                    gameover=1;
                }
            }
            if ( deadun == 0)
            {
                move_monstre(&rcMob2,s);
                SDL_BlitSurface(mob2, NULL, screen, &rcMob2);
            }
            if (deadeux == 0 )
            {
                move_monstre(&rcMob3,s);
                SDL_BlitSurface(mob3, NULL, screen, &rcMob3);
            }


            SDL_UpdateRect(screen,0,0,0,0);
        }
    }

    /**< Libération de la mémoire */
    SDL_FreeSurface(sprite_right);
    SDL_FreeSurface(sprite_left);
    SDL_FreeSurface(sprite_up);
    SDL_FreeSurface(sprite_down);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(backbg);
    SDL_FreeSurface(wall);
    SDL_FreeSurface(fire);
    SDL_FreeSurface(life);
    SDL_FreeSurface(tableau);
    SDL_FreeSurface(mob);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(epee);
    SDL_FreeSurface(bouclier);
    SDL_FreeSurface(potion);

    free_grille(s);
    TTF_CloseFont(police);
    TTF_CloseFont(police2);
    TTF_Quit();
    SDL_Quit();

    return val;
}

void move_monstre(SDL_Rect *rcMob,grille *s)
{
    int alea=-1;
    alea=rand_a_b(0,11);
    if ( alea < 2)
    {
        if ( (rcMob->y)+32 < SCREEN_HEIGHT-50 && s->grille[(rcMob->x/32)][(rcMob->y/32)+1] != 1 )
        {
            rcMob->y += STEP_SIZE;
        }
    }
    if ( alea >= 2 && alea < 6)
    {
        if ( (rcMob->y)-32  >= 0 && s->grille[(rcMob->x/32)][(rcMob->y/32)-1] != 1 )
        {
            rcMob->y -= STEP_SIZE;
        }
    }
    if ( alea >= 6 && alea < 8)
    {
        if ((rcMob->x)-32  >= 0 && s->grille[(rcMob->x/32)-1][(rcMob->y/32)] != 1 )
        {
            rcMob->x -= STEP_SIZE;
        }
    }
    if ( alea >= 8 && alea < 10)
    {
        if ( (rcMob->x)+32  < SCREEN_WIDTH && s->grille[(rcMob->x/32)+1][(rcMob->y/32)] != 1 )
        {
            rcMob->x += STEP_SIZE;
        }
    }
}
