#include "jeux.h"



//Fonction qui initialise la matrice qui represente le jeu
int **initMatrice(int tailleMatrice)
{
    int **matrice;                                                  //Declare la matrice qui va representer la banquise

    matrice = (int **)malloc(tailleMatrice * sizeof(int *));        //Alloue de la memoire aux lignes de la matrice

    int i;                                                          //Declare un entier pour une boucle for

    for (i = 0; i < tailleMatrice; i++)                             //Boucle qui parcourt les colonnes de la matrice
    {
        matrice[i] = (int *)malloc(tailleMatrice * sizeof(int));    //Alloue de la memoire aux colonnes de la matrice
    }

    return matrice;                                                 //Retourne la matrice initialise
}



//Fonction qui initialise un tableau de glaces
T_glace *initTabGlaces(int taille)
{
    T_glace *tabGlaces = (T_glace *)malloc(taille * sizeof(T_glace));  //Aloue de la memoire pour le tableau

    int i;                                                             //Variable pour la boucle

    for (i = 0; i < taille; i++)                                       //Boucle qui parcourt le tableau de glaces
    {
        tabGlaces[i].estPresent = 0;                                   //Initialise la valeur pour dire qu'il n'y a pas de glace a la position qui suit
        tabGlaces[i].position.x =
        tabGlaces[i].position.y = 0;                                   //Initialise la position de la glace
    }

    return tabGlaces;                                                  //Retourne le tableau de glace initialise
}



//Change une case de la banquise selon la valeur indiquee a l'emplacement donne
void modifieCaseBanquise(T_banquise *banquise, int caseX, int caseY, T_case valeur)
{
    banquise->matrice[caseX][caseY] = valeur;  //Met la valeur dans la banquise a l'emplcamenent donne en parametre
}



//Ajoute une case glace dans le tableau de glaces de la banquise, selon l'emplacement donne en parametre
void ajouteCaseGlace(T_banquise *banquise, int caseX, int caseY)
{
    T_point glace;                                                 //Declare une variable point pour la position de la glace a ajouter

    glace.x = caseX, glace.y = caseY;                              //Initialise la position de la glace selon les valeurs de parametre

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
    banquise->nombreGlaces++;                                      //Incremente le nombre de glace
}



//Enleve une glace du tableau de glace selon sa position et remplace la glace par une autre valeur de case
void enleveCaseGlace(T_banquise *banquise, int caseX, int caseY, T_case valeur)
{
    int i;                                                         //Variable pour la boucle

    for (i = 0; i < (banquise->tailleN * banquise->tailleN); i++)  //Boucle qui parcourt le tableau de glace
    {
        if (banquise->tabGlaces[i].position.x == caseX
            && banquise->tabGlaces[i].position.y == caseY
            && banquise->tabGlaces[i].estPresent == 1)             //Verifie que la glace est bien a la bonne position et presente dans le jeu
        {
            banquise->tabGlaces[i].estPresent = 0;                 //Dis qu'il n'y a plus de glace a cette position
            break;                                                 //Sort de la boucle
        }
    }

    modifieCaseBanquise(banquise, caseX, caseY, valeur);           //Change l'ancienne glace en un autre type
    banquise->nombreGlaces--;                                      //Decremente le nombre de glaces
}



//Change la matrice de la banquise en y ajoutant les cases d'arrive et de depart
void ajouteDepartArrive(T_banquise *banquise)
{
    int taille = banquise->tailleN,                                                          //Recupere la taille de la banquise
        tailleEau = banquise->tailleEau;                                                     //Recupere la taille de l'eau autour de la banquise

    banquise->depart.x = 1 + tailleEau + (rand() % (taille - 2 - (tailleEau * tailleEau)));  //Genere aleatoirement la case de depart
    banquise->depart.y = 1 + tailleEau;

    banquise->arrive.x = tailleEau + (rand() % (taille - 1 -(tailleEau * tailleEau)));       //Genere aleatoirement la case d'arrive
    banquise->arrive.y = taille - 1 - tailleEau;

    enleveCaseGlace(banquise, banquise->depart.x, banquise->depart.y, DEPART);               //Modifie la case de depart
    enleveCaseGlace(banquise, banquise->arrive.x, banquise->arrive.y, ARRIVE);               //Modifie la case d'arrive
}



//Remplit le tableau du pointeur de type banquise avec la taille de nombre de cases d'eau qui entoure la glace de la banquise
void remplitBanquise(T_banquise *banquise)
{
    int taille = banquise->tailleN,                       //Recupere la taille de la banquise
        tailleEau = banquise->tailleEau,                  //Recupere la taille de l'eau qui entoure la banquise
        i, j;                                             //Declare deux entier pour les boucles for

    for (i = 0; i < taille; i++)                          //Boucle qui parcourt les lignes de la matrice
    {
        for (j = 0; j < taille; j++)                      //Boucle qui parcourt les collones de la matrice
        {
            modifieCaseBanquise(banquise, i, j, EAU);     //Met de l'eau a la case de ligne i et de colonne j
        }
    }

    for (i = tailleEau; i < taille - tailleEau; i++)      //Boucle qui parcourt les lignes ou la glace peut etre pose
    {
        for (j = tailleEau; j < taille - tailleEau; j++)  //Boucle qui parcourt les collones ou la glace peut etre pose
        {
            ajouteCaseGlace(banquise, i, j);              //Ajoute la glace (ligne i et colonne j) dans le tableau de glace de la banquise
        }
    }

    ajouteDepartArrive(banquise);                         //Ajoute la case d'arrivee et la case de depart
}



