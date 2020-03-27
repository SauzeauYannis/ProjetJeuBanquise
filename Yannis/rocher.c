#include "jeux.h"



//Retourne un rocher selon la position donnée en paramètre
T_rocher initRocher(T_point pos)
{
    T_rocher rocher;        //Variable qui stocke un rocher

    rocher.position = pos;  //Intialise la position du rocher

    return rocher;          //Retourne le rocher
}



//Retourne un tableau de rochers
T_rocher *initTabRochers(T_banquise *banquise, int nombreRochers)
{
    T_rocher *rochers = (T_rocher *)malloc(nombreRochers * sizeof(T_rocher));             //Alloue de la mémoire pour le tableau de rochers

    int i;                                                                                //Variable pour la boucle suivante

    for (i = 0; i < nombreRochers; i++)                                                   //Parcourt le tableau de rochers
    {
        T_point positionRocher = caseGlaceAleatoire(banquise, 1);                         //Initialise la position du rocher aléatoirement

        rochers[i] = initRocher(positionRocher);                                          //Initialise le rocher

        enleveCaseGlace(banquise, rochers[i].position.x, rochers[i].position.y, ROCHER);  //Met le rocher à sa position sur la banquise
    }

    return rochers;                                                                       //Retourne le tableau de rochers
}
