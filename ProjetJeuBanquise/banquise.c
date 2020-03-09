#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "jeux.h"

//Retourne un pointeur de type banquise initialisé avec une taille en parametre
T_banquise *initBanquise(int taille)
{
    srand(time(NULL));

    T_banquise *banquise = (T_banquise *)malloc(sizeof(T_banquise)); //Alloue de la memoire pour retourner un pointeur de type banquise

    int **banquiseTab;                                               //Declare la matrice qui va representer la banquise
    banquiseTab = (int **)malloc(taille * sizeof(int *));            //Alloue de la memoire aux lignes de la matrice
    int i;                                                           //Declare un entier pour une boucle for
    for (i = 0; i < taille; i++)                                     //Boucle qui parcourt les colonnes de la matrice
    {
        banquiseTab[i] = (int *)malloc(taille * sizeof(int));        //Alloue de la memoire aux colonnes de la matrice
    }

    banquise->tab = banquiseTab;                                     //Met la matrice dans le pointeur banquise
    banquise->tailleN = taille;                                      //Met la taille dans le pointeur banquise
    banquise->glaces = NULL;                                         //Initialise le pointeur du tableau de glace a NULL
    banquise->nombreGlaces = 0;                                      //Initialise le nombre de glaces à 0

    banquise->depart.x = 1 + (rand() % (taille - 2));                //Genere aleatoirement la case de depart
    banquise->depart.y = 1;

    banquise->arrive.x = rand() % (taille);                          //Genere aleatoirement la case d'arrive
    banquise->arrive.y = (taille / 2) + (rand() % (taille / 2));

    return banquise;                                                 //Retourne le pointeur de type banquise
}



//Remplit le tableau du pointeur de type banquise avec la valeur donnee en parametre
void remplitBanquise(T_banquise *banquise, T_case valeur, int tailleEau)
{
    int taille = banquise->tailleN;  //Recupere la taille de la banquise
    int i, j;                        //Declare deux entier pour les boucles for

    for (i = 0; i < taille; i++)        //Boucle qui parcourt les lignes de la matrice
    {
        for (j = 0; j < taille; j++)    //Boucle qui parcourt les collones de la matrice
        {
            banquise->tab[i][j] = EAU;  //Met de l'eau a la case de ligne i et de colonne j
        }
    }

    for (i = tailleEau; i < taille - tailleEau; i++)      //Boucle qui parcourt les lignes ou la glace peut etre pose
    {
        for (j = tailleEau; j < taille - tailleEau; j++)  //Boucle qui parcourt les collones ou la glace peut etre pose
        {
            ajouteCaseGlace(banquise, i, j);              //Ajoute la glace (ligne i et colonne j) dans le tableau de glace de la banquise

            banquise->tab[i][j] = valeur;                 //Met la valeur de parametre a la case de ligne i et de colonne j
        }
    }
}



//Change une case de la banquise selon la valeur indiquee a l'emplacement donne
void modifieCaseBanquise(T_banquise *banquise, int caseX, int caseY, T_case valeur)
{
    banquise->tab[caseX][caseY] = valeur; //Met la valeur a l'emplcamenent donne en parametre
}



//Change la matrice de la banquise en y ajoutant les cases d'arrive et de depart
void ajouteDepartArrive(T_banquise *banquise)
{
    modifieCaseBanquise(banquise, banquise->depart.x, banquise->depart.y, DEPART);  //Modifie la case de depart
    modifieCaseBanquise(banquise, banquise->arrive.x, banquise->arrive.y, ARRIVE);  //Modifie la case d'arrive
}



//Ajoute une case glace dans le tableau de glaces de la banquise, selon l'emplacement donne en parametre
void ajouteCaseGlace(T_banquise *banquise, int caseX, int caseY)
{
    T_point glace;                                                                                   //Declare une variable point

    glace.x = caseX;                                                                                 //Initialise les valeurs de la glace selon les valeurs de parametre
    glace.y = caseY;

    banquise->nombreGlaces += 1;                                                                     //Augmente le nombre de glaces present sur la banquise
    banquise->glaces = (T_point *)realloc(banquise->glaces, banquise->nombreGlaces * sizeof(glace)); //Re-aloue de la memoire pour ajouter un glacon
    banquise->glaces[banquise->nombreGlaces - 1] = glace;                                            //Met la glace dans le tableau
}