//Retourne un pointeur de type banquise initialise avec une taille en parametre
T_banquise *initBanquise(int tailleMatrice, int tailleEau)
{
    T_banquise *banquise = (T_banquise *)malloc(sizeof(T_banquise));     //Alloue de la memoire pour retourner un pointeur de type banquise

    banquise->matrice = initMatrice(tailleMatrice);                      //Initialise la matrice qui represente la banquise
    banquise->tailleN = tailleMatrice;                                   //Initialise la taille de la matrice selon les parametres de la fonction
    banquise->tailleEau = tailleEau;                                     //Initialise la taille de l'eau selon les parametres de la fonction
    banquise->depart.x = banquise->depart.y =
    banquise->arrive.x = banquise->arrive.y = 0;                         //Initialise les cases d'arrivee et de depart
    banquise->tabGlaces = initTabGlaces(tailleMatrice * tailleMatrice);  //Initialise le tableau de glaces
    banquise->nombreGlaces = 0;                                          //Initialise le nombre de glaces a 0

    remplitBanquise(banquise);

    return banquise;                                                     //Retourne le pointeur de type banquise
}



//Retourne une position dans la banquise ou la case est une case de type glace
T_point caseGlaceAleatoire(T_banquise *banquise, int choix)
{
    int tailleTabGlace = banquise->tailleN * banquise->tailleN,           //Recupere la taille du tableau de glaces
        tailleTabTemp = 0,                                                //Initialise la taille du tableau temporaire a 0
        i;                                                                //Valeur pour la boucle while
    T_point tabTemp[tailleTabGlace];                                      //Initialise un tableau temporaire de positions

    if (choix == 0)                                                       //Si le parametre choix est 0
    {
        for (i = 0; i < tailleTabGlace; i++)                              //Boucle qui parcourt le tableau de glaces
        {
            T_point glace = banquise->tabGlaces[i].position;              //Recupere la position de la glace parcourut par la boulce

            if (((glace.x) + 1) < banquise->tailleN
                && ((glace.x) - 1) >= 0
                && ((glace.y) + 1) < banquise->tailleN
                && ((glace.y) - 1) >= 0)
            {
                if (banquise->tabGlaces[i].estPresent == 1
                    &&(banquise->matrice[(glace.x) + 1][glace.y] == EAU
                    || banquise->matrice[(glace.x) - 1][glace.y] == EAU
                    || banquise->matrice[glace.x][(glace.y) + 1] == EAU
                    || banquise->matrice[glace.x][(glace.y) - 1] == EAU))     //Verifie que la glace est presente sur la banquise et qu'elle est entoure d'au moins une case d'eau
                {
                    tabTemp[tailleTabTemp] = glace;                           //Met dans le tableau temporaire la glace
                    tailleTabTemp++;                                          //Incremente la taille du tableau temporaire
                }
            }
        }
    }
    else                                                                  //Si le parametre choix est different de 0
    {
        int i = 0;                                                        //Initialise la variable i a 0

        while (tailleTabTemp != banquise->nombreGlaces)                   //Boucle tant que la taille du tableau temporaire est differente du nombre de glaces dans la banquise
        {
            if (banquise->tabGlaces[i].estPresent == 1)                   //Verifie si la glace est bien sur la banquise
            {
                tabTemp[tailleTabTemp] = banquise->tabGlaces[i].position; //Met dans le tableau temporaire la glace
                tailleTabTemp++;                                          //Incremente la taille du tableau temporaire
            }
            i++;                                                          //Incremente la valeur i qui parcourt le tableau de glaces de la banquise
        }
    }

    return tabTemp[rand() % tailleTabTemp];                               //Retourne une case de type glace aleatoire
}



//Fonction qui applique la fonte de la banquise avec une probabilite de 1 sur le parametre chanceFonte
void fonteBanquise(T_banquise *banquise, int chanceFonte)
{
    if (banquise->tailleEau != 0)                              //Verifie qu'il y a bien de l'eau autour de la banquise
    {
        if (rand() % chanceFonte == 0)                         //Verifie si le nombre a aleatoire est egal a 0
        {
            T_point glace = caseGlaceAleatoire(banquise, 0);   //Initialise une position aleatoire de glace qui touche une case d'eau

            enleveCaseGlace(banquise, glace.x, glace.y, EAU);  //Remplace la case glace aleatoire par une case d'eau
        }
    }
}
