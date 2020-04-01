#include "jeux.h"



//Retourne le type couleur qu'a choisi l'utilisateur
T_couleur choixCouleur()
{
    int couleur;                                          //Declare un entier qui correspond au choix de la couleur du joueur

    printf("\nChoisisez une couleur parmis : \n"
           "0 : Rouge\n"
           "1 : Vert\n"
           "2 : Bleu\n"
           "3 : Jaune\n");                                //Affiche le choix de couleur a l'utlisateur
    fflush(stdin);                                        //Vide le buffer
    scanf("%d", &couleur);                                //Prend l'entier saisi par l'utilisateur

    if (couleur < 0 || couleur > 3)                       //Verifie que l'entier est compris entre 0 et 3
    {
        while (couleur < 0 || couleur > 3)                //Boucle jusqu'a ce que l'entier soit compris entre 0 et 3
        {
            printf("\nValeur incorrect, reessayer : ");   //Redemande a l'utilisateur de saisir une valeur
            fflush(stdin);                                //Vide le buffer
            scanf("%d", &couleur);                        //Récupère l'entier saisie
        }
    }

    return couleur;                                       //Retourne la couleur choisie
}



//Fonction qui retourne un type joueur selon un numero qui va l'identifier
T_joueur *initJoueur(int numeroJoueur)
{
    T_joueur *joueur = (T_joueur *)malloc(sizeof(T_joueur));                         //Alloue de la mémoire au type joueur

    printf("Veuillez choisir un nom pour le joueur numero %d : ", numeroJoueur + 1); //Demande le nom au joueur
    fflush(stdin);                                                                   //Vide le buffer
    scanf("%s", joueur->nom);                                                        //Initialise le nom du joueur

    joueur->couleur = choixCouleur();                                                //Initialise la couleur de joueur
    joueur->identifiant = numeroJoueur;                                              //Initialise l'identifiant du joueur
    joueur->position.x = joueur->position.y = 0;                                     //Initialise la position du joueur
    joueur->vecteur.dx = joueur->vecteur.dy = 0;                                     //Initialise le veteur déplacement du joueur
    joueur->score = 1000;                                                            //Initialise le score du joueur
    joueur->etat = ENCOURS;                                                          //Initialise l'état du joueur
    joueur->nbMort = 0;                                                              //Initialise le nombre de mort

    return joueur;                                                                   //Retourne un pointeur de type joueur
}



//Retourne le nombre de joueurs selon le choix de l'utilisateur
int demandeNombreJoueurs()
{
    int nbJoueurs = 0;                                   //Variable pour le nombres de joueurs

    while (nbJoueurs < 1 || nbJoueurs > 4)               //Verifie que l'utilisateur rentre un chiffre entre 1 et 4
    {
        printf("Nombre de joueurs (entre 1 et 4) : ");   //Demande de rentrer un chiffre entre 1 et 4
        fflush(stdin);                                   //Vide le buffer
        scanf("%d", &nbJoueurs);                         //Récupère le chiffre rentré
        system("cls");                                   //Nettoie la console
    }

    return nbJoueurs;                                    //Retourne le nombre de joueurs
}



//Retourne un tableau de joueurs selon le nombre de joueurs en parametre
T_joueur **initTabJoueurs(T_banquise *banquise, int nombreJoueurs)
{
    T_joueur **joueurs = (T_joueur **)malloc(nombreJoueurs * sizeof(T_joueur *));  //Alloue de la mémoire pour le tableau de joueurs

    int i;                                                                         //Déclare un entier pour la boucle suivante

    for (i = 0; i < nombreJoueurs; i++)                                            //Boucle qui partcourt chaque joueurs
    {
        joueurs[i] = initJoueur(i);                                                //Ajoute le joueur numero i

        departJoueur(banquise, joueurs[i]);                                        //Met le joueur à sa case depart

        system("cls");                                                             //Nettoie la console
    }

    return joueurs;                                                                //Retourne le tableau de joueurs
}



