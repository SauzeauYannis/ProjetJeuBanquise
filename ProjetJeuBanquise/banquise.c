#include "jeux.h"



//Aloue de la memoire pour une matrice carrée d'entier selon la taille mise en paramètre
int **initMatrice(int tailleMatrice)
{
    int **matrice;                                                  //Declare la matrice qui va representer la banquise

    matrice = (int **)malloc(tailleMatrice * sizeof(int *));        //Alloue de la memoire aux lignes de la matrice

    int i;                                                          //Declare un entier pour une boucle for

    for (i = 0; i < tailleMatrice; i++)                             //Boucle qui parcourt les colonnes de la matrice
    {
        matrice[i] = (int *)malloc(tailleMatrice * sizeof(int));    //Alloue de la memoire aux colonnes de la matrice
    }

    return matrice;                                                 //Retourne la matrice initialisé
}



//Initialise un tableau de glaces de taille donnée en paramètre
T_glace *initTabGlaces(int taille)
{
    T_glace *tabGlaces = (T_glace *)malloc(taille * sizeof(T_glace));  //Aloue de la memoire pour le tableau

    int i;                                                             //Variable pour la boucle

    for (i = 0; i < taille; i++)                                       //Boucle qui parcourt le tableau de glaces
    {
        tabGlaces[i].estPresent = FAUX;                                //Initialise la valeur pour dire qu'il n'y a pas de glace a la position qui suit
        tabGlaces[i].position.x = tabGlaces[i].position.y = 0;         //Initialise la position de la glace
    }

    return tabGlaces;                                                  //Retourne le tableau de glace initialise
}



//Change une case de la banquise selon la valeur indiquee a l'emplacement donné
void modifieCaseBanquise(T_banquise *banquise, int caseX, int caseY, T_case valeur)
{
    banquise->matrice[caseX][caseY] = valeur;  //Met la valeur dans la banquise a l'emplcamenent donné en paramètre
}



//Ajoute une case glace dans le tableau de glaces de la banquise, selon l'emplacement donné en paramètre
void ajouteCaseGlace(T_banquise *banquise, int caseX, int caseY)
{
    T_point positionGlace;                                     //Variable point pour la position de la glace à ajouter
    T_glace *glaces = banquise->tabGlaces;                     //Variable qui stocke le tableau de glaces sur la banquise
    int tailleMax = (banquise->tailleN * banquise->tailleN),   //Variable qui stocke la taille maximale du tableau de glaces
        i;                                                     //Variable pour la boucle

    positionGlace.x = caseX, positionGlace.y = caseY;          //Initialise la position de la glace selon les valeurs données en paramètre

    for (i = 0; i < tailleMax; i++)                            //Boucle qui parcourt le tableau de glaces
    {
        if (glaces[i].estPresent == FAUX)                      //Verifie qu'une case du tableau peut prendre une glace
        {
            glaces[i].estPresent = VRAI;                       //Dis qu'il y a une glace dans le tableau
            glaces[i].position = positionGlace;                //Met la glace dans le tableau
            break;                                             //Sort de la boucle
        }
    }

    modifieCaseBanquise(banquise, caseX, caseY, GLACE);        //Met la glace sur la banquise
    banquise->nombreGlaces++;                                  //Incremente le nombre de glace
}



//Enlève une glace du tableau de glace selon sa position et remplace la glace par une autre valeur de case
void enleveCaseGlace(T_banquise *banquise, int caseX, int caseY, T_case valeur)
{
    T_glace *glaces = banquise->tabGlaces;                     //Variable qui stocke le tableau de glaces sur la banquise
    int tailleMax = (banquise->tailleN * banquise->tailleN),   //Variable qui stocke la taille maximale du tableau de glaces
        i;                                                     //Variable pour la boucle

    for (i = 0; i < tailleMax; i++)                            //Boucle qui parcourt le tableau de glace
    {
        if (glaces[i].position.x == caseX &&
            glaces[i].position.y == caseY &&
            glaces[i].estPresent == VRAI)                      //Verifie que la glace est bien a la bonne position et presente dans le jeu
        {
            glaces[i].estPresent = FAUX;                       //Dis qu'il n'y a plus de glace a cette position
            break;                                             //Sort de la boucle
        }
    }

    modifieCaseBanquise(banquise, caseX, caseY, valeur);       //Change l'ancienne glace avec la valeur mise paramètre
    banquise->nombreGlaces--;                                  //Décrémente le nombre de glaces
}



//Change la matrice de la banquise en y ajoutant les cases d'arrive et de depart
void ajouteDepartArrive(T_banquise *banquise)
{
    int taille = banquise->tailleN,                                                          //Récupère la taille de la banquise
        tailleEau = banquise->tailleEau;                                                     //Récupère la taille de l'eau autour de la banquise

    banquise->depart.x = 1 + tailleEau + (rand() % (taille - 2 - (tailleEau + tailleEau)));  //Génère aléatoirement la case de départ
    banquise->depart.y = 1 + tailleEau;

    banquise->arrive.x = tailleEau + (rand() % (taille - 1 -(tailleEau + tailleEau)));       //Génère aléatoirement la case d'arrivé
    banquise->arrive.y = taille - 1 - tailleEau;

    enleveCaseGlace(banquise, banquise->depart.x, banquise->depart.y, DEPART);               //Modifie la case de départ
    enleveCaseGlace(banquise, banquise->arrive.x, banquise->arrive.y, ARRIVE);               //Modifie la case d'arrivé
}



