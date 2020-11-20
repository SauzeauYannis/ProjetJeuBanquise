#include "jeux.h"



//Fonction qui initialise un ressort
T_ressort initRessort(T_point position)
{
    T_ressort ressort;           //créé un ressort vide

    ressort.position = position; //Enregistre la position du ressort avec la position en paramètre

    return ressort;              //Retourne le ressort
}



//Initialise un tableau de ressort
T_ressort *initTabRessorts(T_banquise *banquise, int nombreRessorts)
{
    T_ressort *ressorts = (T_ressort *)malloc(nombreRessorts * sizeof(T_ressort));           //Alloue de la mémoire pour un tableau ressort

    int i;

    for (i = 0; i < nombreRessorts; i++)                                                     //Boucle qui parcourt le tableau de ressort
    {
        T_point positionRessort = caseGlaceAleatoire(banquise, 1);                           //Initialise une position à une case aléatoire valide sur la banquise

        ressorts[i] = initRessort(positionRessort);                                          //Initialise le ressort à la position i dans le tableau

        enleveCaseGlace(banquise, ressorts[i].position.x, ressorts[i].position.y, RESSORT);  //Remplace la case de glace en un ressort sur la banquise en fonction de la position de celui-ci
    }

    return ressorts;                                                                         //Retourne le tableau de ressort
}



//Fonction qui va modifier le vecteur du glaçon quand il touche une ressort
void glaconToucheRessort(T_glacon *glacon)
{
    int direction = rand()% 3;                                         //Initialise un entier aléatoire entre 0 et 2
    int Gdx = glacon->vecteur.dx, Gdy = glacon->vecteur.dy;            //Enregistre le vecteur du glaçon

    switch(direction)
    {
    case 0 :
        glacon->vecteur.dx *= -1, glacon->vecteur.dy *= -1;            //Le direction du glaçon va être inversée
        break;
    case 1 :
        glacon->vecteur.dx = Gdy * -1, glacon->vecteur.dy = Gdx * -1;  //Le glaçon va soit aller à droite, soit à gauche du ressort en fonction de son vecteur de départ
        break;
    default :
        glacon->vecteur.dx = Gdy, glacon->vecteur.dy = Gdx;            //Le glaçon va soit aller à droite, soit à gauche du ressort en fonction de son vecteur de départ
    }
}
