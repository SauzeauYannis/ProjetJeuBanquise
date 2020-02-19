#include <stdio.h>
#include <stdlib.h>
#include "jeux.h"

//Affiche le Menu du jeu
void afficheMenu()
{
    printf("Jeu de la banquise\n"
           "\n"
           "1-4 joueurs\n"
           "\n"
           "Bonne chance !\n"
           "\n"
           "Creer par :\n"
           "Samuel GOUBEAU\n"
           "Yannis SAUZEAU\n"
           "\n"
           "Appuyer sur entree pour continuer");  //Affiche le Menu

    char entree;                                  //Stocke un caractere
    entree = getchar();                           //Attend que la touche entree soit pressee

    system("cls");                                //Nettoie l'ecran
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
        jeu->joueurs[i] = (T_joueur *)realloc(jeu->joueurs[i], sizeof(T_joueur));                         //Re-alloue de la memoire pour le joueur
        jeu->joueurs[i] = initJoueur(i);                                                                  //Ajoute un joueur
        jeu->nombreJoueur++;                                                                              //Rajoute 1 au nombres de joueurs

        modifieCaseBanquise(jeu->banquise, jeu->joueurs[i]->position.x, jeu->joueurs[i]->position.y, 1);  //Ajoute le joueur sur la banquise

        system("cls");                                 //Nettoie la console
    }
}

//Retourne un pointeur de type jeu en fonction du niveau et de la taille de la banquise
T_jeu *initJeux(int niveau, int taille)
{
    T_jeu *jeu = (T_jeu *)malloc(sizeof(T_jeu));               //Aloue de l'espace memoire a un pointeur de type jeu

    jeu->banquise = initBanquise(taille);                      //Initialise la banquise dans le jeu
    jeu->joueurs = (T_joueur **)malloc(sizeof(T_joueur *));    //Aloue de la memoire pour creer un tableau de pointeur de joueur
    jeu->nombreJoueur = 0;                                     //Initialise le nombre de joueur
    jeu->nombreTour = 0;                                       //Initialise le nombre de tour
    jeu->IdJeu = niveau;                                       //Initialise le niveau

    remplitBanquise(jeu->banquise, 0);                         //Remplit la banquise de 0
    ajouteJoueurs(jeu);                                        //Ajoute les joueurs

    return jeu;                                                //Retourne le pointeur de type jeu
}