//Remplit la banquise avec de l'eau, de la glace et les cases d'arrivé et de départ
void remplitBanquise(T_banquise *banquise)
{
    int taille = banquise->tailleN,                       //Récupère la taille de la banquise
        tailleEau = banquise->tailleEau,                  //Récupère la taille de l'eau qui entoure la banquise
        i, j;                                             //Déclare deux entiers pour les boucles for

    for (i = 0; i < taille; i++)                          //Boucle qui parcourt les lignes de la matrice
    {
        for (j = 0; j < taille; j++)                      //Boucle qui parcourt les colonnes de la matrice
        {
            modifieCaseBanquise(banquise, i, j, EAU);     //Met de l'eau à la case de ligne i et de colonne j
        }
    }

    for (i = tailleEau; i < taille - tailleEau; i++)      //Boucle qui parcourt les lignes où la glace peut être posé
    {
        for (j = tailleEau; j < taille - tailleEau; j++)  //Boucle qui parcourt les colonnes où la glace peut être posé
        {
            ajouteCaseGlace(banquise, i, j);              //Ajoute la glace (ligne i et colonne j) dans le tableau de glace de la banquise
        }
    }

    ajouteDepartArrive(banquise);                         //Ajoute la case d'arrivée et la case de départ
}



//Retourne un pointeur de type banquise initialise avec une taille en paramètre
T_banquise *initBanquise(int tailleMatrice, int tailleEau)
{
    T_banquise *banquise = (T_banquise *)malloc(sizeof(T_banquise));     //Alloue de la memoire pour retourner un pointeur de type banquise

    banquise->matrice = (T_case **)initMatrice(tailleMatrice);           //Initialise la matrice qui représente la banquise
    banquise->tailleN = tailleMatrice;                                   //Initialise la taille de la matrice selon les paramètres
    banquise->tailleEau = tailleEau;                                     //Initialise la taille de l'eau selon les paramètres
    banquise->depart.x = banquise->depart.y =
    banquise->arrive.x = banquise->arrive.y = 0;                         //Initialise les cases d'arrivée et de départ
    banquise->tabGlaces = initTabGlaces(tailleMatrice * tailleMatrice);  //Initialise le tableau de glaces
    banquise->nombreGlaces = 0;                                          //Initialise le nombre de glaces a 0

    remplitBanquise(banquise);                                           //Remplit la banquise

    return banquise;                                                     //Retourne un pointeur de type banquise
}



//Retourne une position dans la banquise où la case est une case de type glace et autour de l'eau si partout est égal à FAUX
T_point caseGlaceAleatoire(T_banquise *banquise, T_booleen partout)
{
    int tailleTabGlace = banquise->tailleN * banquise->tailleN,    //Récupère la taille du tableau de glaces
        tailleTabTemp = 0,                                         //Initialise la taille du tableau temporaire a 0
        i;                                                         //Valeur pour la boucle while
    T_point tabTemp[tailleTabGlace];                               //Initialise un tableau temporaire de positions

    if (partout == FAUX)                                           //Si le parametre partout est égal à FAUX
    {
        T_point glacePos;                                          //Variable qui va stocker la position de la glace
        int gX, gY;                                                //Variable pour les coordonnées en x et en y de la glace

        for (i = 0; i < tailleTabGlace; i++)                       //Boucle qui parcourt le tableau de glaces
        {
            glacePos = banquise->tabGlaces[i].position;            //Récupère la position de la glace parcourut par la boucle
            gX = glacePos.x, gY = glacePos.y;                      //Initialise les coordonnées

            if ((gX + 1) < banquise->tailleN &&
                (gX - 1) >= 0 &&
                (gY + 1) < banquise->tailleN &&
                (gY - 1) >= 0)                                     //Vérifie que la boucle suivante puisse fonctionner
            {
                if (banquise->tabGlaces[i].estPresent == VRAI && (
                    banquise->matrice[gX + 1][gY] == EAU ||
                    banquise->matrice[gX - 1][gY] == EAU ||
                    banquise->matrice[gX][gY + 1] == EAU ||
                    banquise->matrice[gX][gY - 1] == EAU))         //Verifie que la glace est présente sur la banquise et qu'elle est entourée d'au moins une case d'eau
                {
                    tabTemp[tailleTabTemp] = glacePos;             //Met dans le tableau temporaire la glace
                    tailleTabTemp++;                               //Incrémente la taille du tableau temporaire
                }
            }
        }
    }
    else                                                           //Si le parametre partout est différent de FAUX
    {
        T_glace glace;                                             //Variable qui va stocker les glaces
        i = 0;                                                     //Initialise la variable i à 0

        while (tailleTabTemp != banquise->nombreGlaces)            //Boucle tant que la taille du tableau temporaire est différente du nombre de glaces dans la banquise
        {
            glace = banquise->tabGlaces[i];                        //Récupère la glace parcourue

            if (glace.estPresent == VRAI)                          //Verifie si la glace est bien sur la banquise
            {
                tabTemp[tailleTabTemp] = glace.position;           //Met dans le tableau temporaire la glace
                tailleTabTemp++;                                   //Incrémente la taille du tableau temporaire
            }
            i++;                                                   //Incrémente la valeur i qui parcourt le tableau de glaces de la banquise
        }
    }

    return tabTemp[rand() % tailleTabTemp];                        //Retourne une case de type glace aléatoire
}



//Fonction qui applique la fonte de la banquise avec une probabilite de 1 sur le paramètre chanceFonte
void fonteBanquise(T_banquise *banquise, int chanceFonte)
{
    if (banquise->tailleEau != 0)                                //Verifie qu'il y a bien de l'eau autour de la banquise
    {
        if (rand() % chanceFonte == 0)                           //Verifie si le nombre aléatoire est égal à 0
        {
            T_point glace = caseGlaceAleatoire(banquise, FAUX);  //Initialise une position aléatoire de glace qui touche une case d'eau

            enleveCaseGlace(banquise, glace.x, glace.y, EAU);    //Remplace la case glace aléatoire par une case d'eau
        }
    }
}
