#include <stdio.h>
#include <stdlib.h>
#include "jeux.h"


int main()
{
    int stop;

    afficheMenu();                                     //Affiche le menu du jeu

    while(stop == 0)
    {
        stop = 0;                                      //Permet d'�viter un bug lorsqu'on relance une partie et qu'elle se finie
        system("cls");
        T_jeu *jeuN1 = initJeux(1,10);                //Creer le niveau

        joueNiveau(jeuN1);                             //Joue le niveau selectionn�

        free(jeuN1);                                   //Lib�re l'espace prit par le niveau 1

        stop = rejouer();
    }

    return 0;
}
