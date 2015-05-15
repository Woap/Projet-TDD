/**
* @file fonction_grille.h
* @brief les fonctions de la grille
* @author ibis ibrahim
* @date 13/05/2015
*/
#include "fonction_jeu.h"

#ifndef __FONCTION_GRILLE_H_
#define __FONCTION_GRILLE_H_


/**
* @brief caractéristique de la grille
*/
typedef struct
{
    int ** grille ;
    int n ;
    int m ;
} grille ;

/**
* @brief créer une nouvelle grille
* @param (int n) -> ligne de la grille / (int m) -> colonne de la grille
* @return retourne une grille de taille n*m
*/
void new_grille(grille *x,int n, int m);

/**
* @brief initialise une grille
* @param grille x -> une grille quelconque
* @return retourne une grille initialisé à 0
*/
void init_grille(grille *x);

/**
* @brief lecture fichier texte
* @param grille *x -> adresse d'une grille quelconque / joueur *p -> adresse d'un joueur / mob *un - mob *deux -> pointeur sur les deux monstres
*/
void lecture_grille(grille *x, joueur *p, mob *un,mob *deux);


/**
* @brief libère la grille
* @param grille x -> une grille quelconque
*/
void free_grille(grille *x);

#endif
