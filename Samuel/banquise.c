#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "jeux.h"

//Retourne un pointeur de type banquise initialisé avec une taille en parametre
T_banquise *initBanquise(int taille)
{
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
    banquise->depart.x = banquise->depart.y =                        //Initialise les cases d'arrivee et de depart
    banquise->arrive.x = banquise->arrive.y = 0;

    banquise->tabGlaces = (T_point *)malloc(taille * taille * sizeof(T_point)); //Alloue de memoire pour le tableau de glaces

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

    ajouteDepartArrive(banquise, tailleEau);              //Ajoute la case d'arrivee et la case de depart
}



//Change une case de la banquise selon la valeur indiquee a l'emplacement donne
void modifieCaseBanquise(T_banquise *banquise, int caseX, int caseY, T_case valeur)
{
    banquise->tab[caseX][caseY] = valeur; //Met la valeur a l'emplcamenent donne en parametre
}



//Change la matrice de la banquise en y ajoutant les cases d'arrive et de depart
void ajouteDepartArrive(T_banquise *banquise, int tailleEau)
{
    srand(time(NULL));                                                              //Pour faire de l'aleatoire

    int taille = banquise->tailleN;                                                 //Recupere la taille de la banquise

    banquise->depart.x = 1 + tailleEau + (rand() % (taille - 1 - (tailleEau * tailleEau)));       //Genere aleatoirement la case de depart
    banquise->depart.y = 1 + tailleEau;

    banquise->arrive.x = tailleEau + (rand() % (taille - tailleEau));       //Genere aleatoirement la case d'arrive
    banquise->arrive.y = (taille / 2) + (rand() % (taille / 2)) - tailleEau;

    enleveCaseGlace(banquise, banquise->depart.x, banquise->depart.y, DEPART);  //Modifie la case de depart
    enleveCaseGlace(banquise, banquise->arrive.x, banquise->arrive.y, ARRIVE);  //Modifie la case d'arrive
}



//Ajoute une case glace dans le tableau de glaces de la banquise, selon l'emplacement donne en parametre
void ajouteCaseGlace(T_banquise *banquise, int caseX, int caseY)
{
    T_point glace;                                                 //Declare une variable point

    glace.x = caseX;                                               //Initialise les valeurs de la glace selon les valeurs de parametre
    glace.y = caseY;

    int i;                                                         //Variable pour la boucle

    for (i = 0; i < (banquise->tailleN * banquise->tailleN); i++)  //Boucle qui parcourt le tableau de glaces
    {
        if (banquise->tabGlaces[i].estPresent == 0)                //Verifie qu'une case du tabelau peut prendre une glace
        {
            banquise->tabGlaces[i].estPresent = 1;                 //Dis qu'il y a une glace dans le tableau
            banquise->tabGlaces[i].position = glace;               //Met la glace dans le tableau
            break;                                                 //Sort de la boucle
        }
    }

    modifieCaseBanquise(banquise, caseX, caseY, GLACE);            //Met la glace sur la banquise
}

//Enleve une glace du tableau de glace selon sa position et remplace la glace par une autre valeur de case
void enleveCaseGlace(T_banquise *banquise, int caseX, int caseY, T_case valeur)
{
    int i;                                                                                                                                       //Variable pour la boucle

    for (i = 0; i < (banquise->tailleN * banquise->tailleN); i++)                                                                                //Boucle qui parcourt le tableau de glace
    {
        if (banquise->tabGlaces[i].position.x == caseX && banquise->tabGlaces[i].position.y == caseY && banquise->tabGlaces[i].estPresent == 1)  //Verifie que la glace est bien a la bonne position et presente dans le jeu
        {
            banquise->tabGlaces[i].estPresent = 0;                                                                                               //Dis qu'il n'y a plus de glace a cette position
            break;                                                                                                                               //Sort de la boucle
        }
    }

    modifieCaseBanquise(banquise, caseX, caseY, valeur);                                                                                         //Change l'ancienne glace en un autre type
}
