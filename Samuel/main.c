#include "jeux.h"


int main()
{
    srand(time(NULL));                                                              //Pour faire de l'aleatoire

    int stop;

    afficheMenu();                                     //Affiche le menu du jeu

    while(stop == 0)
    {
        stop = 0;                                      //Permet d'eviter un bug lorsqu'on relance une partie et qu'elle se finie
        system("cls");
        T_jeu *jeuN1 = initJeux(1,15);                 //Creer le niveau

        joueNiveau(jeuN1);                             //Joue le niveau selectionne

        free(jeuN1);                                   //Libere l'espace prit par le niveau 1

        stop = rejouer();
    }

    return 0;
}
