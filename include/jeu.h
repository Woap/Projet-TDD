/**
* @file jeu.h
* @brief fonctionnalit� principale du jeu
* @author ibis ibrahim
* @date 13/05/2015
*/

#ifndef __JEU_H_
#define __JEU_H_
#include "SDL_image.h"
#include "../include/fonction_grille.h"
#include "../include/fonction_jeu.h"

/**
* @brief fonction principal du jeu :
* - Affichage graphique avec l'aide de SDL
* - G�re l'interaction avec le joueur ( gestion des touches clavier / souris )
* > Les touches fl�ch�s pour le deplacement
* > 'p' pour pause
* > 'q' ou '�chap' pour quitter
* > 'r' pour recommencer
* > 'c' pour l'utilisation de la potion ( les effets du bouclier et de l'�p�e sont automatiques )
* - G�re les int�ractions entre le joueur et les objets
* - D�placement du joueur avec la souris
* - D�placements de monstres al�atoires
* - Affichage du tableau de score ( vie restante / caract�ristique personnage / inventaire )
* - Syst�me de combat entre le joueur et les monstres
* @param (joueur *j) -> pointeur sur le joueur / (grille *s) -> pointeur sur la grille / (mob *un) -> pointeur sur monstre1 / (mob *deux) -> pointeur sur monstre2
* @return retourne un entier : 0 pour l'arret / 1 pour le relancement du jeu
*/
int jeu(joueur *j,grille *s,mob *un, mob *deux);

/**
* @brief mouvement al�atoire des monstres
* @param (SDL_Rect *rcMob2) -> pointeur sur rcMob / (grille *s) -> pointeur sur la grille
*/
void move_monstre(SDL_Rect *rcMob2,grille *s);

#endif
