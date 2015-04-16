/**
* @file jeu.h
* @brief fonctionnalité du jeu
* @author ibis ibrahim
* @date 11/04/2015
*/

#ifndef __JEU_H_
#define __JEU_H_


typedef struct {
    int posx ;
    int posy ;
    int vie ;
    int att ;
    int def ;
    char tab[10] ;
} joueur ;

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
* @brief affichage d'une grille ( INDICATION VALEUR : 0=VIDE / 1=MUR / 2=PIEGE )
* @param grille x -> une grille quelconque
*/
void affiche_grille(grille *x,joueur *q);

/**
* @brief lecture fichier texte
* @param grille *x -> adresse d'une grille quelconque / joueur *p -> adresse d'un joueur
*/
void lecture_grille(grille *x, joueur *p);

/**
* @brief deplacement du joueur
* @param  grille *x -> adresse d'une grille quelconque / joueur *j -> adresse d'un joueur
*/
void deplacer_joueur(grille *x, joueur *j);

/**
* @brief initialisation des points du joueur
* @param  joueur *p -> adresse d'un joueur
*/
void init_joueur( joueur *p);

/**
* @brief libère la grille
* @param grille x -> une grille quelconque
*/
void free_grille(grille *x);

/**
* @brief renvoie le nombre de cases non vides
* @param grille *x -> adresse  d'une grille quelconque
*/
int nb_case_nvide(grille *x);

#endif
