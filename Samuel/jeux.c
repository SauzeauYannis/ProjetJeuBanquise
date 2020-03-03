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

    while (nbJoueurs != 1 && nbJoueurs != 2 && nbJoueurs != 3 && nbJoueurs != 4)             //Verifie que l'utilisateur rentre un chiffre entre 1 et 4
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
int tourJoueur(T_jeu *jeu, int numJoueur)
{
    int caseValeur;
    int **tab = jeu->banquise->tab;
    system("cls");                                                                           //efface le terminal
    printf("Tour %d\n", jeu->nombreTour);
    afficheJeu(jeu);                                                                         //Affiche la banquise dans le terminal
    rafraicheBanquise(jeu, jeu->joueurs[numJoueur], 0);                                      //Met un zero sur la futur ancienne case du joueur sur la banquise
    deplacementJoueur(jeu->joueurs[numJoueur], jeu->banquise->tailleN, tab);                 //Effectue le déplacement du joueur sur la banquise
    caseValeur = tab[jeu->joueurs[numJoueur]->position.x][jeu->joueurs[numJoueur]->position.y];
    printf("\n");
    rafraicheBanquise(jeu, jeu->joueurs[numJoueur], 1);                                      // Met un 1 sur la nouvelle case du joueur sur la banquise
    return caseValeur;
}



//Ressort un entier qui détermine si la partie est finie ou non
int victoire(T_jeu *jeu, int caseVal, int i)
{
    if (caseVal == 3)                                                              //Valeur de l'entier correspondant à l'arrivée
    {
        jeu->joueurs[i]->etat = 1;                                                 //Change l'etat de ce joueur pour le designer en tant que gagnant
        printf("La partie est finie ! %s est victorieux !", jeu->joueurs[i]->nom);  //Affiche que la partie est finie, ainsi que le nom du gagnant
        Sleep(3000);                                                               //Attend 3s avant de passer à l'instruction suivante
        return 1;                                                                  //Retourne l'entier 1 pour signaler une victoire
    }
    else
    {
        return 0;                                                                  //Retourne l'entier 0 pour signaler que la partie continue
    }
}



//Affiche le scrore à la fin de la partie
void afficheScore(T_jeu *jeu)
{
    system("cls");                                           //Efface le terminal
    printf("Score de la partie : \n\n");
    for(int i = 0; i<jeu->nombreJoueur; i++)                 //Permet d'afficher le score de chaque joueur
    {
        printf("->Joueur %d\n", i+1);
        printf("    Nom : %s\n", jeu->joueurs[i]->nom);
        printf("    Score : %d\n", jeu->joueurs[i]->score);
        if (jeu->joueurs[i]->etat == 1)                      //Permet de savoir si le joueur est gagnant ou perdant
        {
            printf("    Etat : GAGNANT\n");
        }
        else
        {
            printf("    Etat : PERDANT\n");
        }
        printf("\n");
    }
}



//Fonction qui joue un niveau sélectionné jusqu'à la victoire d'un joueur
void joueNiveau(T_jeu *jeu)
{
    jeu->nombreTour = 1;
    int caseVal, finPartie = 0; //caseVal sert à connaitre la valeur de la case, et finPartie sert à mettre fin à la partie en cours

    T_glacon *glacon = initGlacon(5,0);
    glacon->vecteur.dy = 1, glacon->vecteur.dx = 0;
    ajouteGlacon(jeu, glacon);

    while(finPartie == 0)
    {
        for(int i = 0; i<jeu->nombreJoueur; i++)    //Boucle for qui permet à chaque joueur de jouer pour un tour
        {
            caseVal = tourJoueur(jeu, i);           //Tour du joueur i
            finPartie = victoire(jeu, caseVal, i);  //Donne un entier si la partie est gagnée, ou si elle continue
            if (caseVal == 3)                       //Permet de réellement stopper le jeu, pour ainsi éviter les joueurs suivant de jouer
                break;                              //Brise la boucle for
        }
        deplacementGlacon(jeu, glacon);
        jeu->nombreTour += 1;
    }
    afficheScore(jeu);  //Affiche le score du jeu
    Sleep(5000);        //Donne 5s au joueur pour lire les scores
    system("cls");
    printf("Merci d'avoir joue !\n");
}



//Fonction qui renvoie un entier qui permet de rejouer une partie
int rejouer()
{
    char c;  //Enregistre la valeur saisie par l'utilisateur
    printf("\nVoulez vous rejouer ? (Tapez \"y\" pour oui ou \"n\" pour non) : "); //Permet au joueur de relancer une partie
    c = getchar();
    c = getchar();

    while (c != 'n' && c != 'y')
    {
        printf("\nChoix inconnue ! Veuillez reessayer : ");
        c = getchar();
    }

    if (c == 'y')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}



//Ajoute un glaçon sur la banquise
void ajouteGlacon(T_jeu *jeu, T_glacon *glacon)
{
    int posx = glacon->position.x, posy = glacon->position.y;  //Variable qui enregistre la position du glaçon
    modifieCaseBanquise(jeu->banquise, posx, posy, 4);         //Ajoute le glaçon sur la banquise
}


//Actualise la postion d'un glaçon sur la banquise à chaque tour
void deplacementGlacon(T_jeu *jeu, T_glacon *glacon)
{
    int posx = glacon->position.x, posy = glacon->position.y;                  //Variables qui enregistrent la position du glaçon
    int dx = glacon->vecteur.dx, dy = glacon->vecteur.dy;                      //Variables qui enregistrent le vecteur du glacon
    int verif = verifieDeplacementGlacon(posx+dx, posy+dy, jeu->banquise->tab[posx][posy],jeu->banquise->tailleN);

    if(verif  < 0)
    {
        glacon->position.x += dx, glacon->position.y += dy;                             //Modifie la position du glacon en fonction de son vecteur
        modifieCaseBanquise(jeu->banquise, posx, posy, 0);                              //Modifie la valeur de l'ancienne position du glaçon sur la banquise
        modifieCaseBanquise(jeu->banquise, glacon->position.x, glacon->position.y, 4);  //Modifie la valeur de l'ancienne position du glaçon sur la banquise
    }
    else
    {
        glacon->vecteur.dx = glacon->vecteur.dy = 0;
    }
}
