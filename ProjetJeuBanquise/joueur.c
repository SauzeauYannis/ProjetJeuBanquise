#include <stdio.h>
#include <stdlib.h>
#include "jeux.h"

//Retourne le type couleur qu'a choisi l'utilisateur
T_couleur choixCouleur()
{
    int couleur = -1;                                     //Declare un entier

    printf("\nChoisisez une couleur parmis : \n"
           "0 : Rouge\n"
           "1 : Vert\n"
           "2 : Bleu\n"
           "3 : Jaune\n");                                //Affiche le choix de couleur a l'utlisateur

    scanf("%d", &couleur);                                //Prend l'entier saisi par l'utilisateur

    if (couleur < 0 || couleur > 3)                       //Verifie que l'entier est compris entre 0 et 3
    {
        while (couleur < 0 || couleur > 3)                //Boucle jusqu'a ce que l'entier soit compris entre 0 et 3
        {
            printf("\nValeur incorrect, reessayer : ");   //Redemande a l'utilisateur de saisir une valeur
            scanf("%d", &couleur);                        //Recupere l'entier saisie
        }
    }

    switch (couleur)                                      //Transforme un entier en un type couleur pour le retourner
    {
    case 0 :
        return ROUGE;
        break;
    case 1 :
        return VERT;
        break;
    case 2 :
        return BLEU;
        break;
    case 3 :
        return JAUNE;
        break;
    default :
        return BLANC;
    }
}



//Fonction qui retourne un type joueur selon un numero qui va l'identifier
T_joueur *initJoueur(int numeroJoueur)
{
    T_joueur *joueur = (T_joueur *)malloc(sizeof(T_joueur));  //Alloue de la memoire au type joueur

    printf("Veuillez choisir un nom pour le joueur numero %d : ", numeroJoueur + 1); //Demande le nom au joueur
    scanf("%s", joueur->nom);                                                        //Initialise le nom du joueur

    joueur->couleur = choixCouleur();             //Initialise la couleur de joueur
    joueur->identifiant = numeroJoueur;           //Initialise l'identifiant du joueur
    joueur->position.x = joueur->position.y = 0;  //Initialise la position du joueur
    joueur->vecteur.dx = joueur->vecteur.dy = 0;  //Initialise le veteur deplacement du joueur
    joueur->score = 0;
    joueur->etat = 0;                             //Initialise l'etat du joueur

    return joueur;                                //Retourne un pointeur de type joueur
}

void spawnJoueur(T_banquise *banquise, T_joueur *joueur)
{
    T_point pos;                            //Declare un type point
    T_point depart = banquise->depart;

    switch (joueur->identifiant)
    {
    case 0:
        pos.x = depart.x;
        pos.y = depart.y + 1;
        break;
    case 1:
        pos.x = depart.x + 1;
        pos.y = depart.y;
        break;
    case 2:
        pos.x = depart.x;
        pos.y = depart.y - 1;
        break;
    default:
        pos.x = depart.x - 1;
        pos.y = depart.y;
    }

    joueur->position = pos;

    enleveCaseGlace(banquise, pos.x, pos.y, JOUEUR);  //Ajoute le joueur sur la banquise
}



//Retourne une lettre du clavier qui correspond a un deplacement
char saisieDeplacement(T_joueur *joueur)
{
    char clavier = getchar();               //Declare un caractere et l'initialise pour eviter un bug que nous comprenons pas

    changeCouleurTexte(joueur->couleur);    //Change la couleur selon la couleur choisi par le joueur
    printf("%s", joueur->nom);              //Affiche le nom du joueur choisi
    changeCouleurTexte(BLANC);              //Remet la couleur blanche
    printf(" deplacez vous : ");            //Demande au joueur ou il veut se deplacer
    scanf("%c", &clavier);                  //Recupere la touche qui a ete frappe

    while (clavier != 'z' && clavier != 'q' && clavier != 's' && clavier != 'd')           //Boucle qui fini quand l'utilisateur a rentree une bonne touche
    {
        printf("\r\nTouche incorrect, veuillez saisir une touche entre \"z, q, s, d\" : ");  //Re-demande le deplacement en rappellant les bonnes touches
        scanf("%c", &clavier);                                                             //Recupere la touche qui a ete frappe
    }

    return clavier;                              //Retourne la bonne touche
}



