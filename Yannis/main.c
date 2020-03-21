#include "jeux.h"



int main()
{
    srand(time(NULL));                                 //Pour faire de l'aleatoire

    int stop;                                          //Varibale pour stoper le jeu

    //afficheMenu();                                   //Affiche le menu du jeu

    while(stop == 0)                                   //Boucle tant que le jeu n'est pas stope
    {
        stop = 0;                                      //Permet d'eviter un bug lorsqu'on relance une partie et qu'elle se finie

        system("cls");                                 //Nettoie la console

        T_jeu *jeuN1 = initJeux(1, 15, 1, 10, 2, 10, 10, 5, 100);  //Cree le niveau

        joueNiveau(jeuN1);                             //Joue le niveau selectionne

        free(jeuN1);                                   //Libere l'espace prit par le niveau 1

        stop = rejouer();                              //Regarde si l'on doit stoper le jeu
    }

    return 0;
}
