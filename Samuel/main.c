#include <stdio.h>
#include <stdlib.h>
#include "jeux.h"


int main()
{
    afficheMenu();                                 //Affiche le menu du jeu

    T_jeu *jeuN1 = initJeux(1, 10);                //Creer le niveau 1

    afficheJeu(jeuN1);                             //Affiche le jeu

    affichePositionJoueur(jeuN1->joueurs[0]);
    deplacementJoeur(jeuN1->joueurs[0], jeuN1->banquise->tailleN);
    printf("\n");
    affichePositionJoueur(jeuN1->joueurs[0]);

    free(jeuN1);                                   //Libère l'espace prit par le niveau 1

    printf("OK");                                  //Pour tester ou debugger

    return 0;
}
