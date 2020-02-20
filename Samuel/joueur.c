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
        return ERREUR;
    }
}

//Fonction qui retourne un type joueur selon un numero qui va l'identifier
T_joueur *initJoueur(int numeroJoueur)
{
    T_joueur *joueur = (T_joueur *)malloc(sizeof(T_joueur));  //Alloue de la memoire au type joueur
    T_point pos;                                              //Declare un type point
    pos.x = 0;                                                //Met le joueur sur la premiere ligne
    pos.y = numeroJoueur;                                     //Met le joueur a droite du precedent (en haut a gauche si premier joueur)

    printf("Veuillez choisir un nom pour le joueur numero %d : ", numeroJoueur+1);
    scanf("%s", joueur->nom);                     //Initialise le nom du joueur
    joueur->couleur = choixCouleur();             //Initialise la couleur de joueur
    joueur->identifiant = numeroJoueur;           //Initialise l'identifiant du joueur
    joueur->position = pos;                       //Initialise la position du joueur
    joueur->vecteur.dx = joueur->vecteur.dy = 0;  //Initialise le veteur deplacement du joueur
    joueur->score = 0;

    return joueur;                                //Retourne un pointeur de type joueur
}

//Fonction qui permet le déplacement du personnage
void deplacementJoeur(T_joueur *joueur, int taille)
{
    int stop1 = 0,stop2 = 0, dep; //Initialisation de "stop", la valeur d'arrêt du While et de "dep", la valeur de la réussite du déplacement
    char c;// = getchar();                       //Variable qui va récupérer la touche que l'utilisateurn saisie

    printf("Ou voulez vous vous deplacer ?\n");
    while(stop1 == 0)                                                                        //Boucle while qui permettant à l'utilisateur de refaire son choix si son déplacement est impossible
    {printf("allo\n");
        while(stop2 == 0)                                                                   //Boucle while permettant d'afficher un message d'erreur si la touche saisie est incorrecte
        {printf("allo\n");
            c = getchar();
            c = getchar();
            printf("allo\n");                                                               //Permet de récupérer la touche saisie par le joueur
            if(c!='z' || c!='s' || c!='q' || c!='d')                                        //If qui permet de vérifier si la touhe saisie est correcte
            {
                printf("\nLa touche saisie est inconnue ! Veuillez refaire un choix : ");  //Message d'erreur
            }
            else
            {
                stop2 = 1;                                                                  //Met fin à la 2e boucle while
            }
        }

        switch(c)  //Switch qui appelle la fonction "deplacementJoueur_bis"
        {
        case 'z' :
            dep = deplacementJoeur_bis(joueur, 0, -1, taille);  //Déplacement vers le haut
            break;
        case 's' :
            dep = deplacementJoeur_bis(joueur, 0, 1, taille);  //Déplacement vers le bas
            break;
        case 'q' :
            dep = deplacementJoeur_bis(joueur, -1, 0, taille);  //Déplacement vers la gauche
            break;
        default :
            dep = deplacementJoeur_bis(joueur, 1, 0, taille);  //Déplacement vers la droite
        }

        if(dep == -1)  //If qui vérifie si le déplacement esqt fonctionnel
        {
            printf("\nLe deplacement est impossible ! Veuillez reessayer : ");
        }
        else
        {
            printf("Deplacement reussi !");
            stop1 = 1; //Met fin à la 1er boucle while
        }
    }
}



//Fonction qui s'occupe du déplacement du personnage en fonction de ses paramettres, et renvoie un entier en fonction du déplacement
int deplacementJoeur_bis(T_joueur *j, int dx, int dy, int taille)
{
    int jx = j->position.x, jy = j->position.y, x, y;
    x = jx + dx, y = jy + dy;

    if(x<0 || x>=taille || y<0 || y>=taille)
    {
        printf("\nLe joueur est en dehors du jeu !");
        return -1;
    }
    else
    {
        j->position.x = x, j->position.y = y;
        return 0;
    }
}

void affichePositionJoueur(T_joueur *joueur)
{
    printf("x = %d\n", joueur->position.x);
    printf("y = %d\n", joueur->position.y);
}
