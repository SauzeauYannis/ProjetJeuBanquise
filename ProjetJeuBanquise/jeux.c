#include <stdio.h>
#include <stdlib.h>
#include "general.h"

T_jeu *initJeux(int niveau, int taille)
{
    T_jeu *jeu = (T_jeu *)malloc(sizeof(T_jeu));

    jeu->banquise = initBanquise(taille);
    jeu->nombreJoueur = 0;
    jeu->nombreTour = 0;
    jeu->IdJeu = niveau;

    remplitBanquise(jeu->banquise, 0);            //Remplit la banquise de 0
    ajouteJoueur(jeu->banquise);                  //Ajoute un joueur

    return jeu;
}
