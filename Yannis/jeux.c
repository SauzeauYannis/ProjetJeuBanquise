#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "jeux.h"

//Affiche le Menu du jeu
void afficheMenu()
{
    printf("Jeu de la banquise\n"
           "\n"
           "Nombre de joueurs : 1-4 joueurs\n"
           "\n"
           "Creer par :\n"
           "Samuel GOUBEAU\n"
           "Yannis SAUZEAU\n"
           "\n"
           "Bonne chance !\n"
           "\n"
           "Appuyer sur entree pour continuer");  //Affiche le Menu

    char entree;                                  //Stocke un caractere
    entree = getchar();                           //Attend que la touche entree soit pressee

    system("cls");                                //Nettoie l'ecran

    printf("Regles du jeux\n"
           "\n"
           "A venir\n"
           "\n"
           "Appuyer sur entree pour continuer");  //Affiche les regles du jeu

    entree = getchar();                           //Attend que la touche entree soit pressee

    system("cls");                                //Nettoie l'ecran

    printf("Controle\n"
           "\n"
           "Pour se deplacer, utiliser les "
           "touches du clavier suivante :\n"
           "Z : haut\n"
           "Q : gauche\n"
           "S : bas\n"
           "D : droite\n"
           "\n"
           "Appuyer sur entree pour commencer le jeu"); //Affiche les controles

    entree = getchar();                          //Attend que la touche entree soit pressee

    system("cls");                               //Nettoie l'ecran
}

//Change la couleur du texte selon la type couleur mis en parametre
void changeCouleurTexte(T_couleur couleur)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); //Declare la console windows du jeu

    switch (couleur)                                  //Change la couleur du texte de la console selon le type couleur mis en parametre
    {
    case 0 :
        SetConsoleTextAttribute(console, 12);
        break;
    case 1 :
        SetConsoleTextAttribute(console, 2);
        break;
    case 2 :
        SetConsoleTextAttribute(console, 9);
        break;
    case 3 :
        SetConsoleTextAttribute(console, 14);
        break;
    case 4 :
        SetConsoleTextAttribute(console, 11);
        break;
    case 5 :
        SetConsoleTextAttribute(console, 13);
        break;
    default :
        SetConsoleTextAttribute(console, 15);
    }
}

//Ajoute entre 1 et 4 joueurs au jeu
void ajouteJoueurs(T_jeu *jeu)
{
    int nbJoueurs = 0;                                 //Declare le nombre de joueurs

    while (nbJoueurs < 1 || nbJoueurs > 4)             //Verifie que l'utilisateur rentre un chiffre entre 1 et 4
    {
        printf("Nombre de joueurs (entre 1 et 4) : "); //Demande de rentrer un chiffre
        scanf("%d", &nbJoueurs);                       //Recupere le chiffre rentre
        system("cls");                                 //Nettoie la console
    }

    int i;                                             //Declare un entier pour la boucle

    for (i = 0; i < nbJoueurs; i++)                    //Rentre dans la boucle autant de fois qu'il y a de joueurs
    {
        jeu->joueurs[i] = (T_joueur *)realloc(jeu->joueurs[i], sizeof(T_joueur));                         //Re-alloue de la memoire pour le joueur
        jeu->joueurs[i] = initJoueur(i);                                                                  //Ajoute un joueur
        jeu->nombreJoueur++;                                                                              //Rajoute 1 au nombres de joueurs

        modifieCaseBanquise(jeu->banquise, jeu->joueurs[i]->position.x, jeu->joueurs[i]->position.y, 1);  //Ajoute le joueur sur la banquise

        system("cls");                                 //Nettoie la console
    }
}

//Retourne un pointeur de type jeu en fonction du niveau et de la taille de la banquise
T_jeu *initJeux(int niveau, int taille)
{
    T_jeu *jeu = (T_jeu *)malloc(sizeof(T_jeu));               //Aloue de l'espace memoire a un pointeur de type jeu

    jeu->banquise = initBanquise(taille);                      //Initialise la banquise dans le jeu
    jeu->joueurs = (T_joueur **)malloc(sizeof(T_joueur *));    //Aloue de la memoire pour creer un tableau de pointeur de joueur
    jeu->nombreJoueur = 0;                                     //Initialise le nombre de joueur
    jeu->nombreTour = 0;                                       //Initialise le nombre de tour
    jeu->IdJeu = niveau;                                       //Initialise le niveau

    remplitBanquise(jeu->banquise, 0);                         //Remplit la banquise de 0
    ajouteDepartArrive(jeu->banquise);                         //Ajoute les cases de depart et d'arrive
    ajouteJoueurs(jeu);                                        //Ajoute les joueurs

    return jeu;                                                //Retourne le pointeur de type jeu
}
/*
void joueTour(T_jeu *jeu, T_joueur *joueur)
{

}
*/