//Retourne un entier en fonction du deplacement du joueur, et modifie la position de celui-ci
int verifieDeplacement(T_banquise *banquise, T_joueur *joueur, int caseX, int caseY, int caseValeur, int taille)
{
    switch (caseValeur)
    {
    case -1:
        printf("\nDeplacement impossible : le joueur est en dehors des limites\n"); //Previens le joueur dans ce cas la
        return -1;                                                                  //Retourne une valeur d'echec pour prevenir la fonction suivante
        break;
    case JOUEUR:
        printf("\nDeplacement impossible : un autre joueur occupe deja la case\n"); //Previens le joueur dans ce cas la
        return -1;                                                                  //Retourne une valeur d'echec pour prevenir la fonction suivante
        break;
    case DEPART:
        printf("\nDeplacement impossible : le joueur ne peut pas aller sur le spawn\n"); //Previens le joueur dans ce cas la
        return -1;                                                                       //Retourne une valeur d'echec pour prevenir la fonction suivante
        break;
    case GLACON:
        printf("\nDeplacement d'un glacon\n");                                           //Previens le joueur dans ce cas la
        return -2;                                                                       //Retourne une valeur d'echec pour prevenir la fonction suivante
        break;
    case EAU:
        changeCouleurTexte(joueur->couleur);
        printf("\n%s ", joueur->nom);                                                    //Previens le joueur dans ce cas la
        changeCouleurTexte(BLANC);
        printf("est tombe dans l'eau !");
        ajouteCaseGlace(banquise, joueur->position.x, joueur->position.y);
        spawnJoueur(banquise, joueur);
        return 0;                                                                       //Retourne une valeur d'echec pour prevenir la fonction suivante
        break;
    default :
        joueur->position.x = caseX;   //Affectation de sa nouvelle position
        joueur->position.y = caseY;
        return 0;                     //Retourne une valeur de succes pour la fonction suivante
    }
}


//Fonction qui s'occupe du déplacement du personnage en fonction de ses paramettres, et renvoie un entier en fonction du déplacement
int deplacementJoueur_bis(T_banquise *banquise, T_joueur *joueur, int taille, char deplacement, int **tab)
{
    int jx = joueur->position.x,  //Recupere la position du joueur
        jy = joueur->position.y,
        x, y;                     //Declare 2 entier pour tester le deplacement

    switch (deplacement)          //Effectue le decalage selon la touche mis en parametre et change le vecteur du joueur (utile pour la collision avec un glaçon immobile)
    {
    case 'z' :
        joueur->vecteur.dx = -1;
        joueur->vecteur.dy = 0;
        break;
    case 'q' :
        joueur->vecteur.dx = 0;
        joueur->vecteur.dy = -1;
        break;
    case 's' :
        joueur->vecteur.dx = 1;
        joueur->vecteur.dy = 0;
        break;
    default :
        joueur->vecteur.dx = 0;
        joueur->vecteur.dy = 1;
    }


    x = jx + joueur->vecteur.dx;                  //Positions apres le decalage
    y = jy + joueur->vecteur.dy;

    int caseValeur = -1;

    if (x >= 0 && x < taille && y >= 0 && y < taille)
    {
       caseValeur = tab[x][y];
    }


    return verifieDeplacement(banquise, joueur, x, y, caseValeur, taille);
}


//Fonction qui permet le déplacement du personnage
int deplacementJoueur(T_banquise *banquise, T_joueur *joueur, int taille, int **tab)
{

    char clavier = saisieDeplacement(joueur);                                     //Recupere la bonne touche saisie par le joueur

    int correct = deplacementJoueur_bis(banquise, joueur, taille, clavier, tab);            //Stocke la valeur de la fonction precedente

    if (correct == -2)
        return 4;

    while (correct == -1)                                                         //Si la valeur est une valeur d'echec
    {
        clavier = saisieDeplacement(joueur);                                      //On re-recupere la bonne touche saisie par le joueur
        correct = deplacementJoueur_bis(banquise, joueur, taille, clavier, tab);  //On re-stocke la valeur de la fonction precedente
    }

    joueur->score -= 10;
    return 0;
}



//Fonction test
void affichePositionJoueur(T_joueur *joueur)
{
    printf("x = %d\n", joueur->position.x);
    printf("y = %d\n", joueur->position.y);
}
