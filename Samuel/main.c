#include <stdio.h>
#include <stdlib.h>
#include "banquise.h"
#include "joueur.h"
#include "jeux.h"


int main()
{
    //T_banquise *banquise = initBanquise(10); //Definit une banquise de taille 50

    T_jeu jeuN1;
    jeuN1.banquise = initBanquise(10);

    remplitBanquise(jeuN1.banquise, 0);            //Remplit la banquise de 0

    ajouteJoueur(jeuN1.banquise);                  //Ajoute un joueur

    afficheBanquise(jeuN1.banquise);               //Affiche la banquise

    printf("OK");                                  //Pour tester ou debugger

    return 0;
}