//Fait apparaitre le joueur sur sa case de depart
void departJoueur(T_banquise *banquise, T_joueur *joueur)
{
    T_point pos;                                      //Declare la position du joueur
    T_point depart = banquise->depart;                //Recupere la position de la case de depart

    switch (joueur->identifiant)                      //Retourne la case de depart du joueur selon son identifiant
    {
    case 0:                                           //Joueur 0 a droite de la case de depart
        pos.x = depart.x,
        pos.y = depart.y + 1;
        break;
    case 1:                                           //Joueur 1 en bas de la case de depart
        pos.x = depart.x + 1,
        pos.y = depart.y;
        break;
    case 2:                                           //Joueur 2 en gauche de la case de depart
        pos.x = depart.x,
        pos.y = depart.y - 1;
        break;
    default:                                          //Joueur 3 en haut de la case de depart
        pos.x = depart.x - 1,
        pos.y = depart.y;
    }

    joueur->position = pos;                           //Change la position du joueur

    enleveCaseGlace(banquise, pos.x, pos.y, JOUEUR);  //Ajoute le joueur sur la banquise
}



//Retourne un entier en fonction du déplacement du joueur, et modifie la position de celui-ci
int verifieDeplacement(T_banquise *banquise, T_joueur *joueur, int caseX, int caseY, int caseValeur)
{
    switch (caseValeur)                                                                  //Retourne un entier selon la valeur de la case
    {
    case ERREUR:
        printf("\nDeplacement impossible : le joueur est en dehors des limites\n");                        //Préviens le joueur dans ce cas la
        return -1;                                                                                         //Retourne une valeur d'échec pour prévenir la fonction suivante
    case JOUEUR:
        printf("\nDeplacement impossible : un autre joueur occupe deja la case\n");                        //Préviens le joueur dans ce cas la
        return -1;                                                                                         //Retourne une valeur d'échec pour prévenir la fonction suivante
    case DEPART:
        printf("\nDeplacement impossible : le joueur ne peut pas aller au depart\n");                      //Préviens le joueur dans ce cas la
        return -1;                                                                                         //Retourne une valeur d'échec pour prévenir la fonction suivante
    case ROCHER:
        printf("\nDeplacement impossible : le joueur ne peut pas aller sur un rocher\n");                  //Préviens le joueur dans ce cas la
        return -1;                                                                                         //Retourne une valeur d'échec pour prévenir la fonction suivante
    case RESSORT:
        printf("\nDeplacement impossible : le joueur ne peut pas interagir avec un ressort\n");            //Préviens le joueur dans ce cas la
        return -1;                                                                                         //Retourne une valeur d'échec pour prévenir la fonction suivante
    case MARTEAU_TETE :
        printf("\nDeplacement impossible : le joueur ne peut pas interagir avec la tete d'un marteau\n");  //Préviens le joueur dans ce cas la
        return -1;                                                                                         //Retourne une valeur d'échec pour prévenir la fonction suivante
    case MARTEAU_CENTRE :
        printf("\nDeplacement impossible : le joueur ne peut pas interagir avec un marteau\n");            //Préviens le joueur dans ce cas la
        return -1;                                                                                         //Retourne une valeur d'échec pour prévenir la fonction suivante
    case GLACON:
        printf("\nDeplacement d'un glacon\n");                                                             //Préviens le joueur dans ce cas la
        return -2;                                                                                         //Retourne une valeur pour prévenir la fonction suivante
    case EAU:
        tuerJoueur(joueur, banquise);
        return 0;                                                                                          //Retourne une valeur pour prévenir la fonction suivante
    default :
        joueur->position.x = caseX;                                                                        //Affectation de sa nouvelle position
        joueur->position.y = caseY;
        return 0;                                                                                          //Retourne une valeur de succès pour la fonction suivante
    }
}