//Affiche le jeu avec les joueurs en couleur
void afficheJeu(T_jeu *jeu)
{
    int taille = jeu->banquise->tailleN;        //Recupere la taille de la banquise
    int i, j;                                   //Declare deux entier pour les boucles for

    for (i = 0; i < taille; i++)                //Boucle qui parcourt les lignes de la matrice
    {
        printf("| ");                           //Esthetique
        for (j = 0; j < taille; j++)            //Boucle qui parcourt les collones de la matrice
        {
            int pos = jeu->banquise->tab[i][j]; //Declare la position parcouru
            int k;                              //Declare un entier pour une boucle

            switch (pos)
            {
            case 1 :
                for (k = 0; k < jeu->nombreJoueur; k++) //Parcourt les joueurs present
                {
                    T_joueur *joueur = jeu->joueurs[k]; //Declare le joueur parcouru

                    if (joueur->position.x == i && joueur->position.y == j)  //Verifie si la case parcouru est celle du joueur parcouru
                    {
                        changeCouleurTexte(joueur->couleur);                 //Change la couleur du texte selon celle du joueur
                        printf("%d ", pos);                                  //Affiche le joueur avec sa couleur
                        changeCouleurTexte(ERREUR);                          //Remet la couleur en blanc
                    }
                }
                break;
            case 2 :
                changeCouleurTexte(TURQUOISE);  //Change la couleur en turquoise pour le depart
                printf("%d ", pos);             //Affiche la case de depart
                changeCouleurTexte(ERREUR);     //Remet la couleur initiale
                break;
            case 3 :
                changeCouleurTexte(ROSE);       //Change la couleur en rose pour l'arrive
                printf("%d ", pos);             //Affiche la case d'arrive
                changeCouleurTexte(ERREUR);     //Remet la couleur initiale
                break;
            default :
                printf("%d ", pos);             //Affiche la case de la matrice qui se trouve a la ligne i et la colonne j
            }
        }
        printf("|\n");                          //Esthetique
    }
}

//Fonction qui change la valeur de la banquise en fonction de la position du joueur et d'une valeur
void rafraicheBanquise(T_jeu *jeu, T_joueur *joueur, int val)
{
    int posx = joueur->position.x, posy = joueur->position.y;  //Variables contenant la position du joueur
    modifieCaseBanquise(jeu->banquise, posx, posy, val);       //Changement de la valeur sur la banquise
}

//Fonction qui s'occupe d'effectuer le tour d'un joueur
void tourJoueur(T_jeu *jeu, int numJoueur)
{
    printf("Tour %d\n", jeu->nombreTour);
    afficheJeu(jeu);                                                                         //Affiche la banquise dans le terminal
    rafraicheBanquise(jeu, jeu->joueurs[numJoueur], 0);                                      //Met un zero sur la futur ancienne case du joueur sur la banquise
    deplacementJoueur(jeu->joueurs[numJoueur], jeu->banquise->tailleN, jeu->banquise->tab);  //Effectue le d�placement du joueur sur la banquise
    printf("\n");
    rafraicheBanquise(jeu, jeu->joueurs[numJoueur], 1);                                      // Met un 1 sur la nouvelle case du joueur sur la banquise
    system("cls");                                                                           //efface le terminal
}

//Fonction qui joue un niveau s�lectionn� jusqu'� la victoire d'un joueur
void joueNiveau(T_jeu *jeu)
{
    jeu->nombreTour = 1;

    while(1)
    {
        for(int i = 0; i<jeu->nombreJoueur; i++)  //Boucle for qui permet � chaque joueur de jouer pour un tour
        {
            tourJoueur(jeu, i);                   //Tour du joueur i
        }
        jeu->nombreTour += 1;
    }
}
