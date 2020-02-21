#include <stdio.h>
#include <stdlib.h>
#include "jeux.h"


int main()
{
    int stop = 0;
    char c;

    afficheMenu();                                     //Affiche le menu du jeu

    while(stop == 0)
    {
        system("cls");
        T_jeu *jeuN1 = initJeux(1, 10);                //Creer le niveau

        joueNiveau(jeuN1);                             //Joue le niveau selectionné

        free(jeuN1);                                   //Libère l'espace prit par le niveau 1

        stop = rejouer();

    }

    return 0;
}