//Fonction qui s'occupe du déplacement du personnage en fonction de ses paramètres, et renvoie un entier en fonction du déplacement
int deplacementJoueur_bis(T_banquise *banquise, T_joueur *joueur, char deplacement)
{
    int jx = joueur->position.x,                                     //Récupère la position du joueur
        jy = joueur->position.y,
        x, y,                                                        //Variable pour simuler le deplacement du joueur
        taille = banquise->tailleN,                                  //Récupère la taille de la banquise
        caseValeur;                                                  //Variable qui récupère la valeur de la case ou le joueur va aller

    switch (deplacement)                                             //Effectue le décalage selon la touche mis en paramètre et change le vecteur du joueur (utile pour la collision avec un glacon immobile)
    {
    case 'z' :
    case 'Z' :
        joueur->vecteur.dx = -1;
        joueur->vecteur.dy = 0;
        break;
    case 'q' :
    case 'Q' :
        joueur->vecteur.dx = 0;
        joueur->vecteur.dy = -1;
        break;
    case 's' :
    case 'S' :
        joueur->vecteur.dx = 1;
        joueur->vecteur.dy = 0;
        break;
    case 'd' :
    default :
        joueur->vecteur.dx = 0;
        joueur->vecteur.dy = 1;
    }


    x = jx + joueur->vecteur.dx;                                     //Simule la nouvelle position du joueur
    y = jy + joueur->vecteur.dy;

    if (x >= 0 && x < taille && y >= 0 && y < taille)                //Vérifie si le joueur ne sort pas de la matrice
    {
        caseValeur = banquise->matrice[x][y];                        //Affecte la valeur de la case ou le joueur va
    }
    else                                                             //Si le joueur sort de la matrice
    {
        caseValeur = ERREUR;                                         //Affecte une valeur de case d'erreur
    }

    return verifieDeplacement(banquise, joueur, x, y, caseValeur);   //Retourne la valeur de la fonction qui verifie la case ou le joueur va aller
}



//Fonction qui permet le déplacement du personnage
int deplacementJoueur(T_banquise *banquise, T_joueur *joueur, char clavier)
{
    int correct = deplacementJoueur_bis(banquise, joueur, clavier);  //Stocke la valeur de la fonction précédente

    while (correct == -1)                                            //Tant que la valeur est mauvaise
    {
        clavier = saisieTouche(joueur);                              //On re-récupère la bonne touche saisie par le joueur
        correct = deplacementJoueur_bis(banquise, joueur, clavier);  //On re-stocke la valeur de la fonction précédente
    }

    if (correct == -2)                                               //Verifie si le joueur pousse un glacon
    {
        joueur->score += 100;                                        //Incrémente le score du joueur
        return GLACON;                                               //Retourne la valeur qui correspond au glacon
    }
    else                                                             //Si le joueur va vers une case de glace
    {
        joueur->score -= 10;                                         //Décrémente le score du joueur
        return GLACE;                                                //Retourne la valeur qui correspond à la glace
    }
}



//Cherche un joueur en fonction d'une position en paramètre
T_joueur *joueurSelonPosition(T_joueur **joueurs, int posX, int posY, int nbJoueurs)
{
    T_joueur *joueur = joueurs[0];              //Variable pour retourner le joueur
    int i;                                      //Variable pour la boucle suivante

    for(i = 0; i < nbJoueurs; i++)              //Regarde chaque joueur du tableau
    {
        joueur = joueurs[i];

        if (posX == joueur->position.x
            && posY == joueur->position.y)      //Condition qui regarde si le position en paramètre correspond à celle du joueur
        {
            break;                              //Sort de la boucle
        }
    }

    return joueur;                              //Retourne le joueur
}



//Fonction qui s'occupe de tuer le joueur et de le ramener au point de depart
void tuerJoueur(T_joueur *joueur, T_banquise *banquise)
{
    int posx = joueur->position.x, posy = joueur->position.y;  //Enregistre la position du joueur dans 2 varibles

    printf("\nLe joueur ");                                    //Affichage du message de mort du joueur
    changeCouleurTexte(joueur->couleur);
    printf("%s ", joueur->nom);
    changeCouleurTexte(BLANC);
    printf("est mort !\n");
    Sleep(2000);                                               //Attend 2 secondes pour laisser le temps au joueur de lire le message

    joueur->score -= 150;                                      //Enlève des points au joueur qui meurt
    joueur->nbMort += 1;                                       //Ajoute 1 au nombre de mort du joueur

    ajouteCaseGlace(banquise, posx, posy);                     //Ajoute une case GLACE sur la position où le joueur est mort
    departJoueur(banquise, joueur);                            //Fait reapparaitre le joueur sur sa case de départ
}