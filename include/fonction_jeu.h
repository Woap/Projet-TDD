/**
* @file fonction_jeu.h
* @brief les fonctions du jeu
* @author ibis ibrahim
* @date 13/05/2015
*/

#ifndef __FONCTION_JEU_H_
#define __FONCTION_JEU_H_


/**
* @brief caractéristique joueur
*/
typedef struct {
    int posx ;
    int posy ;
    int vie ;
    int att ;
    int def ;
    char tab[10] ;
} joueur ;

/**
* @brief caractéristique monstre
*/
typedef struct {
    int posx ;
    int posy ;
    int vie;
    int att;
} mob ;

/**
* @brief initialise le joueur
* @param (joueur *p) -> pointeur sur le joueur
*/
void init_joueur( joueur *p);

/**
* @brief initialise le monstre qui bouge
* @param (mob *p) -> pointeur sur le monstre
*/
void init_mobv2( mob *m);

/**
* @brief initialise le monstre statique
* @param (mob *m) -> pointeur sur le monstre
*/
void init_mob( mob *m);

/**
* @brief initialise le joueur
* @param (mob *m) -> pointeur sur le joueur
*/
void init_mob( mob *m);

/**
* @brief combat entre joueur et monstre statique
* @param (joueur *j) -> pointeur sur le joueur
* @return retourne 0 si victoire sinon 1
*/
int combat(joueur *j);

/**
* @brief combat entre joueur et monstre qui bouge
* @param (joueur *p) -> pointeur sur le joueur, (mob *nb) -> pointeur sur monstre
* @return retourne 0 si victoire sinon 1
*/
int combat2(joueur *j, mob *nb);

/**
* @brief fonction pour mettre en pause le jeu ( touche p )
*/
void pause();

/**
* @brief renvoie un entier aléatoire
* @param (int a) -> valeur min / (int b) -> valeur max
*/
int rand_a_b(int a, int b);


#endif
