#include "jeux.h"

//Fonction qui initialise un ressort
T_ressort initRessort(int caseX, int caseY)
{
    printf("1\n");
    T_ressort ressort;           //Créé un ressort vide
printf("1\n");
    ressort.position.x = caseX;  //Initialise la position en x du ressort
    printf("1\n");
    ressort.position.y = caseY;  //Initialise la position en y du ressort
printf("1\n");
    return ressort;              //Retoune le ressort initialisé
}
