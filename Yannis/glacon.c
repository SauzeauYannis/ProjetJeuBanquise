#include <stdio.h>
#include <stdlib.h>
#include "jeux.h"

//Fonction qui initialise un glaçon
T_glacon *initGlacon(int caseX, int caseY)
{
    T_glacon *glacon = (T_glacon *)malloc(sizeof(T_glacon));  //Alloue de la mémoire pour le glaçon
    T_point pos;            //Créer un point qui sera la position du glaçon
    pos.x = caseX;          //Initialise la postion du glaçon via les paramètres
    pos.y = caseY;
    T_vecteur vect;         //Créer le vecteur du glacon
    vect.dx = 1;
    vect.dy = 0;            //Initialise le vecteur à 0

    glacon->position = pos;
    glacon->vecteur = vect;
    glacon->pourcentage_fondre = 0;

    return glacon;         //Retourne le glaçon
}



//Fonction qui vérifie que le vecteur du glaçon est valide : HAUT BAS GAUCHE DROITE
int verifieVecteurGlacon(T_glacon *glacon)
{
    int dx = glacon->vecteur.dx, dy = glacon->vecteur.dy;

    if(dx != 0 && dy != 0)
    {
        printf("Le vecteur du glacon à la position x = %d y = %d est incorrecte !", glacon->position.x, glacon->position.y);
        return -1;
    }
    else
    {
        return 0;
    }
}



//Fonction qui vérifie si le glaçon touche  un rebord ou non
int verifieDeplacementGlacon(int caseX, int caseY,int caseValeur, int taille)
{
    if (caseX < 0 || caseX >= taille || caseY < 0 || caseY >= taille) return -1;
    else if(caseValeur != 0) return -1;
    else return 0;         //Entier de validation sinon
}
