#include <stdio.h>
#include <stdlib.h>
#include "general.h"


int main()
{
    T_jeu *jeuN1 = initJeux(1, 10);                //Creer le niveau 1

    afficheBanquise(jeuN1->banquise);              //Affiche la banquise

    printf("OK");                                  //Pour tester ou debugger

    return 0;
}
