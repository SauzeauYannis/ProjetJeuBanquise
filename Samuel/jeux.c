#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jeux.h"

T_jeu initJeux(int nbj, int taille)
{
    srand(time(NULL));

    T_jeu jeu;

    jeu.banquise = initBanquise(taille);
    jeu.nombreJoueur = nbj;
    jeu.nombreTour = 0;
    jeu.IdJeu = rand()%99;

    remplitBanquise(jeu.banquise, 0);            //Remplit la banquise de 0
    ajouteJoueur(jeu.banquise);                  //Ajoute un joueur

    return jeu;
}
