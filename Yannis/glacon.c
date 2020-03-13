#include <stdio.h>
#include <stdlib.h>
#include "jeux.h"

//Fonction qui initialise un gla�on
T_glacon *initGlacon(int caseX, int caseY)
{
    T_glacon *glacon = (T_glacon *)malloc(sizeof(T_glacon));  //Alloue de la m�moire pour le gla�on
    T_point pos;            //Cr�er un point qui sera la position du gla�on
    pos.x = caseX;          //Initialise la postion du gla�on via les param�tres
    pos.y = caseY;
    T_vecteur vect;         //Cr�er le vecteur du glacon
    vect.dx = 0;
    vect.dy = 0;            //Initialise le vecteur � 0

    glacon->position = pos;
    glacon->vecteur = vect;
    glacon->pourcentage_fondre = 0;

    return glacon;         //Retourne le gla�on
}



//Fonction qui v�rifie que le vecteur du gla�on est valide : HAUT BAS GAUCHE DROITE
int verifieVecteurGlacon(T_glacon *glacon)
{
    int dx = glacon->vecteur.dx, dy = glacon->vecteur.dy;

    if(dx != 0 && dy != 0)
    {
        printf("Le vecteur du glacon � la position x = %d y = %d est incorrecte !", glacon->position.x, glacon->position.y);
        return -1;
    }
    else
    {
        return 0;
    }
}



//Fonction qui v�rifie si le gla�on touche  un rebord ou non
int verifieDeplacementGlacon(int caseX, int caseY, int caseValeur, int taille)
{
    switch (caseValeur)
    {
    case -1:                                                                        //Retourne une valeur d'echec pour prevenir la fonction suivante
    case DEPART:
    case ARRIVE:
        return -1;
        break;
    case JOUEUR:
        return 1;                                                                   //Retourne une valeur pour dire que le gla�on touche un joueur
        break;
    case EAU:
        return 2;                                                                   //Retourne une valeur pour indiquer que la gla�on touche de l'eau
        break;
    default :
        return 0;                                                                   //Entier de validation
    }
}


//Fonction qui se charge de d�placer le gla�on en paramettre
int deplacementGlacon(T_glacon *glacon, T_banquise *banquise)
{
    ajouteCaseGlace(banquise, glacon->position.x, glacon->position.y);

    int posx = glacon->position.x, posy = glacon->position.y;          //Position du gla�on avant son d�placement
    int x = posx + glacon->vecteur.dx, y = posy + glacon->vecteur.dy;  //Position vers laquelle le gla�on se d�place
    int taille = banquise->tailleN;
    int caseValeur, verif;

    if(x < 0 || x >= taille || y < 0 || y >= taille)                   //V�rifie si le gla�on se d�place en dehors du cadre
    {
        caseValeur = -1;
    }
    else
    {
        caseValeur = banquise->tab[x][y];
    }

    verif = verifieDeplacementGlacon(x, y, caseValeur, taille);

    switch(verif)
    {
        case -1 :
            glacon->vecteur.dx = glacon->vecteur.dy = 0;
            return 0;
            break;
        case 1 :
            return 1;
            break;
        case 2 :
            glacon->position.x = x, glacon->position.y = y;
            glacon->vecteur.dx = glacon->vecteur.dy = 0;
            return 2;
            break;
        default :
            glacon->position.x = x, glacon->position.y = y;
            return 0;
    }
}
