#include <stdio.h>
#include <stdlib.h>
#include "jeux.h"


int main()
{
    afficheMenu();                                 //Affiche le menu du jeu

    T_jeu *jeuN1 = initJeux(1, 10);                //Creer le niveau

    joueNiveau(jeuN1);                             //Joue le niveau selectionn�

    free(jeuN1);                                   //Lib�re l'espace prit par le niveau 1

    printf("\nOK");                                //Pour tester ou debugger

    return 0;
}
