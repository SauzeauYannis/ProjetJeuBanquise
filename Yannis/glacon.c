#include "jeux.h"



//Fonction qui initialise un glacon
T_glacon *initGlacon(int caseX, int caseY)
{
    T_point pos;                                              //Creer un point qui sera la position du glacon
    T_vecteur vect;                                           //Creer le vecteur du glacon
    T_glacon *glacon = (T_glacon *)malloc(sizeof(T_glacon));  //Alloue de la memoire pour le glacon

    pos.x = caseX, pos.y = caseY;                             //Initialise la postion du glacon via les parametres
    vect.dx = vect.dy = 0;                                    //Initialise le vecteur à 0

    glacon->position = pos;                                   //Initialise la position
    glacon->vecteur = vect;                                   //Initialise le vecteur
    glacon->pourcentage_fondre = 0;                           //Initialise le pourcentage de fonte

    return glacon;                                            //Retourne le glacon
}



//Fonction qui verifie que le vecteur du glacon est valide : HAUT BAS GAUCHE DROITE
int verifieVecteurGlacon(T_glacon *glacon)
{
    int dx = glacon->vecteur.dx, dy = glacon->vecteur.dy;                              //Recupere les vecteurs du glacon en parametre

    if(dx != 0 && dy != 0)                                                             //Verifie si il n'y a aucun des deux vecteurs a 0
    {
        printf("Le vecteur du glacon à la position x = %d y = %d est incorrecte !",
               glacon->position.x, glacon->position.y);                                //Affiche un message d'erreur

        return -1;                                                                     //Retourne une valeur d'echec
    }
    else                                                                               //Si les vecteurs sont bons
    {
        return 0;                                                                      //Retourne une valeur de succes
    }
}



//Fonction qui se charge de deplacer le glacon en paramettre
int deplacementGlacon(T_glacon *glacon, T_banquise *banquise, T_joueur **joueurs, int nbJoueurs)
{

    int posx = glacon->position.x, posy = glacon->position.y,          //Position du glacon avant son deplacement
        x = posx + glacon->vecteur.dx, y = posy + glacon->vecteur.dy,  //Position vers laquelle le glacon se deplace
        taille = banquise->tailleN,                                    //Recupere la taille de la banquise
        caseValeur;                                                    //Variable pour prendre la valeur de la case

    ajouteCaseGlace(banquise, posx, posy);                             //Remplace le glacon par de la glace

    if(x < 0 || x >= taille || y < 0 || y >= taille)                   //Verifie si le glacon est dans la matrice
    {
        caseValeur = ERREUR;                                           //Met la valeur de la case a ERREUR
    }
    else                                                               //Si le glacon va bien dans la matrice
    {
        caseValeur = banquise->matrice[x][y];                          //Met la valeur de la case selon le deplacement du glacon
    }

    switch(caseValeur)                                                 //Selon la valeur de la case
    {
        case ERREUR :
        case DEPART :
        case ARRIVE :
            glacon->vecteur.dx = glacon->vecteur.dy = 0;               //Arrete le glacon
            return 0;
            break;
        case JOUEUR :
            {
            T_joueur *joueur;                                          //Variable pour recuperer le joueur touche

            glacon->position.x = x, glacon->position.y = y;            //Recupere la position du glacon
            joueur = joueurSelonPoisition(joueurs, x, y, nbJoueurs);   //Recupere le joueur ou
            tuerJoueur(joueur, banquise);
            return 0;
            break;
            }
        case GLACON :
            //glacon->position.x = x, glacon->position.y = y;
            return 1;
            break;
        case EAU :
            glacon->position.x = x, glacon->position.y = y;
            glacon->vecteur.dx = glacon->vecteur.dy = 0;
            return 2;
            break;
        default :
            glacon->position.x = x, glacon->position.y = y;
            return 0;
    }
}
