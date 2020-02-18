#include <stdio.h>
#include <stdlib.h>
#include "banquise.h"

//Retourne un pointeur de type banquise initialisé avec une taille en parametre
T_banquise *initBanquise(int taille)
{
    T_banquise *banquise = (T_banquise *)malloc(sizeof(T_banquise)); //Alloue de la memoire pour retourner un pointeur de type banquise

    int **banquiseTab;                                        //Declare la matrice qui va representer la banquise
    banquiseTab = (int **)malloc(taille * sizeof(int *));     //Alloue de la memoire aux lignes de la matrice
    int i;                                                    //Declare un entier pour une boucle for
    for (i = 0; i < taille; i++)                              //Boucle qui parcourt les colonnes de la matrice
    {
        banquiseTab[i] = (int *)malloc(taille * sizeof(int)); //Alloue de la memoire aux colonnes de la matrice
    }

    banquise->tab = banquiseTab;  //Met la matrice dans le pointeur banquise
    banquise->tailleN = taille;   //Met la taille dans le pointeur banquise
    banquise->nombreJ = 0;        //Met le nombre de joueurs a 0

    return banquise; //retourne le pointeur de type banquise
}

//Remplit le tableau du pointeur de type banquise avec la valeur donnee en parametre
void remplitBanquise(T_banquise *banquise, int valeur)
{
    int taille = banquise->tailleN; //Recupere la taille de la banquise
    int i, j;                       //Declare deux entier pour les boucles for

    for (i = 0; i < taille; i++) //Boucle qui parcourt les lignes de la matrice
    {
        for (j = 0; j < taille; j++) //Boucle qui parcourt les collones de la matrice
        {
            banquise->tab[i][j] = valeur; //Met la valeur de parametre a la case de ligne i et de colonne j
        }
    }
}

//Affichage du pointeur du type banquise
void afficheBanquise(T_banquise *banquise)
{
    int taille = banquise->tailleN; //Recupere la taille de la banquise
    int i, j;                       //Declare deux entier pour les boucles for

    for (i = 0; i < taille; i++) //Boucle qui parcourt les lignes de la matrice
    {
        printf("| ");   //Esthetique
        for (j = 0; j < taille; j++) //Boucle qui parcourt les collones de la matrice
        {
            printf("%d ", banquise->tab[i][j]); //Affiche la case de la matrice qui se trouve a la ligne i et la colonne j
        }
        printf("|\n"); //Esthetique
    }
}
