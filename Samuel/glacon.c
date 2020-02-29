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
    vect.dy = 0;  //Initialise le vecteur à 0

    glacon->position = pos;
    glacon->vecteur = vect;
    glacon->pourcentage_fondre = 0;

    return glacon;         //Retourne le glaçon
}
