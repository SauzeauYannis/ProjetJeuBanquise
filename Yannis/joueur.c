#include <stdio.h>
#include <stdlib.h>
#include "general.h"

//Ajout d'un joueur sur un pointeur de type banquise
void ajouteJoueur(T_jeu *jeu)
{
    T_joueur joueur;                                //Declare un type joueur
    T_point pos;                                    //Declare un type position
    pos.x = 0;                                      //Met le joueur sur la premiere ligne
    pos.y = jeu->nombreJoueur;                      //Met le joueur a droite du joueur precedent

    printf("Veuillez choisir un nom "
           "pour le joueur numero %d : ",
           jeu->nombreJoueur+1);                    //Demande le nom du joueur
    scanf("%s", joueur.nom);                        //Initialise le nom du joueur
    joueur.couleur = choixCouleur();                //Initialise la couleur de joueur
    joueur.identifiant = jeu->nombreJoueur;         //Initialise l'identifiant du joueur
    joueur.position = pos;                          //Initialise la position du joueur
    joueur.vecteur.dx = joueur.vecteur.dy = 0;      //Initialise le veteur deplacement du joueur
    joueur.score = 0;                               //Initialise le score du joueur

    modifieCaseBanquise(jeu->banquise, pos, 1);     //Met le joueur dans la matrice de type banquise
    jeu->nombreJoueur++;                            //Rajoute un joueur dans le jeu
}

//Ajoute entre 1 et 4 joueurs au jeu
void ajouteJoueurs(T_jeu *jeu)
{
    int nbJoueurs = 0;                                 //Declare le nombre de joueurs

    while (nbJoueurs < 1 || nbJoueurs > 4)             //Verifie que l'utilisateur rentre un chiffre entre 1 et 4
    {
        printf("Nombre de joueurs (entre 1 et 4) : "); //Demande de rentrer un chiffre
        scanf("%d", &nbJoueurs);                       //Recupere le chiffre rentre
        system("cls");                                 //Nettoie la console
    }

    int i;                                             //Declare un entier pour la boucle

    for (i = 0; i < nbJoueurs; i++)                    //Rentre dans la boucle autant de fois qu'il y a de joueurs
    {
        ajouteJoueur(jeu);                             //Ajoute un joueur
        system("cls");                                 //Nettoie la console
    }
}
