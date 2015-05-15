#include <stdio.h>
#include <stdlib.h>
#include "../../include/1.0/jeu.h"
#include "curses.h"

#define VIE_MAX 5;

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


void affiche_grille(grille *x,joueur *q)
{
    int i,j;
    x->grille[q->posx][q->posy]=9;
    mvprintw(0,0,"VIE: %d",q->vie);
    mvprintw(1,0,"ATT: %d | DEF : %d ",q->att,q->def);

    for ( i= 0 ; i < x->n ; i++)
        mvprintw(2,i+1,"-");


    for ( i = 0 ; i < (x->m) ; i++ )
    {

        for ( j = 0 ; j < (x->n) ; j++ )
        {
			mvprintw(i+3,0,"|");
            mvprintw(i+3,j+1,"%d",x->grille[i][j]);
			mvprintw(i+3,x->n+1,"|");
        }

    }

    for ( i= 0 ; i < x->n ; i++)
        mvprintw(x->m+3,i+1,"-");

    refresh();


}


void lecture_grille(grille *x,joueur *p)
{
    int n=0,m=0;
    FILE *fd;
    int lecture = 0;
    char temp[1];
    int i,j;
    int nombre=0;

    fd= fopen("../src/grille2.txt","r");

    if ( fd == NULL )
    {
        perror("Erreur ouverture grille");
        exit (1);
    }

    fscanf(fd,"%d %d",&n,&m); // taille de la grille
    new_grille(x,n,m);
    init_grille(x);


    fscanf(fd,"%d %d ",&(p->posx),&(p->posy)); // position du joueur

    for ( i=0 ; i < x->m ; i ++)
    {
        for ( j=0 ; j < x->n; j++)
        {

            lecture = fgetc(fd);
            fgetc(fd);
            sprintf(temp,"%c",lecture);
            nombre= atoi(temp);
            x->grille[i][j] = nombre;
        }
    }

	fclose(fd);
}


int deplacer_joueur(grille *x, joueur *j,int gwin)
{
    int key;
    key=0;
    key = getch() ;


    switch(key)
    {
    case 'q': //GAUCHE
        if (j->posy-1 < 0)
            break;
        if (x->grille[j->posx][j->posy-1] == 1 )
            break;
        if (x->grille[j->posx][j->posy-1] == 2 )
            j->vie--;
        if (x->grille[j->posx][j->posy-1] == 3 )
            j->vie++;
        if (x->grille[j->posx][j->posy-1] == 5 )
            gwin=1;
        if (x->grille[j->posx][j->posy-1] == 3 )
            j->vie++;
        if (x->grille[j->posx][j->posy-1] == 6 )
            j->att++;
        if (x->grille[j->posx][j->posy-1] == 7 )
            j->vie=VIE_MAX;
        if (x->grille[j->posx][j->posy-1] == 8 )
            j->def++;

        x->grille[j->posx][j->posy]=0;
        j->posy--;

        break;

    case 'd': //DROITE
        if (j->posy+1 > x->n-1)
            break;
        if (x->grille[j->posx][j->posy+1] == 1 )
            break;
        if (x->grille[j->posx][j->posy+1] == 2 )
            j->vie--;
        if (x->grille[j->posx][j->posy+1] == 3 )
            j->vie++;
        if (x->grille[j->posx][j->posy+1] == 5 )
            gwin=1;
        if (x->grille[j->posx][j->posy+1] == 3 )
            j->vie++;
        if (x->grille[j->posx][j->posy+1] == 6 )
            j->att++;
        if (x->grille[j->posx][j->posy+1] == 7 )
            j->vie=VIE_MAX;
        if (x->grille[j->posx][j->posy+1] == 8 )
            j->def++;

        x->grille[j->posx][j->posy]=0;
        j->posy++;
        break;
    case 's': // BAS
        if (j->posx+1 > x->m-1)
            break;
        if (x->grille[j->posx+1][j->posy] == 1 )
            break;
        if (x->grille[j->posx+1][j->posy] == 2 )
            j->vie--;
        if (x->grille[j->posx+1][j->posy] == 3 )
            j->vie++;
        if (x->grille[j->posx+1][j->posy] == 5  )
            gwin=1;
        if (x->grille[j->posx+1][j->posy] == 3 )
            j->vie++;
        if (x->grille[j->posx+1][j->posy] == 6 )
            j->att++;
        if (x->grille[j->posx+1][j->posy] == 7 )
            j->vie=VIE_MAX;
        if (x->grille[j->posx+1][j->posy] == 8 )
            j->def++;

        x->grille[j->posx][j->posy]=0;
        j->posx++;
        break;
    case 'z': //HAUT
        if (j->posx-1 < 0)
            break;
        if (x->grille[j->posx-1][j->posy] == 1 )
            break;
        if (x->grille[j->posx-1][j->posy] == 2 )
            j->vie--;
        if (x->grille[j->posx-1][j->posy] == 3 )
            j->vie++;
        if (x->grille[j->posx-1][j->posy] == 5  )
            gwin=1;
        if (x->grille[j->posx-1][j->posy] == 3 )
            j->vie++;
        if (x->grille[j->posx-1][j->posy] == 6 )
            j->att++;
        if (x->grille[j->posx-1][j->posy] == 7 )
            j->vie=VIE_MAX;
        if (x->grille[j->posx-1][j->posy] == 8 )
            j->def++;

        x->grille[j->posx][j->posy]=0;
        j->posx--;
        break;
    }

    return gwin;
}

void init_joueur( joueur *p)
{
    p->att=1;
    p->def=1;
    p->vie=5;
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

int nb_case_nvide(grille *x)
{
    int i,j;
    int nb_case=0;
    for ( i = 0 ; i < x->n ; i++)
        for ( j=0 ; j < x->m ; j++)
            if ( x->grille[i][j] != 0 )
            {
                nb_case++;
            }
    return nb_case;
}

