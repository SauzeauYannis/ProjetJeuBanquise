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
    vect.dx = 1;
    vect.dy = 0;  //Initialise le vecteur � 0

    glacon->position = pos;
    glacon->vecteur = vect;
    glacon->pourcentage_fondre = 0;

    return glacon;         //Retourne le gla�on
}
