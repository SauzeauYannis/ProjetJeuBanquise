#include <stdio.h>
#include <stdlib.h>
#include "banquise.h"
#include "joueur.h"


int main()
{
    T_banquise *banquise = initBanquise(10); //Definit une banquise de taille 50

    remplitBanquise(banquise, 0);            //Remplit la banquise de 0

    ajouteJoueur(banquise);                  //Ajoute un joueur

    afficheBanquise(banquise);               //Affiche la banquise

    printf("OK");                            //Pour tester ou debugger

    return 0;
}
