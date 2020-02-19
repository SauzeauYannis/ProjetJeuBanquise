#include <stdio.h>
#include <stdlib.h>
#include "jeux.h"


int main()
{
    afficheMenu();                                 //Affiche le menu du jeu

    T_jeu *jeuN1 = initJeux(1, 10);                //Creer le niveau 1

    afficheBanquise(jeuN1->banquise);              //Affiche la banquise

    free(jeuN1);                                   //Libère l'espace prit par le niveau 1

    printf("OK");                                  //Pour tester ou debugger

    return 0;
}
