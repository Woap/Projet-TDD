#include <stdio.h>
#include <stdlib.h>
#include "../include/fonction_grille.h"



void new_grille(grille *x,int n, int m)
{
    int i;
    x->n=n;
    x->m=m;
    x->grille=(int **) malloc ((x->n)*sizeof(int*));
    for ( i=0 ; i < x->n ; i++ )
        x->grille[i]=(int*) malloc ((x->m)*sizeof(int));
}

void init_grille(grille *x)
{
    int i,j;
    for ( i=0 ; i < (x->n) ; i++ )
    {
        for ( j=0 ; j < (x->m) ; j++ )
        {
            x->grille[i][j]=0;
        }
    }

}


void lecture_grille(grille *x,joueur *p,mob *un,mob *deux)
{
    int n=0,m=0;
    FILE *fd;
    int lecture = 0;
    char temp[1];
    int i,j;
    int nombre=0;

    fd= fopen("../src/grille1.txt","r"); 

    if ( fd == NULL )
    {
        perror("Erreur ouverture grille");
        exit (1);
    }

    fscanf(fd,"%d %d",&n,&m); // taille de la grille
    new_grille(x,n,m);
    init_grille(x);


    fscanf(fd,"%d %d ",&(p->posx),&(p->posy)); // position du joueur
    fscanf(fd,"%d %d ",&(un->posx),&(un->posy)); // position mob 1
    fscanf(fd,"%d %d ",&(deux->posx),&(deux->posy));

    for ( i=0 ; i < x->m ; i ++)
    {
        for ( j=0 ; j < x->n; j++)
        {

            lecture = fgetc(fd);
            fgetc(fd);
            sprintf(temp,"%c",lecture);
            nombre= atoi(temp);
            x->grille[j][i] = nombre;
        }
    }

    fclose(fd);
}

void free_grille(grille *x)
{
    int i;
    for ( i = 0 ; i < (x->n) ; i ++ )
    {
        free(x->grille[i]);
    }

    free(x->grille);
}

