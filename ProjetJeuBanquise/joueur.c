#include <stdio.h>
#include <stdlib.h>
#include "banquise.h"
#include "joueur.h"

//Ajout d'un joueur sur un pointeur de type banquise
void ajouteJoueur(T_banquise *banquise)
{
    T_joueur joueur; //Declare un type joueur

    printf("Veuillez choisir un nom de joueur : "); //Demande le nom du joueur
    scanf("%s", joueur.nom);                        //Initialise le nom du joueur
    joueur.couleur = ROUGE;                         //Initialise la couleur de joueur
    joueur.identifiant = 0;                         //Initialise l'identifiant du joueur
    joueur.position.x = joueur.position.y = 0;      //Initialise la position du joueur
    joueur.vecteur.dx = joueur.vecteur.dy = 0;      //Initialise le veteur deplacement du joueur
    joueur.score = 0;                               //Initialise le score du joueur

    banquise->tab[joueur.position.x][joueur.position.y] = 1; //Met le joueur dans la matrice de type banquise
}
