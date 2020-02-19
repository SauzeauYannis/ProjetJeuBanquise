#include <stdio.h>
#include <stdlib.h>
#include "jeux.h"

//Retourne le type couleur qu'a choisi l'utilisateur
T_couleur choixCouleur()
{
    int couleur = -1;                                     //Declare un entier

    printf("\nChoisisez une couleur parmis : \n"
           "0 : Rouge\n"
           "1 : Vert\n"
           "2 : Bleu\n"
           "3 : Jaune\n");                                //Affiche le choix de couleur a l'utlisateur

    scanf("%d", &couleur);                                //Prend l'entier saisi par l'utilisateur

    if (couleur < 0 || couleur > 3)                       //Verifie que l'entier est compris entre 0 et 3
    {
        while (couleur < 0 || couleur > 3)                //Boucle jusqu'a ce que l'entier soit compris entre 0 et 3
        {
            printf("\nValeur incorrect, reessayer : ");   //Redemande a l'utilisateur de saisir une valeur
            scanf("%d", &couleur);                        //Recupere l'entier saisie
        }
    }

    switch (couleur)                                      //Transforme un entier en un type couleur pour le retourner
    {
    case 0 :
        return ROUGE;
        break;
    case 1 :
        return VERT;
        break;
    case 2 :
        return BLEU;
        break;
    case 3 :
        return JAUNE;
        break;
    default :
        return ERREUR;
    }
}

//Fonction qui retourne un type joueur selon un numero qui va l'identifier
T_joueur *initJoueur(int numeroJoueur)
{
    T_joueur *joueur = (T_joueur *)malloc(sizeof(T_joueur));  //Alloue de la memoire au type joueur
    T_point pos;                                              //Declare un type point
    pos.x = 0;                                                //Met le joueur sur la premiere ligne
    pos.y = numeroJoueur;                                     //Met le joueur a droite du precedent (en haut a gauche si premier joueur)

    printf("Veuillez choisir un nom pour le joueur numero %d : ", numeroJoueur+1);
    scanf("%s", joueur->nom);                     //Initialise le nom du joueur
    joueur->couleur = choixCouleur();             //Initialise la couleur de joueur
    joueur->identifiant = numeroJoueur;           //Initialise l'identifiant du joueur
    joueur->position = pos;                       //Initialise la position du joueur
    joueur->vecteur.dx = joueur->vecteur.dy = 0;  //Initialise le veteur deplacement du joueur
    joueur->score = 0;

    return joueur;                                //Retourne un pointeur de type joueur
}


